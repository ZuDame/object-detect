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
        QMessageBox msg(this);
        msg.setText("Left image (src) can not be loaded");
        msg.exec();
        return -1;
    }

    // right image
    img_scene = cv::imread("/home/borche/Documents/git/object-detect/images/books-opencv//box_in_scene.png", cv::IMREAD_GRAYSCALE);
    if(img_scene.empty()){
        QMessageBox msg(this);
        msg.setText("Rught image (gray_image) can not be loaded");
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
    cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(400);
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::xfeatures2d::SURF::create(400);

    // detect points of interest;
    detector->detect(img_source, keypoints_source);
    detector->detect(img_scene,keypoints_scene);

    // print result in console
    cout << "FOUND " << keypoints_source.size() << " keypoints on source image" << endl;
    cout << "FOUND " << keypoints_scene.size() << " keypoints on scene image" << endl;

    // describe neighborhood for points of interest
    descriptor->compute(img_source, keypoints_source, img_source_descriptor);
    descriptor->compute(img_scene, keypoints_scene, img_scene_descriptor);

    // run matcher
    matcher.match(img_source_descriptor, img_scene_descriptor, matches);

    // define corners
    vector<cv::Point2f> obj_corners(4);
    vector<cv::Point2f> scene_corners(4);

    // vectors to return matching points
    // aka localize the object
    vector<cv::Point2f> obj;
    vector<cv::Point2f> scene;

    // set corners for detected object,
    // make offset acording to src width,
    // assume that src is left, gray_image is right
    obj_corners[0] = (cvPoint(0,0));                                            // top left
    obj_corners[1] = (cvPoint(img_source.cols,0));                       // top right
    obj_corners[2] = (cvPoint(img_source.cols, img_source.rows)); // botom right
    obj_corners[3] = (cvPoint(0,img_source.rows));                       // botom left

    // calculate max and min distances between keypoints
    for (int i = 0; i < img_source_descriptor.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    cout << "-- max dist: " << max_dist << endl;
    cout << "-- min dist: " << min_dist << endl;
    //printf("-- Max dist : %f \n", max_dist);
    //printf("-- Min dist : %f \n", min_dist);

    // find best matches
    for (int i = 0; i < img_source_descriptor.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, 0.2))
        {
            good_matches.push_back(matches[i]);
        }
    }
    cout << "-- good matches: " << good_matches.size() << endl;

    // draw matches on a form
    cv::drawMatches(img_source, keypoints_source, img_scene,keypoints_scene,
                good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // get points of interest from good matrices
    if(good_matches.size() >= 4){
        for(int i=0; i<good_matches.size(); i++){
            obj.push_back(keypoints_source[good_matches[i].queryIdx].pt);
            scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
        }
    }

    H = cv::findHomography(obj,scene, CV_RANSAC);

    // Calculate a perspective transform from four pairs of the corresponding points/*
    cv::perspectiveTransform(obj_corners, scene_corners, H);

    // tracking
    cv::line(img_matches, scene_corners[0] + cv::Point2f(img_source.cols,0), scene_corners[1] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_matches, scene_corners[1] + cv::Point2f(img_source.cols,0), scene_corners[2] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_matches, scene_corners[2] + cv::Point2f(img_source.cols,0), scene_corners[3] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);
    cv::line(img_matches, scene_corners[3] + cv::Point2f(img_source.cols,0), scene_corners[0] + cv::Point2f(img_source.cols,0), cv::Scalar(0, 255, 0), 4);

    cv::imshow("Good matches", img_matches);
}


void::MainWindow::executeOnGpu(){

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






