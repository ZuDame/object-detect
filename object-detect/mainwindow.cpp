#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

#include <QImage>

#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initilise default values
    initDefaultValues();
}

int MainWindow::loadImages(){
    // left image
    img_source = cv::imread(img_source_path, cv::IMREAD_GRAYSCALE);
    if(img_source.empty()){
        string erormsg = "Left image (object/source) missing";
        cout << erormsg << endl;
        QMessageBox msg(this);
        msg.setText(erormsg.data());
        msg.exec();
        return -1;
    }

    // right image
    img_scene = cv::imread(img_scene_path, cv::IMREAD_GRAYSCALE);
    if(img_scene.empty()){
        string errormsg = "Right image (scene) missing";
        cout << errormsg << endl;
        QMessageBox msg(this);
        msg.setText(errormsg.data());
        msg.exec();
        return -1;
    }

    return 1;
}

void MainWindow::on_pushButtonSourceImage_clicked()
{
    img_source_path = QFileDialog::getOpenFileName(this, "Open image of object to be tracked",
                                                  QDir::homePath()).toStdString();

    cout << "Path to source image: " << img_source_path << endl;
}

void MainWindow::on_pushButtonSceneImage_clicked()
{
    img_scene_path = QFileDialog::getOpenFileName(this, "Open image of scene where object will be tracked",
                                                  QDir::homePath()).toStdString();

    cout << "Path to scene image: " << img_scene_path << endl;
}

void MainWindow::on_pushButtonCpu_clicked()
{
    // first load iamges
    int result = loadImages();

    if(result > 0){
        executeOnCpu();
    }
}

void MainWindow::on_pushButtonGpu_clicked()
{
    // first load iamges
    int result = loadImages();

    if(result > 0){
        executeOnGpu();
    }
}

void MainWindow::executeOnCpu(){
    // write log in console
    cout << "Started serial (CPU) version" << endl;

    // create feature detecetor and feture descriptor
    surf = cv::xfeatures2d::SURF::create(min_hessian);

    // Step 1: detect points of interest
    // Step 2: describe points of interest
    //
    // Note that steps 1 and 2 can be done separate or together
    timer.start();

    surf->detectAndCompute(img_source, cv::noArray(), keypoints_source, descriptor_source, false);
    surf->detectAndCompute(img_scene, cv::noArray(), keypoints_scene, descriptor_scene, false);

    // start geting log infomration
    surf_time_cpu = timer.elapsed();

    keypoints_source_number = keypoints_source.size();
    keypoints_scene_number = keypoints_scene.size();

    descriptor_source_number_cols = descriptor_source.cols;
    descriptor_source_number_rows = descriptor_source.rows;

    descriptor_scene_number_cols = descriptor_scene.cols;
    descriptor_scene_number_rows = descriptor_scene.rows;
    // end geting log informations

    // Step 3:
    // run matcher
    timer.restart();

    matcher.match(descriptor_source, descriptor_scene, matches);

    // start geting log information
    matching_time_cpu = timer.elapsed();
    matches_number = matches.size();
    // end geting log information

    // Step 4:
    // calculate max and min distances between keypoints
    // use this to find best matches later
    calculateMinAndMaxDistance();

    // Step 5:
    // find best matches
    filterMatches();

    // Step 6:
    // join sorce iamge and scene image into one large image
    // and draw lines between good matches
    drawKeyPointsAndMatches();

    // Step 7:
    // localize the object
    localiseObject();

    // Step 8:
    // display processed image
    drawProcessedImage();

    // Step 9
    writeLog("cpu");
    displayInfo();
    displayExecutionTimeCpu();
    freeCpuMemory();
    resetMinAndMaxDistance();
}


