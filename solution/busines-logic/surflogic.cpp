#include "surflogic.h"

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
#include <QDebug>
#include <QDir>
#include <sstream>

SurfLogic::SurfLogic()
{
    // default constructor
}

void SurfLogic::initDefaultValues(){
    steps_number = 8;
    min_hessian = 100;
    good_matches_threshold = 0.2;    // 0.2 = 20 / 100.0;

    upright = false;
    extended = false;

    num_octaves = 4;
    num_of_layers_per_octave = 2;

    resetMinAndMaxDistance();
}

void SurfLogic::resetMinAndMaxDistance(){
    min_dist = 100;
    max_dist = 0;
}

int SurfLogic::loadImages(){
    // left image
    img_source = cv::imread(img_source_path, cv::IMREAD_GRAYSCALE);
    if(img_source.empty()){
        img_load_error_msg = "Left image (object/source) missing";
        cout << img_load_error_msg << endl;
        return -1;
    }

    // right image
    img_scene = cv::imread(img_scene_path, cv::IMREAD_GRAYSCALE);
    if(img_scene.empty()){
        img_load_error_msg = "Right image (scene) missing";
        cout << img_load_error_msg << endl;
        return -2;
    }

    return 1;
}

void SurfLogic::createSurfCpu(){
    // create feature detecetor and feture descriptor
    surf = cv::xfeatures2d::SURF::create(min_hessian, num_octaves, num_of_layers_per_octave, extended, upright);
}

void SurfLogic::createSurfGpu(){
    // create feature detecetor and feture descriptor
    surf_gpu = cv::cuda::SURF_CUDA(min_hessian, num_octaves, num_of_layers_per_octave, extended, 0.01f, upright);
}

int SurfLogic::detectAndDescribeCPU(){
    if(img_source.empty() || img_scene.empty()){
        error_message = QString("Source or Scene image missing. Can't execute: detectAndDescribeCPU()");
        return -1;
    }

    timer.start();
    // detectAndCompute throw assertion error
    // OpenCV Error: Assertion failed (!_img.empty() && CV_MAT_DEPTH(imgtype) == CV_8U && (imgcn == 1 || imgcn == 3 || imgcn == 4))
    try{
        surf->detectAndCompute(img_source, cv::noArray(), keypoints_source, descriptor_source, false);
        surf->detectAndCompute(img_scene, cv::noArray(), keypoints_scene, descriptor_scene, false);
    }
    catch(...){
        error_message = QString("failed execution of surf->detectAndCompute() on CPU");
        return -2;
    }

    // start geting log infomration
    surf_time_cpu = timer.elapsed();

    keypoints_source_number = keypoints_source.size();
    keypoints_scene_number = keypoints_scene.size();

    descriptor_source_number_cols = descriptor_source.cols;
    descriptor_source_number_rows = descriptor_source.rows;

    descriptor_scene_number_cols = descriptor_scene.cols;
    descriptor_scene_number_rows = descriptor_scene.rows;
    // end geting log informations

    return 1;
}

int SurfLogic::detectAndDescribeGPU(){
    if(img_source_gpu.empty() || img_scene_gpu.empty()){
        error_message = QString("Source or Scene image missing. Can't proceed detectAndDescribeGPU() method");
        return -1;
    }
    try{
        timer.restart();
        surf_gpu(img_source_gpu, cv::cuda::GpuMat(), keypoints_source_gpu, descriptor_source_gpu);
        surf_gpu(img_scene_gpu, cv::cuda::GpuMat(), keypoints_scene_gpu, descriptor_scene_gpu);
    }
    catch(...){
        error_message = "detectAndDescribeGPU() failed. Can't execute GPU kernel";
        return -2;
    }

    // get log informations
    surf_time_gpu = timer.elapsed();

    // Note: number of keypoints and it's dimensions will be downloaded later
    //
    // there is method that download them from device memory to host memory
    return 1;
}

int SurfLogic::runMatcherCPU(){
    if(descriptor_source.empty() || descriptor_scene.empty()){
        error_message = "runMatcherCPU() failed. Can't proceed to the kernel with empty descriptors";
        return -1;
    }

    try{
        timer.restart();
        matcher_cpu.match(descriptor_source, descriptor_scene, matches);
    }
    catch(...){
        error_message = "matcher_cpu.match() failed";
        return -2;
    }

    // start geting log information
    matching_time_cpu = timer.elapsed();
    matches_number = matches.size();
    // end geting log information

    return 1;
}

int SurfLogic::runMatcherGPU(){
    createMatcherGpu();

    if(descriptor_source_gpu.empty() || descriptor_scene_gpu.empty()){
          error_message = "runMatcherGPU() failed, descriptor_source_gpu or descriptor_scene_gpu is empty";
          return -1;
    }

    try{
        timer.restart();
        matcher_gpu->match(descriptor_source_gpu, descriptor_scene_gpu, matches);
    }
    catch(...){
        error_message = "matcher_gpu->match() failed.";
        return -2;
    }

    // get log informations
    matching_time_gpu = timer.elapsed();
    matches_number = matches.size();

    // extra step on gpu
    // download from device to host
    //
    // Note1: downloadKepoints() can be moved to detectAndDescribeGPU()
    //        this way download will occur just after computation
    //
    // Note 2: Be carefull to properly calcucalate time spend on memory trinsfer
    //          it might be overriden in one or other method
    timer.restart();
    try{
        surf_gpu.downloadKeypoints(keypoints_source_gpu, keypoints_source);
        surf_gpu.downloadKeypoints(keypoints_scene_gpu, keypoints_scene);
    }
    catch(...){
        error_message = "downloadKeypoints od gpu failed";
        return -3;
    }

    //surf_gpu.downloadDescriptors(descriptor_source_gpu, descriptor_source_downloaded);
    //surf_gpu.downloadDescriptors(descriptor_scene_gpu, descriptor_scene_downloaded);

    // other way to download descriptors from device to host
    try{
        descriptor_source = cv::Mat(descriptor_source_gpu);
        descriptor_scene = cv::Mat(descriptor_scene_gpu);
    }
    catch(...){
        error_message = "downloading descriptors from gpu failed";
        return -4;
    }

    // start geting log informations
    memory_download_time_gpu = timer.elapsed();

    keypoints_source_number = keypoints_source.size();
    keypoints_scene_number = keypoints_scene.size();

    descriptor_source_number_cols = descriptor_source.cols;
    descriptor_source_number_rows = descriptor_source.rows;

    descriptor_scene_number_cols = descriptor_scene.cols;
    descriptor_scene_number_rows = descriptor_scene.rows;
    // end geting log informations

    return 1;
}

