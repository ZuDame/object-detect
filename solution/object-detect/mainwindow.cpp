#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "surflogic.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

// dclare global variable for SurfLogic library
SurfLogic model;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model.initDefaultValues();

    // /////////////////////////////////////

//    cv::DMatch first = cv::DMatch(1,1,0.5);
//    cv::DMatch second = cv::DMatch(1,1,0.8);
//    int result;

//    if(first.distance < second.distance){
//        result = 1;
//    }
//    else{
//        result = 0;
//    }
//    qDebug() << QString::number(result);

    // ////////////////////////////////////////

//    cv::DMatch first = cv::DMatch(1,1,0.1);
//    cv::DMatch second = cv::DMatch(1,1,0.2);
//    cv::DMatch third = cv::DMatch(1,1,0.4);
//    cv::DMatch fourth = cv::DMatch(1,1,0.8);
//    cv::DMatch fifth = cv::DMatch(1,1,0.6);

//    vector<cv::DMatch> vectormatches;

//    vectormatches.push_back(first);
//    vectormatches.push_back(second);
//    vectormatches.push_back(third);
//    vectormatches.push_back(fourth);
//    vectormatches.push_back(fifth);

//    qDebug() << QString::number(vectormatches.size());
}

MainWindow::~MainWindow()
{
    // default destructor
    delete ui;
}

void MainWindow::on_pushButtonSourceImage_clicked()
{
    model.img_source_path = QFileDialog::getOpenFileName(this, "Open image of object to be tracked",
                                                        QDir::homePath()).toStdString();

    cout << "Path to source image: " << model.img_source_path << endl;
}

void MainWindow::on_pushButtonSceneImage_clicked()
{
    model.img_scene_path = QFileDialog::getOpenFileName(this, "Open image of scene where object will be tracked",
                                                        QDir::homePath()).toStdString();

    cout << "Path to scene image: " << model.img_scene_path << endl;
}

void MainWindow::on_pushButtonCpu_clicked()
{
    // first load iamges
    int result = model.loadImages();

    if(result > 0){
        //model.executeOnCpu();
        setSurfParameters();
        executeOnCpu();
    }
    else{
        QMessageBox msg(this);
        msg.setText(model.img_load_error_msg.data());
        msg.exec();
    }
}

void MainWindow::on_pushButtonGpu_clicked()
{
    // first load iamges
    int result = model.loadImages();

    if(result > 0){
        setSurfParameters();
        executeOnGpu();
    }
    else{
        QMessageBox msg(this);
        msg.setText(model.img_load_error_msg.data());
        msg.exec();
    }
}

void MainWindow::executeOnCpu(){
    // represent the status of method call
    // <0 -> failed
    // >0 -> sucessfull
    int status;

    // write log in console
    cout << "Started serial (CPU) version" << endl;

    // create feature detecetor and feture descriptor
    model.createSurfCpu();

    // Step 1: detect points of interest
    // Step 2: describe points of interest
    //
    // Note that steps 1 and 2 can be done separate or together

    // update progressbar that we are at step 1
    // note that this update do not represent that step 1 is finished as expected
    updateProgressbarValue(1);
    status = model.detectAndDescribeCPU();
    if(status < 0){
        displayErrorMsg(model.error_message);
        return;
    }

    // update progress bar that we finished step 2
    updateProgressbarValue(2);

    // Step 3:
    // run matcher
    model.runMatcherCPU();

    // update progress bar that we finished step 3
    updateProgressbarValue(3);

    // Step 4:
    // calculate max and min distances between keypoints
    // use this to find best matches later
    model.calculateMinAndMaxDistance();

    // update progress bar that we finished step 4
    updateProgressbarValue(4);

     // Step 5:
     // find best matches
     model.filterMatches();

     // update progress bar that we finished step 5
     updateProgressbarValue(5);

     // Step 6:
     // join sorce iamge and scene image into one large image
     // and draw lines between good matches
     model.drawKeyPointsAndMatches();

     // update progress bar that we finished step 6
     updateProgressbarValue(6);

     // Step 7:
     // localize the object
     model.localiseObject();
     updateProgressbarValue(7);

     // Step 8:
     // display processed image
     drawProcessedImage();
     updateProgressbarValue(8);

     // Step 9
     model.writeLog("cpu");
     displayInfo();
     displayExecutionTimeCpu();
     model.resetMinAndMaxDistance();
     model.freeCpuMemory();

}