void MainWindow::executeOnGpu(){
    // check if cuda capable devices are found
    // if none is found then quit
    int cuda_devices_count = checkForCudaCapableDevice();
    if(cuda_devices_count <= 0){
        cout << "aborting execution of parallel (GPU) version" << endl;
        return;
    }
    cout << "Starting parallel (GPU) version" << endl;

    // Step 0 --extra step on gpu:
    // upload images from host to device
    timer.start();
    img_source_gpu.upload(img_source);
    img_scene_gpu.upload(img_scene);

    // get log information
    memory_upload_time_gpu = timer.elapsed();

    // Step 1: detect points of interest
    // Step 2: describe points of interest
    //
    // Note1: steps 1 and 2 can be done separate or together
    //
    // Note 2: surf_gpu(...) throw 'OpenCV Error: Gpu API call (out of memory) in allocate' error
    // when loading two 4k images
    surf_gpu = cv::cuda::SURF_CUDA(min_hessian);

    timer.restart();
    surf_gpu(img_source_gpu, cv::cuda::GpuMat(), keypoints_source_gpu, descriptor_source_gpu);
    surf_gpu(img_scene_gpu, cv::cuda::GpuMat(), keypoints_scene_gpu, descriptor_scene_gpu);

    // get log informations
    surf_time_gpu = timer.elapsed();

    // used in debugging
    //cout << "Keypoints on source image on GPU: " << keypoints_source_gpu.cols << endl;
    //cout << "Keypoints on scene image on GPU: " << keypoints_scene_gpu.cols << endl;

    //cout << "Descripotr source on GPU: " << descriptor_source_gpu.size() << endl;
    //cout << "Descripotr scene on GPU: " << descriptor_scene_gpu.size() << endl;

    // Step 3:
    // run matcher
    matcher_gpu = cv::cuda::DescriptorMatcher::createBFMatcher(surf_gpu.defaultNorm());

    timer.restart();
    matcher_gpu->match(descriptor_source_gpu, descriptor_scene_gpu, matches);

    // get log informations
    matching_time_gpu = timer.elapsed();
    matches_number = matches.size();

    // Step between 3 and 4 --extra step on gpu
    // download from device to host
    timer.restart();
    surf_gpu.downloadKeypoints(keypoints_source_gpu, keypoints_source);
    surf_gpu.downloadKeypoints(keypoints_scene_gpu, keypoints_scene);

    //surf_gpu.downloadDescriptors(descriptor_source_gpu, descriptor_source_downloaded);
    //surf_gpu.downloadDescriptors(descriptor_scene_gpu, descriptor_scene_downloaded);

    // other way to download descriptors from device to host
    descriptor_source = cv::Mat(descriptor_source_gpu);
    descriptor_scene = cv::Mat(descriptor_scene_gpu);

    // start geting log informations
    memory_download_time_gpu = timer.elapsed();

    keypoints_source_number = keypoints_source.size();
    keypoints_scene_number = keypoints_scene.size();

    descriptor_source_number_cols = descriptor_source.cols;
    descriptor_source_number_rows = descriptor_source.rows;

    descriptor_scene_number_cols = descriptor_scene.cols;
    descriptor_scene_number_rows = descriptor_scene.rows;
    // end geting log informations

    // Step 4:
    // calculate max and min distances between keypoints
    // use this to find best matches later
    calculateMinAndMaxDistance();

    // Step 5:
    // find best matches
    filterMatches();

    // Step 6:
    // join sorce iamge and scene image into one large image
    // and draw lines between good matches
    drawKeyPointsAndMatches();

    // Step 7:
    // localize the object
    localiseObject();

    // Step 8:
    // display processed image
    drawProcessedImage();

    // Step 9
    writeLog("gpu");
    displayInfo();
    displayExecutionTimeGpu();
    freeGpuMemory();
    freeCpuMemory();
    resetMinAndMaxDistance();
}

void MainWindow::calculateMinAndMaxDistance(){
    for (int i = 0; i < descriptor_source.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
}

void MainWindow::filterMatches(){
    for (int i = 0; i < descriptor_source.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, good_matches_threshold))
        {
            good_matches.push_back(matches[i]);
        }
    }

    // get loging informations
    good_matches_number = good_matches.size();
}