int SurfLogic::calculateMinAndMaxDistance(){
    if(descriptor_source.rows <= 0){
        error_message = "calculateMinAndMaxDistance() failed. descriptor_source.rows = 0";
        return -1;
    }
    if(descriptor_source.rows != matches.size()){
        error_message = "calculateMinAndMaxDistance() failed. descriptor_source.rows != matches.size()";
        return -2;
    }

    for (int i = 0; i < descriptor_source.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    return 1;
}

int SurfLogic::filterMatches(){
    if(descriptor_source.rows <= 0){
        error_message = "filterMatches() failed. descriptor_source.row <= 0.";
        return -1;
    }

    if(matches.size() != descriptor_source.rows){
        error_message = "filterMatches() failed. matches.size() != descriptor_source.rows";
        return -1;
    }

    for (int i = 0; i < descriptor_source.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, good_matches_threshold))
        {
            good_matches.push_back(matches[i]);
        }
    }

    // get loging informations
    good_matches_number = good_matches.size();

    return 1;
}

int SurfLogic::drawKeyPointsAndMatches(){
    if(img_source.empty()) {
        error_message = "drawKeypointsAndMatches() failed. img_source is empty";
        return -1;
    }

    if(img_scene.empty()){
        error_message = "drawKeypointsAndMatches() failed. img_scene is empty";
        return -2;
    }

    if(keypoints_source.empty()){
        error_message = "drawKeypointsAndMatches() failed. keypoints_source is empty";
        return -3;
    }

    if(keypoints_scene.empty()){
        error_message = "drawKeypointsAndMatches() failed. keypoints_scene is empty";
        return -4;
    }

    if(good_matches.empty()){
        error_message = "drawKeypointsAndMatches() failed. good_matches is empty";
        return -5;
    }

    try{
        cv::drawMatches(img_source, keypoints_source, img_scene,keypoints_scene,
                    good_matches, img_processed, cv::Scalar::all(-1), cv::Scalar::all(-1),
                    vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    }
    catch(...){
        error_message = "drawKeyPointsAndMatches() failed becouse drawMatches() throw exception";
        return -6;
    }


    // display img_processed at this state
    // usefull while debugging
    // cv::imshow("conected matching points", img_processed);

    return 1;
}

void SurfLogic::localiseObject(){
    // declare corners
    //
    // corners are used to draw square around detected (localised) object
    vector<cv::Point2f> source_corners(4);
    vector<cv::Point2f> scene_corners(4);

    vector<cv::Point2f> obj;
    vector<cv::Point2f> scene;

    // set corners acording to width of source image,
    // assume that source image is left, scene image is right
    source_corners[0] = (cvPoint(0,0));                                 // top left
    source_corners[1] = (cvPoint(img_source.cols,0));                   // top right
    source_corners[2] = (cvPoint(img_source.cols, img_source.rows));    // botom right
    source_corners[3] = (cvPoint(0,img_source.rows));                   // botom left

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

void SurfLogic::writeLog(string type){
    // write and print log
    log = "";
    stringstream ss;

    ss << "Min hassian: " << min_hessian << endl;

    if(type == "cpu" || type == "Cpu" || type == "CPU"){

        ss << "Detect and describe keypoints: " << surf_time_cpu << "ms" << endl;
        ss << "Match keypoints: " << matching_time_cpu << "ms" << endl;
    }
    else{
        memory_total_time_gpu = memory_upload_time_gpu + memory_download_time_gpu;
        ss << "Memory transfer host->device->host: " << memory_total_time_gpu << "ms" << endl;
        ss << "Detect and describe keypoints: " << surf_time_gpu << "ms" << endl;
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

void SurfLogic::uploadImagesFromHostToDevuce(){
    timer.start();

    img_source_gpu.upload(img_source);
    img_scene_gpu.upload(img_scene);

    // get log information
    memory_upload_time_gpu = timer.elapsed();
}

void SurfLogic::freeCpuMemory(){
    img_source.release();
    img_scene.release();

    matcher_cpu.clear();;

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

void SurfLogic::freeGpuMemory(){
    img_source_gpu.release();
    img_scene_gpu.release();

    keypoints_source_gpu.release();
    keypoints_scene_gpu.release();

    descriptor_source_gpu.release();
    descriptor_scene_gpu.release();

    surf_gpu.releaseMemory();

    matcher_gpu.release();
}

void SurfLogic::createMatcherGpu(){
    matcher_gpu = cv::cuda::DescriptorMatcher::createBFMatcher(surf_gpu.defaultNorm());
}
