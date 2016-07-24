#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"

#include "opencv2/cudafeatures2d.hpp"
#include "opencv2/xfeatures2d/cuda.hpp"

#include <QElapsedTimer>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    static void workBegin();
//    static void workEnd();
//    static double getTime();

//    static cv::Mat drawGoodMatches(const cv::Mat& img1,
//                               const cv::Mat& img2,
//                               const std::vector<cv::KeyPoint>& keypoints1,
//                               const std::vector<cv::KeyPoint>& keypoints2,
//                               std::vector<cv::DMatch>& matches,
//                               std::vector<cv::Point2f>& scene_corners_);


private slots:
    void on_pushButtonGpu_clicked();

    void on_pushButtonCpu_clicked();

private:
    /* ##################################
     * #                                #
     * #        Variables               #
     * #                                #
     * ##################################
     */

    // timer to measure execution time of methods
    QElapsedTimer timer;


    // source image of the object and
    // image of the scene where we track for the object
    cv::Mat img_source;
    cv::Mat img_scene;

    // points of interest
    vector<cv::KeyPoint> keypoints_source;
    vector<cv::KeyPoint> keypoints_scene;

    // descriptors of points of interest
    cv::Mat descriptor_source;
    cv::Mat descriptor_scene;

    // matching alogorytham (brute force or flann based)
    //cv::FlannBasedMatcher matcher;
    cv::BFMatcher matcher;

    // distance for the matcher to accept match or not match
    double max_dist = 0;
    double min_dist = 100;

    // vectors of matching points
    vector<cv::DMatch> matches;
    vector<cv::DMatch> good_matches;

    // image that contains lines matches that should be displayed
    // on top of the actial image as circles
    cv::UMat img_matches;

    // declare homography matrix
    cv::Mat H;

    // pointer to the form
    Ui::MainWindow *ui;

    /* ##################################
     * #                                #
     * #        Methods                 #
     * #                                #
     * ##################################
     */

    // CPU version
    void executeOnCpu();

    // GPU Version
    void executeOnGpu();

    // load images from my pc
    // note that this method is using absolute path to the images
    int loadImages();

    // return negative number and messagebox if no cuda capable device is found
    // return number of cuda capable devices if they are found
    int checkForCudaCapableDevice();
};

#endif // MAINWINDOW_H