void MainWindow::drawKeyPointsAndMatches(){
    cv::drawMatches(img_source, keypoints_source, img_scene,keypoints_scene,
                good_matches, img_processed, cv::Scalar::all(-1), cv::Scalar::all(-1),
                vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // display img_processed at this state
    // used in debugging
    // cv::imshow("conected matching points", img_processed);
}

void MainWindow::localiseObject(){
    // declare corners
    //
    // corners are used to draw square around detected (localised) object
    vector<cv::Point2f> source_corners(4);
    vector<cv::Point2f> scene_corners(4);

    // set corners acording to width of source image,
    // assume that source image is left, scene image is right
    source_corners[0] = (cvPoint(0,0));                                 // top left
    source_corners[1] = (cvPoint(img_source.cols,0));                   // top right
    source_corners[2] = (cvPoint(img_source.cols, img_source.rows));    // botom right
    source_corners[3] = (cvPoint(0,img_source.rows));                   // botom left

    vector<cv::Point2f> obj;
    vector<cv::Point2f> scene;

    // get points of interest from good matrices
    if(good_matches.size() >= 4){
        for(unsigned int i=0; i<good_matches.size(); i++){
            obj.push_back(keypoints_source[good_matches[i].queryIdx].pt);
            scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
        }
    }

    // find the transform between matched keypoints (good_matchces only)
    H = cv::findHomography(obj,scene, CV_RANSAC);

    // map pairs of the corresponding points
    cv::perspectiveTransform(source_corners, scene_corners, H);

    // draw square around detected object
    cv::line(img_processed, scene_corners[0] + cv::Point2f(img_source.cols,0), scene_corners[1] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_processed, scene_corners[1] + cv::Point2f(img_source.cols,0), scene_corners[2] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_processed, scene_corners[2] + cv::Point2f(img_source.cols,0), scene_corners[3] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_processed, scene_corners[3] + cv::Point2f(img_source.cols,0), scene_corners[0] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
}

void MainWindow::drawProcessedImage(){
    // get loging informations
    img_processed_color_chanels = img_processed.channels();

    // display image using opencv
    // cv::imshow("Good matches", img_processed);

    if(img_processed_color_chanels != 3){
        writeLog("GPU");
        cout << "cv::image has " << img_processed_color_chanels << "chanels" << endl;
        cout << "we can handle only cv::images with 3 chanels";

        // messagebox

        return;
    }

    // draw image on qt form
    QImage q_image;
    QPixmap q_pixmap;
    cv::Mat rgb_img_matches;

    // convert  cv::bgr to cv::rgb
    cv::cvtColor(img_processed, rgb_img_matches, CV_BGR2RGB);

    // convert cv::rgb to qImage
    q_image = QImage((const unsigned char *)rgb_img_matches.data,
                     rgb_img_matches.cols,
                     rgb_img_matches.rows,
                     QImage::Format_RGB888);

    // create Qpixmap from QImage
    q_pixmap = QPixmap::fromImage(q_image, Qt::AutoColor);

    // display QPixmap to QT Form
    ui->labelOutputImage->setPixmap(q_pixmap);
}

int MainWindow::checkForCudaCapableDevice(){
    int devices = cv::cuda::getCudaEnabledDeviceCount();

    if(devices <= 0){
        QMessageBox message(this);
        cout << "No CUDA capable device found" << endl;
        message.setText("No CUDA capable device found");
        message.exec();
        return -1;
    }

    else{
       cv::cuda::printShortCudaDeviceInfo(devices);
       return devices;
    }
}

void MainWindow::writeLog(string type){

    log = "";
    stringstream ss;

    ss << "Min hassian: " << min_hessian << endl;

    if(type == "cpu" || type == "Cpu" || type == "CPU"){

        ss << "Detect and describe keypoints: " << surf_time_cpu << "ms" << endl;
        ss << "Match keypoints: " << matching_time_cpu << "ms" << endl;
    }
    else{
        memory_total_time_gpu = memory_upload_time_gpu + memory_download_time_gpu;
        ss << "Memory transfer host->device->host" << memory_total_time_gpu << endl;
        ss << "Detect and describe keypoints: " << memory_upload_time_gpu + surf_time_gpu << "ms" << endl;
        ss << "Match keypoints: " << matching_time_gpu << "ms" << endl;
    }

    ss << "Keypoints on source image: " << keypoints_source_number << endl;
    ss << "Keypoints on scene image: " << keypoints_scene_number << endl;

    ss << "Descripotr source: " << descriptor_source_number_cols << " x " << descriptor_source_number_rows << endl;
    ss << "Descripotr scene: " << descriptor_scene_number_cols << " x " << descriptor_scene_number_rows << endl;

    ss << "Matches: " << matches_number << endl;
    ss << "Good matches threshold: " << good_matches_threshold << endl;
    ss << "Good matches: " << good_matches_number << endl;

    ss << "Min dist: " << min_dist << endl;
    ss << "Max dist: " << max_dist << endl;

    ss << "openCV processed image has: " << img_processed_color_chanels << " chanels" << endl;

    // write two emtpy lines in log, make it easyer to read
    ss << endl << endl;

    // write log
    log += ss.str();
    cout << log << endl;
}

void MainWindow::freeCpuMemory(){

    img_source.release();
    img_scene.release();

    matcher.clear();;

    matches.clear();
    good_matches.clear();

    keypoints_source.clear();
    keypoints_scene.clear();

    descriptor_source.release();
    descriptor_scene.release();

    H.release();

    img_processed.release();

    log.clear();
}

void MainWindow::freeGpuMemory(){

    img_source_gpu.release();
    img_scene_gpu.release();

    keypoints_source_gpu.release();
    keypoints_scene_gpu.release();

    descriptor_source_gpu.release();
    descriptor_scene_gpu.release();

    surf_gpu.releaseMemory();

    matcher_gpu.release();
}

void MainWindow::displayInfo(){
    QString q_string_keypoints_source;
    QString q_string_keypoints_scene;
    QString q_keypoints;

    QString q_string_matches;
    QString q_string_good_matches;

    // display keypoints
    q_string_keypoints_source = QString::number(keypoints_source_number);
    q_string_keypoints_scene = QString::number(keypoints_scene_number);

    q_keypoints = QString();
    q_keypoints.append(q_string_keypoints_source);
    q_keypoints.append(" / ");
    q_keypoints.append(q_string_keypoints_scene);

    ui->lineEditKeyPoints->setText(q_keypoints);

    // display matches
    q_string_matches = QString::number(matches_number);
    ui->lineEditMatches->setText(q_string_matches);

    // display good matches
    q_string_good_matches = QString::number(good_matches_number);
    ui->lineEditGoodMatches->setText(q_string_good_matches);
}

void MainWindow::displayExecutionTimeCpu(){
    QString q_string_execution_time_cpu;
    int timeCpu;

    timeCpu = surf_time_cpu + matching_time_cpu;
    q_string_execution_time_cpu = QString::number(timeCpu);

    ui->lineEditExecutionTimeCpu->setText(q_string_execution_time_cpu);
}

void MainWindow::displayExecutionTimeGpu(){
    QString q_string_execution_time_gpu;
    int timeGpu;

    timeGpu = surf_time_gpu + matching_time_gpu + memory_upload_time_gpu + memory_download_time_gpu;
    q_string_execution_time_gpu = QString::number(timeGpu);

    ui->lineEditExecutionTimeGpu->setText(q_string_execution_time_gpu);
}


void MainWindow::initDefaultValues(){
    min_hessian = ui->spinBoxMinHessian->value();
    good_matches_threshold = ui->spinBoxGoodMatchesThreshold->value() / 100.0;

    resetMinAndMaxDistance();
}

void MainWindow::resetMinAndMaxDistance(){
    min_dist = 100;
    max_dist = 0;
}

void MainWindow::on_spinBoxMinHessian_valueChanged(int arg1)
{
    min_hessian = arg1;
}

void MainWindow::on_spinBoxGoodMatchesThreshold_valueChanged(int arg1)
{
    good_matches_threshold = arg1 / 100.0;
}

MainWindow::~MainWindow()
{
    delete ui;
}