void MainWindow::executeOnGpu(){
    // first check if CUDA capable devices are found
    // if none is found then quit
    int cuda_devices_count = checkForCudaCapableDevice();

    if(cuda_devices_count <= 0){
        cout << "aborting execution of parallel (GPU) version" << endl;
        cout << "No CUDA cabaple device is found" << endl;

        QMessageBox msg(this);
        msg.setText("No CUDA cabaple device is found");
        msg.exec();

        return;
    }
    cout << "Starting parallel (GPU) version" << endl;

    // create feature detecetor and feture descriptor
    model.createSurfGpu();

    // Step 0 --extra step on GPU:
    // upload images from host to device
    //
    // note that tis method will also initialize the timer
    // we need to measure the tupe spent on host -> device transfer
    model.uploadImagesFromHostToDevuce();

    // Step 1: detect points of interest
    // Step 2: describe points of interest
    //
    // Note1: steps 1 and 2 can be done separate or together
    //
    // Note 2: surf_gpu(...) throw 'OpenCV Error: Gpu API call (out of memory) in allocate' error
    // when loading two 4K images

    // update progressbar that we are at step 1
    // note that this update do not represent taht step 1 is finished as expected
    updateProgressbarValue(1);
    if(model.detectAndDescribeGPU() == -1){
        displayErrorMsg(model.error_message);
        return;
    }
    updateProgressbarValue(2);

    // Step 3:
    // run matcher
    if(model.runMatcherGPU() == -1){
        displayErrorMsg(model.error_message);
        return;
    }
    updateProgressbarValue(3);

    // Step 4:
    // calculate max and min distances between keypoints
    // use this to find best matches later
    model.calculateMinAndMaxDistance();
    updateProgressbarValue(4);

    // Step 5:
    // find best matches
    model.filterMatches();
    updateProgressbarValue(5);

    // Step 6:
    // join sorce iamge and scene image into one large image
    // and draw lines between good matches
    model.drawKeyPointsAndMatches();
    updateProgressbarValue(6);

    // Step 7:
    // localize the object
    model.localiseObject();
    updateProgressbarValue(7);

    // Step 8:
    // display processed image
    drawProcessedImage();
    updateProgressbarValue(8);

    // Step 9
    model.writeLog("gpu");
    displayInfo();
    displayExecutionTimeGpu();
    model.resetMinAndMaxDistance();
    model.freeGpuMemory();
    model.freeCpuMemory();
}

void MainWindow::drawProcessedImage(){
    // get loging informations
    model.img_processed_color_chanels = model.img_processed.channels();

    // display image using opencv
    // cv::imshow("Good matches", img_processed);

    if(model.img_processed_color_chanels != 3){
        model.writeLog("GPU");
        // **********************************************
        // error ^ don't use GPU when writing this log,
        // it might come from CPU kernel
        // **********************************************
        cout << "cv::image has " << model.img_processed_color_chanels << "chanels" << endl;
        cout << "we can handle only cv::images with 3 chanels";

        // messagebox

        return;
    }

    // draw image on qt form
    QImage q_image;
    QPixmap q_pixmap;
    cv::Mat rgb_img_matches;

    // convert  cv::bgr to cv::rgb
    cv::cvtColor(model.img_processed, rgb_img_matches, CV_BGR2RGB);

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

void MainWindow::displayInfo(){
    QString q_string_keypoints_source;
    QString q_string_keypoints_scene;
    QString q_keypoints;

    QString q_string_matches;
    QString q_string_good_matches;

    // display keypoints
    q_string_keypoints_source = QString::number(model.keypoints_source_number);
    q_string_keypoints_scene = QString::number(model.keypoints_scene_number);

    q_keypoints = QString();
    q_keypoints.append(q_string_keypoints_source);
    q_keypoints.append(" / ");
    q_keypoints.append(q_string_keypoints_scene);

    ui->lineEditKeyPoints->setText(q_keypoints);

    // display matches
    q_string_matches = QString::number(model.matches_number);
    ui->lineEditMatches->setText(q_string_matches);

    // display good matches
    q_string_good_matches = QString::number(model.good_matches_number);
    ui->lineEditGoodMatches->setText(q_string_good_matches);
}

void MainWindow::displayExecutionTimeCpu(){
    QString q_string_execution_time_cpu;
    int timeCpu;

    timeCpu = model.surf_time_cpu + model.matching_time_cpu;
    q_string_execution_time_cpu = QString::number(timeCpu);

    ui->lineEditExecutionTimeCpu->setText(q_string_execution_time_cpu);
}

void MainWindow::displayExecutionTimeGpu(){
    QString q_string_execution_time_gpu;
    int timeGpu;

    timeGpu = model.surf_time_gpu +
                model.matching_time_gpu +
                model.memory_upload_time_gpu +
                model.memory_download_time_gpu;
    q_string_execution_time_gpu = QString::number(timeGpu);

    ui->lineEditExecutionTimeGpu->setText(q_string_execution_time_gpu);
}

void MainWindow::updateProgressbarValue(int step){
    ui->progressBar->setValue(100.0 / model.steps_number * step);
}

int MainWindow::checkForCudaCapableDevice(){
    int devices = cv::cuda::getCudaEnabledDeviceCount();

    if(devices > 0){
        cv::cuda::printShortCudaDeviceInfo(devices);
    }

    return devices;
}

void MainWindow::displayErrorMsg(QString error){
    QMessageBox msg(this);

    msg.setText(error);
    msg.exec();
}

void MainWindow::setSurfParameters(){
    model.setSurfParameters(ui->spinBoxMinHessian->value(),
                            ui->spinBoxOctaves->value(),
                            ui->spinBoxOctaveLayers->value(),
                            ui->checkBoxExtended->checkState(),
                            ui->checkBoxUpright->checkState(),
                            ui->spinBoxGoodMatchesThreshold->value());
}
