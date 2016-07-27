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

    void on_pushButtonSourceImage_clicked();

    void on_pushButtonSceneImage_clicked();

    void on_spinBoxMinHessian_valueChanged(int arg1);

    void on_spinBoxGoodMatchesThreshold_valueChanged(int arg1);

private:
    /* ##################################
     * #                                #
     * #        Variables               #
     * #                                #
     * ##################################
     */

    // path to soruce and scene images
    string img_source_path;
    string img_scene_path;

    // timer to measure execution time of methods
    QElapsedTimer timer;

    // minimal Hessian threshold for SURF
    //
    // an approximation of the Hessian matrix is built with the partial derivatives
    // of the image intensities within a patch around the pixel
    //
    // the higher the minHessian the fewer keypoints it detect but
    // each keypoint is more repetitive (usefull)
    //
    // a value between 400 and 800 works best.
    int min_hessian;

    // threshold to determine good_matches
    //
    // use value between 0 and 1 representing
    // 0.0 -> nothing will be marked as good match
    // 1.0 -> everything will be marked as good match
    //
    // 0.2 -> 20% deference is acceptable
    // 0.8 -> 80 % deference is acceptable
    //
    // value of 0.2 (20 / 100) is good
    double good_matches_threshold;

    // image of the object and
    // image of the scene where we try to detect instance of the object
    cv::Mat img_source;
    cv::Mat img_scene;

    cv::cuda::GpuMat img_source_gpu;
    cv::cuda::GpuMat img_scene_gpu;

    // points of interest determinated by SURF
    vector<cv::KeyPoint> keypoints_source;
    vector<cv::KeyPoint> keypoints_scene;

    cv::cuda::GpuMat keypoints_source_gpu;
    cv::cuda::GpuMat keypoints_scene_gpu;

    // descriptors of points of interest
    cv::Mat descriptor_source;
    cv::Mat descriptor_scene;

    cv::cuda::GpuMat descriptor_source_gpu;
    cv::cuda::GpuMat descriptor_scene_gpu;

    // SURF
    cv::Ptr<cv::xfeatures2d::SURF> surf;
    cv::cuda::SURF_CUDA surf_gpu;

    // matching alogorytham (brute force or flann based)
    //cv::FlannBasedMatcher matcher;
    cv::BFMatcher matcher;
    cv::Ptr<cv::cuda::DescriptorMatcher> matcher_gpu;

    // distance to determine good matches
    //
    // only good matches are being drown later
    double min_dist;
    double max_dist;

    // matching points
    vector<cv::DMatch> matches;
    vector<cv::DMatch> good_matches;

    // image to be displayed as final result
    //
    // contains matching points (circles) and a line between two matching points
    cv::UMat img_processed;

    // homography matrix
    cv::Mat H;

    // variables used for debugging
    string log;

    int img_processed_color_chanels;

    int keypoints_source_number;
    int keypoints_scene_number;

    int descriptor_source_number_rows;
    int descriptor_source_number_cols;

    int descriptor_scene_number_rows;
    int descriptor_scene_number_cols;

    int matches_number;
    int good_matches_number;

    int surf_time_cpu;
    int surf_time_gpu;

    int matching_time_cpu;
    int matching_time_gpu;

    int memory_upload_time_gpu;
    int memory_download_time_gpu;
    int memory_total_time_gpu;

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

    // calculate minimal distance between two keypoints and
    // maximum distance between two keypoints
    //
    // later it is used to filter(find) good_matches
    void calculateMinAndMaxDistance();

    // return negative number and messagebox if no cuda capable device is found
    // return number of cuda capable devices if they are found
    int checkForCudaCapableDevice();

    // filter good matches from all matches
    void filterMatches();

    // draw circles(keypoints) and lines (matches)
    void drawKeyPointsAndMatches();

    // localise source object on scene
    //
    // draw square if source object is found
    void localiseObject();

    // draw processed image on QT form
    void drawProcessedImage();

    // display updated information on QT
    //
    // data from last kernel (cpu or gpu) is being displayed
    void displayInfo();

    // update exectuion time on cpu
    void displayExecutionTimeCpu();

    // update execution time on gpu
    void displayExecutionTimeGpu();

    // write and print log
    void writeLog(string);

    // free memory
    void freeAllMemory();
    void freeGpuMemory();
    void freeCpuMemory();

    // initialise default values
    void initDefaultValues();

    // reset min and max distances;
    void resetMinAndMaxDistance();
};

#endif // MAINWINDOW_H
