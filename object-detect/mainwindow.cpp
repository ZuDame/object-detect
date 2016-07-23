#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QMessageBox>


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


int MainWindow::loadImages(){
    // left image
    img_source = cv::imread("/home/borche/Documents/git/object-detect/images/books-opencv/box.png", cv::IMREAD_GRAYSCALE);
    if(img_source.empty()){
        string erormsg = "Left image (src) can not be loaded";
        cout << erormsg << endl;
        QMessageBox msg(this);
        msg.setText(erormsg.data());
        msg.exec();
        return -1;
    }

    // right image
    img_scene = cv::imread("/home/borche/Documents/git/object-detect/images/books-opencv//box_in_scene.png", cv::IMREAD_GRAYSCALE);
    if(img_scene.empty()){
        string errormsg = "Rught image (gray_image) can not be loaded";
        cout << errormsg << endl;
        QMessageBox msg(this);
        msg.setText(errormsg.data());
        msg.exec();
        return -1;
    }

    return 1;
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
    cout << "Using serial (CPU) version for SURF" << endl;

    // create feature detecetor and feture descriptor
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(100);

    // Step 1: detect points of interest
    // Step 2: describe points of interest
    //
    // Note that steps 1 and 2 can be done separate or together
    surf->detectAndCompute(img_source, cv::noArray(), keypoints_source, source_descriptor, false);
    surf->detectAndCompute(img_scene, cv::noArray(), keypoints_scene, scene_descriptor, false);

    // print result in console
    cout << "Found " << keypoints_source.size() << " keypoints on source image" << endl;
    cout << "Found " << keypoints_scene.size() << " keypoints on scene image" << endl;

    cout << "Size of source descripotr: " << source_descriptor.size() << endl;
    cout << "Size of scene descripotr: " << scene_descriptor.size() << endl;

    // Step 3:
    // run matcher
    matcher.match(source_descriptor, scene_descriptor, matches);

    // Step 4:
    // calculate max and min distances between keypoints
    // use this to find best matches later
    for (int i = 0; i < source_descriptor.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    // print results
    cout << "-- max dist: " << max_dist << endl;
    cout << "-- min dist: " << min_dist << endl;

    // Step 5:
    // find best matches
    for (int i = 0; i < source_descriptor.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, 0.2))
        {
            good_matches.push_back(matches[i]);
        }
    }

    // print result
    cout << "-- good matches: " << good_matches.size() << endl;

    // Step 6:
    // join sorce iamge and scene image into one large image
    // and draw lines between good matches
    cv::drawMatches(img_source, keypoints_source, img_scene,keypoints_scene,
                good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Step 7:
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

    // Step 8;
    // represent good_matches as vector of points
    // aka localize the object
    vector<cv::Point2f> obj;
    vector<cv::Point2f> scene;

    // get points of interest from good matrices
    if(good_matches.size() >= 4){
        for(int i=0; i<good_matches.size(); i++){
            obj.push_back(keypoints_source[good_matches[i].queryIdx].pt);
            scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
        }
    }

    // Step 9:
    // find the transform between matched keypoints
    H = cv::findHomography(obj,scene, CV_RANSAC);

    // map pairs of the corresponding points
    cv::perspectiveTransform(source_corners, scene_corners, H);

    // draw square around detected object
    cv::line(img_matches, scene_corners[0] + cv::Point2f(img_source.cols,0), scene_corners[1] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_matches, scene_corners[1] + cv::Point2f(img_source.cols,0), scene_corners[2] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_matches, scene_corners[2] + cv::Point2f(img_source.cols,0), scene_corners[3] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_matches, scene_corners[3] + cv::Point2f(img_source.cols,0), scene_corners[0] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);

    // Step 10:
    // display final image
    cv::imshow("Good matches", img_matches);
}


void::MainWindow::executeOnGpu(){
    // check if cuda capable devices are found
    // if none is found then quit
    int cuda_devices_count = checkForCudaCapableDevice();
    if(cuda_devices_count <= 0){
        cout << "abort execution of parallel (GPU) version" << endl;
    }
    cout << "Using parallel (GPU) version" << endl;

    // declare matrices on gpu


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


MainWindow::~MainWindow()
{
    delete ui;
}






