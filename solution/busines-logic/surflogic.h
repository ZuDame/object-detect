#ifndef SURFLOGIC_H
#define SURFLOGIC_H

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

#include <QString>
#include <QElapsedTimer>

using namespace std;

class SurfLogic
{
public:
    // default constructor
    SurfLogic();

    /*
     /////////////////////////////
     //                         //
     //         Variables       //
     //                         //
     /////////////////////////////
    */

    // timer to measure execution time of methods
    QElapsedTimer timer;

    // number of steps required to find matches, draw lines and localize
    int steps_number;

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

    // distance to determine good matches
    //
    // only good matches are being drown later
    double min_dist;
    double max_dist;

    // path to soruce and scene images
    string img_source_path;
    string img_scene_path;

    // image of the object and
    // image of the scene where we try to detect instance of the object
    cv::Mat img_source;
    cv::Mat img_scene;

    cv::cuda::GpuMat img_source_gpu;
    cv::cuda::GpuMat img_scene_gpu;

    // error message describing why image is not being loaded
    string img_load_error_msg;

    // general purpose error message
    // used to transfer some error message to mainwindow
    QString error_message;

    // SURF
    cv::Ptr<cv::xfeatures2d::SURF> surf;
    cv::cuda::SURF_CUDA surf_gpu;

    // matching alogorytham (brute force or flann based)
    //cv::FlannBasedMatcher matcher;
    cv::BFMatcher matcher_cpu;
    cv::Ptr<cv::cuda::DescriptorMatcher> matcher_gpu;

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

    /*
     /////////////////////////////
     //                         //
     //         Methods         //
     //                         //
     /////////////////////////////
    */

    // CPU version
    void executeOnCpu();

    // initialise default values
    void initDefaultValues();

    // reset min and max distances;
    void resetMinAndMaxDistance();

    // load images from my pc
    //
    // note1: this method is using absolute path to the images
    // note2: return 1 if images are sucessfully loaded
    //        return -1 if images are not sucessfully loaded
    //                    and the error is stored in 'img_load_error_msg'
    int loadImages();

    // upload images from host memory (cpu) to device memory (gpu)
    void uploadImagesFromHostToDevuce();

    // update progressbar value
    //
    // accept an integer value that represent the number of most recently finished step
    void updateProgressbarValue(int);

    // create SURF kernel
    void createSurfCpu();
    void createSurfGpu();

    // create matcher for GPU
    void createMatcherGpu();

    // detects points of interest and
    // describes neighbourhood around points of interest
    int detectAndDescribeCPU();
    int detectAndDescribeGPU();

    // comparing points of interest
    int runMatcherCPU();
    int runMatcherGPU();

    // calculate minimal distance between two keypoints and
    // maximum distance between two keypoints
    //
    // later it is used to filter(find) good_matches
    int calculateMinAndMaxDistance();

    // filter good matches from all matches
    int filterMatches();

    // draw circles(keypoints) and lines (matches)
    int drawKeyPointsAndMatches();

    // localise source object on scene
    //
    // draw square if source object is found
    void localiseObject();

    // write and print log
    void writeLog(string);

    // free up (release) memory
    void freeCpuMemory();
    void freeGpuMemory();

private:

};

#endif // SURFLOGIC_H
