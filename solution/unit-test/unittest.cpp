#include "unittest.h"

#include "surflogic.h"
#include <QtTest>

UnitTest::UnitTest(QObject *parent) :
    QObject(parent)
{
}

void UnitTest::surfLogic_initDefaultValues(){
    // after execution of initDefaultValues()
    // it is expected all variables to have default values

    // 2 test cases
    // test 1: initialise variables on first start of the program.
    // test 2: variables are already initialised with non default values and
    //         we reset them do default one

    // setup
    SurfLogic model;

    // first verify that non of the variables alredy have expected values.
    // in this case the test makes no sense becouse we don't test anything
    QVERIFY(model.steps_number != 8);
    QVERIFY(model.min_hessian != 100);
    QVERIFY(model.good_matches_threshold != 0.2);

    QVERIFY(model.upright == false);
    QVERIFY(model.extended == false);

    QVERIFY(model.num_octaves != 4);
    QVERIFY(model.num_of_layers_per_octave != 2);

    // test case 1:
    //
    // after execution variables should have expected values
    model.initDefaultValues();

    QCOMPARE(model.steps_number, 8);
    QCOMPARE(model.min_hessian, 100);
    QCOMPARE(model.good_matches_threshold, 0.2);

    QCOMPARE(model.upright, false);
    QCOMPARE(model.extended, false);

    QCOMPARE(model.num_octaves, 4);
    QCOMPARE(model.num_of_layers_per_octave, 2);


    // test case 2:
    //
    // variables have non default values
    // after execution variables should have expected values
    model.steps_number = 5;
    model.min_hessian = -3;
    model.good_matches_threshold = 14.0;

    model.upright = true;
    model.extended = true;

    model.num_octaves = 5;
    model.num_of_layers_per_octave = 5;

    model.initDefaultValues();

    QCOMPARE(model.steps_number, 8);
    QCOMPARE(model.min_hessian, 100);
    QCOMPARE(model.good_matches_threshold, 0.2);

    QCOMPARE(model.upright, false);
    QCOMPARE(model.extended, false);

    QCOMPARE(model.num_octaves, 4);
    QCOMPARE(model.num_of_layers_per_octave, 2);
}

void UnitTest::surfLogic_resetMinAndMaxDistance(){
    // 2 testt cases:
    //
    // test case 1:
    // variables are uninitialised (initialise and set to default values)
    //
    // test case 2:
    // variables have random values (after execution they have expected values)

    // setup
    SurfLogic model;

    // test case 1:
//    QVERIFY(model.min_dist == 100.0);
//    QVERIFY(model.max_dist != 0.0);

    model.resetMinAndMaxDistance();
    QCOMPARE(model.min_dist, 100.0);
    QCOMPARE(model.max_dist, 0.0);

    // test case 2:
    model.min_dist = -650;
    model.max_dist = -650;

    model.resetMinAndMaxDistance();
    QCOMPARE(model.min_dist, 100.0);
    QCOMPARE(model.max_dist, 0.0);
}

void UnitTest::surfLogic_loadImages(){
    //Note 1: method work with two images, left(source) and right(scene)
    //Note 2: path to the image is stored as strings
    //Note 3: OpenCV is reading image from disk by its path (string)

    // 4 posible combinations
    // 1- source = good || scene == good || return 1
    // 2- source = good || scene == bad  || return -1
    // 3- source = bad  || scene == good || return -1
    // 4- source = bad  || scene == bad  || return -1

    // test criterion:
    //
    // Predicate Coverage:
    // at least once loadImages() == true
    // at least once loadImages() == false

    //setup
    SurfLogic model;
    int expected;
    int actual;

    // test case 1:
    //
    // source = good || scene = bad || return -1
    model.img_source_path = "/home/borche/bokiscout-object-detect/images/books-opencv/box.png";
    model.img_scene_path = "/";

    expected = -2;
    actual = model.loadImages();

    QVERIFY(expected == actual);

    // test case 2:
    //
    // source = bad || scene = good || return -1
    model.img_source_path = "/";
    model.img_scene_path = "/home/borche/bokiscout-object-detect/images/books-opencv/box.png";

    expected = -1;
    actual = model.loadImages();

    QVERIFY(expected == actual);

    // test case 3:
    //
    // source = good || scene = good || return 1
    model.img_source_path = "/home/borche/bokiscout-object-detect/images/books-opencv/box.png";
    model.img_scene_path  = "/home/borche/bokiscout-object-detect/images/books-opencv/box.png";

    expected = 1;
    actual = model.loadImages();

    QVERIFY(expected == actual);
}

void UnitTest::surfLogic_loadImagesMutantTest(){
    // test possible mutations

    // setup
    SurfLogic model;
    int data[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};
    model.img_source = cv::Mat(4,4, CV_8U, data);
    model.img_scene = cv::Mat(4,4, CV_8U, data);

    // test case 1:
    //
    // img_source = cv::imread(img_source_path, cv::IMREAD_GRAYSCALE);
    //
    // mutation at: img_source "=" ...
    model.img_source_path = "/home/borche/bokiscout-object-detect/images/books-opencv/box.png";
}

void UnitTest::surfLogic_createSurfCpu(){
    // the SURF pointer is not initialized by it self
    // we initialise it in this method
    //
    // also we pass min_hessian value as argument
    // so test should include that initialised method works acording to passed parameter

    // setup
    SurfLogic model;

    model.min_hessian = 100;
    model.upright = false;
    model.extended = false;
    model.num_octaves = 4;
    model.num_of_layers_per_octave = 2;

    // test that pointer is not initialised when program start
    // intialise it
    // then check if it is correctly initialised
    QCOMPARE(model.surf.empty(), true);

    model.createSurfCpu();

    QCOMPARE(model.surf.empty(), false);
    QCOMPARE(model.surf->getHessianThreshold(), 100.00);
    QCOMPARE(model.surf->getUpright(), false);
    QCOMPARE(model.surf->getExtended(), false);
    QCOMPARE(model.surf->getNOctaves(), 4);
    QCOMPARE(model.surf->getNOctaveLayers(), 2);
}

void UnitTest::surfLogic_createSurfCpuMutationTest(){
    // one posible mutation:
    //
    // mutation 1:
    // each variable to be exchanged by some other of same type
    //
    // other variable might have deferenr os same value as expected

    // Setup
    SurfLogic model;
    model.min_hessian = 150;
    model.upright = false;
    model.extended = false;
    model.num_octaves = 4;
    model.num_of_layers_per_octave = 2;

    int expected;
    int actual;

    // test case 1:
    model.createSurfCpu();

    QCOMPARE(model.surf.empty(), false);
    QCOMPARE(model.surf->getHessianThreshold(), model.min_hessian * 1.0);
    QCOMPARE(model.surf->getUpright(), model.upright);
    QCOMPARE(model.surf->getExtended(), model.extended);
    QCOMPARE(model.surf->getNOctaves(), model.num_octaves);
    QCOMPARE(model.surf->getNOctaveLayers(), model.num_of_layers_per_octave);
}

void UnitTest::surfLogic_createSurfGpu(){
    // SURF on GPU is not declared as pointer as on CPU
    // it is plain method thet accepts few arguments
    //
    // test if SURF is created with expected values passed via parameters

    // setup
    SurfLogic model;

    model.min_hessian = 100;
    model.upright = false;
    model.extended = false;
    model.num_octaves = 4;
    model.num_of_layers_per_octave = 2;

    // test
    model.createSurfGpu();

    QCOMPARE(model.surf_gpu.hessianThreshold, model.min_hessian * 1.0);
    QCOMPARE(model.surf_gpu.upright, model.upright);
    QCOMPARE(model.surf_gpu.extended, model.extended);
    QCOMPARE(model.surf_gpu.nOctaves, model.num_octaves);
    QCOMPARE(model.surf_gpu.nOctaveLayers, model.num_of_layers_per_octave);
}

void UnitTest::surfLogic_createSurfGpuMutationTest(){
    // only one mutation posible
    //
    // if other variable is used instad of min_hessian

    // Setup
    SurfLogic model;
    model.min_hessian = 250;
    int expected;
    int actual;

    // test case 1:
    model.createSurfGpu();

    expected = 250;
    actual = model.surf_gpu.hessianThreshold;

    QCOMPARE(actual, expected);
}

void UnitTest::surfLogic_detectAndDescribeCPU(){
    // detectAndDescribe() return 1 if sucessfull, otherwise -1.
    //
    // if not sucessfull error_message is created

    // if 1 is returned -> source and scene images are ok
    // if -1 is returned -> at least one of source or scene image isn't ok

    // three test are provided
    // test 1 - detectAndDescribe = 1
    // test 2 - detectAndDescribe = -1 and source is bad
    // test 3 - detectAndDescribe = -1 and scene is bad

    // setup
    SurfLogic model;

    int expected;
    int actual;
    model.min_hessian = 100;
    int data[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};
    model.createSurfCpu();

    // test 1
    //
    // detectAndDescribe = 1
    model.img_source = cv::Mat(4,4, CV_8U, data);
    model.img_scene = cv::Mat(4,4, CV_8U, data);

    expected = 1;
    actual = model.detectAndDescribeCPU();

    QCOMPARE(expected, actual);

    // test 2
    //
    // detectAndDescribe = -1 and source isnt' ok
    model.img_source = cv::Mat();
    model.img_scene = cv::Mat(4,4, CV_8U, data);

    expected = -1;
    actual = model.detectAndDescribeCPU();

    QCOMPARE(actual, expected);

    // test 3
    //
    // detectAndDescribe = -1 and scene isn't ok
    model.img_source = cv::Mat(4,4, CV_8U, data);
    model.img_scene = cv::Mat();

    expected = -1;
    actual = model.detectAndDescribeCPU();

    QCOMPARE(expected, actual);
}

void UnitTest::surfLogic_detectAndDescribeCPUMutationTest(){
    // two possible mutations
    //
    // mutation 1:
    // img_scene is replaced with image_source
    //
    // mutation 2:
    // image_source is replaced with image_scene

    // setup
    SurfLogic model;
    int expected;
    int actual;

    bool expected_boool;
    bool actual_bool;

    model.min_hessian = 100;
    int data_source[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};
    int data_scene[] = {20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                       20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10};
    model.createSurfCpu();

    // test mutation 1:
    //
    // if(img_source.empty() || img_scene.empty())
    model.img_source = cv::Mat(4,4, CV_8U, data_source);
    model.img_scene = cv::Mat();

    expected = -1;
    actual = model.detectAndDescribeGPU();

    QCOMPARE(actual, expected);

    // test mutation 2:
    //
    // if(img_source.empty() || img_scene.empty()){
    model.img_source = cv::Mat();
    model.img_scene = cv::Mat(4,4, CV_8U, data_scene);

    expected = -1;
    actual = model.detectAndDescribeCPU();

    QCOMPARE(actual, expected);

//    // test mutation 3:
//    //
//    // surf->detectAndCompute(img_source, cv::noArray(), keypoints_source, descriptor_source, false);
//    model.img_source = cv::Mat(5,5, CV_8U, data_source);
//    model.img_scene = cv::Mat(7,7, CV_8U, data_scene);

//    model.detectAndDescribeCPU();

//    actual_bool = (model.keypoints_source.size() == model.keypoints_scene.size());
//    QVERIFY(actual_bool == false);
}

void UnitTest::surfLogic_detectAndDescribeGPU(){
    // don't fail even when surf_gpu isn't initialised
    // don't fail even when soure and scene are not initialised
    //
    // we should test for wrong values only

    // anyway we do more tests
    //
    // test 1: source = bad  || scene = good || return = -1
    // test 2: source = good || scene = bad  || return = -1
    // test 3: source = good || scene = good || return = 1

    // setup
    SurfLogic model;
    int expected;
    int actual;
    model.min_hessian = 100;
    int data[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};

    // test case 1:
    //
    // source = bad  || scene = good || return = -1
    model.img_source_gpu = cv::cuda::GpuMat();
    model.img_scene_gpu = cv::cuda::GpuMat(4,4, CV_8U, data);

    expected = -1;
    actual = model.detectAndDescribeGPU();

    QVERIFY(expected == actual);

    // test case 2:
    //
    // source = good || scene = bad  || return = -1
    model.img_source_gpu = cv::cuda::GpuMat(4,4, CV_8U, data);
    model.img_scene_gpu = cv::cuda::GpuMat();

    expected = -1;
    actual = model.detectAndDescribeGPU();

    QVERIFY(expected == actual);

//    // test case 3:
//    //
//    // source = good || scene = bad || return = 1
//    int data_source[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};
//    int data_scene[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
//                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};

//    model.img_source_gpu = cv::cuda::GpuMat(80,150, CV_8U, data_source);
//    model.img_scene_gpu = cv::cuda::GpuMat(150,200, CV_8U, data_scene);

//    expected = 1;
//    actual = model.detectAndDescribeGPU();

//    QCOMPARE(actual, expected);
}

void UnitTest::surfLogic_detectAndDescribeGPUMutation(){
    // two possible mutations
    //
    // mutation 1:
    // img_scene is replaced with image_source
    //
    // mutation 2:
    // image_source is replaced with image_scene

    // setup
    SurfLogic model;
    int expected;
    int actual;

    model.min_hessian = 100;
    int data_source[] = {10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255,
                        10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255, 10, 2, 5, 255};
    int data_scene[] = {20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                        20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10,
                       20, 20, 50, 10, 255, 2, 255, 5, 10, 5, 2, 255, 255, 5, 2, 10};
    model.createSurfGpu();

    // test mutation 1
    //
    // if(img_source_gpu.empty() || img_scene_gpu.empty()){}
    model.img_source = cv::Mat(4,4, CV_8U, data_source);
    model.img_scene = cv::Mat();

    expected = -1;
    actual = model.detectAndDescribeGPU();

    QCOMPARE(actual, expected);

    // test mutation 2
    //
    // if(img_source_gpu.empty() || img_scene_gpu.empty()){}
    model.img_source = cv::Mat();
    model.img_scene = cv::Mat(4,4, CV_8U, data_source);

    expected = -1;
    actual = model.detectAndDescribeGPU();

    QCOMPARE(actual, expected);
}

void UnitTest::surfLogic_runMatcherCPU(){
    // matches is reading from descriptor_source and descriptor_scene
    // then matches keypoints and result is stored in vector<> matches

    // possible fails:
    // 1: descriptor_source = bad  || descriptor_scene = ok  || result = -1
    // 2: descriptor_source = good || descriptor_scene = bad || result = -1
    //
    // actualy it won't fail even when descriptors aren't initialised

    // setup
    SurfLogic model;
    int actual;
    int expected;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};

    // test 1:
    //
    // source = bad || scene = ok || result = 1
    model.descriptor_source = cv::Mat();
    model.descriptor_scene = cv::Mat(5, 5, CV_8U, data);

    expected = -1;
    actual = model.runMatcherCPU();

    QVERIFY(expected == actual);

    // test 2:
    //
    // source = good || scene = bad || result = -1
    model.descriptor_source = cv::Mat(5, 5, CV_8U, data);
    model.descriptor_scene = cv::Mat();

    expected = -1;
    actual = model.runMatcherCPU();

    QVERIFY(expected == actual);

    // test 3:
    //
    // source = good || scene = good || result = 1
    model.descriptor_source = cv::Mat(5, 5, CV_8U, data);
    model.descriptor_scene = cv::Mat(5, 5, CV_8U, data);

    expected = 1;
    actual = model.runMatcherCPU();

    QVERIFY(expected == actual);
}

void UnitTest::surfLogic_runMatcherCPUMutation(){
    SurfLogic model;
    int actual;
    int expected;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};


    // test mutation 1
    //
    // if source is tested twice -> cought
    // if scene is teted twise -> cought
    // if || is changed with && -> cought
    model.descriptor_source = cv::Mat(5, 5, CV_8U, data);
    model.descriptor_scene = cv::Mat();

    actual = model.runMatcherCPU();
    expected = -1;
    QCOMPARE(actual, expected);

//    // test mutation 2
//    // if soruce is swapped with scene or wise wersa
//    model.img_source_path = "/home/borche/bokiscout-object-detect/images/books-opencv/box.png";
//    model.img_scene_path  = "/home/borche/bokiscout-object-detect/images/books-opencv/box_in_scene.png";

//    model.loadImages();
//    model.createSurfCpu();
//    model.detectAndDescribeCPU();

//    model.runMatcherCPU();

//    int matches = model.matches.size(); // good
//    int source_size = model.keypoints_source_number;
//    int scene_size = model.keypoints_scene_number;

//    bool expected_bool = false;
//    bool actual_bool = (matches == source_size && matches);

//    QCOMPARE(actual_bool, expected_bool);
}

void UnitTest::surfLogic_runMatcherGPU(){
    // matcher_gpu is defined as pointer
    // need to be initialised before usage

    // posible fails:
    // descriptors_source_gpu is empty
    // descriptors_scene_gpu is empty
    // GPU kernel throw error

    // setup
    SurfLogic model;
    int actual;
    int expected;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};

    model.createMatcherGpu();

    // test casse 1:
    //
    // source = good || scene = bad || result = -1
    model.descriptor_source_gpu = cv::cuda::GpuMat(5, 5, CV_8U, data);
    model.descriptor_scene_gpu = cv::cuda::GpuMat();

    expected = -1;
    actual = model.runMatcherGPU();

    QVERIFY2(expected == actual, qPrintable(model.error_message));

    // test case 2:
    //
    // source = bad || scene = good || result = -1;
    model.descriptor_source_gpu = cv::cuda::GpuMat();
    model.descriptor_scene_gpu = cv::cuda::GpuMat(5, 5, CV_8U, data);

    expected = -1;
    actual = model.runMatcherGPU();

    QVERIFY2(expected == actual, qPrintable(model.error_message));
}

void UnitTest::surfLogic_runMatcherGPUMutation(){
    // setup

    SurfLogic model;
    int actual;
    int expected;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};

    model.createMatcherGpu();

    // test mutant 1:
    // || is changed to &&
    model.descriptor_source_gpu = cv::cuda::GpuMat(5, 5, CV_8U, data);
    model.descriptor_scene_gpu = cv::cuda::GpuMat();

    actual = model.runMatcherGPU();
    expected = -1;

    QCOMPARE(actual, expected);

    // test mutant 1:
    // || is changed to &&
    model.descriptor_source_gpu = cv::cuda::GpuMat();
    model.descriptor_scene_gpu = cv::cuda::GpuMat(5, 5, CV_8U, data);

    actual = model.runMatcherGPU();
    expected = -1;

    QCOMPARE(actual, expected);

//    // test mutant 1:
//    // || is changed to &&
//    model.descriptor_source_gpu = cv::cuda::GpuMat(5, 5, CV_8U, data);
//    model.descriptor_scene_gpu = cv::cuda::GpuMat(5, 5, CV_8U, data);

//    actual = model.runMatcherGPU();
//    expected = 1;

//    QCOMPARE(actual, expected);

    // test mutant 1:
    // || is changed to &&
    model.descriptor_source_gpu = cv::cuda::GpuMat();
    model.descriptor_scene_gpu = cv::cuda::GpuMat();

    actual = model.runMatcherGPU();
    expected = -1;

    QCOMPARE(actual, expected);
}

void UnitTest::surfLogic_calculateMinAndMaxDistance(){
    // Note 1:
    // matches[] length is equal to descriptor_source.rows
    // That is how SURF works

    // Note 2:
    // disatnces have values from 0 to 100

    // posibile fails
    // 1. min default is very small negative number so can't find actual smallest
    // 2. max default is very large positive number so can't find actual largest
    // 3. descriptor_source.rows is 0
    // 4. descriptor_source.rows is 1
    // 5. descriptor_source.rows != matches.size()
    // 6. wrong calculation of min and max

    // test cases
    // 1. all values are 0. Find min and max from 0s
    // 2. mixed values from 0 to 100. Find min and max among them.

    // setup
    SurfLogic model;
    int expected;
    int actual;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};

    cv::DMatch first = cv::DMatch(1,1,0.1);
    cv::DMatch second = cv::DMatch(1,1,0.2);
    cv::DMatch third = cv::DMatch(1,1,0.4);
    cv::DMatch fourth = cv::DMatch(1,1,0.8);
    cv::DMatch fifth = cv::DMatch(1,1,0.6);

    vector<cv::DMatch> vectormatches;

    model.descriptor_source = cv::Mat(5,5, CV_8U, data);

    // test 1 and 2:
    //
    // verify that method that is reseting min and max values is doing it fine
    model.resetMinAndMaxDistance();
    QVERIFY2(model.min_dist >= 100, "resetMinAndMaxDistance() is seting min_dist too low");
    QVERIFY2(model.max_dist <= 0,   "resetMinAndMaxDistance() is seting max_dist too high");

    // test 3:
    //
    // descriptor_source.rows is 0
    model.descriptor_source = cv::Mat(0,0, CV_8U);
    expected = -1;
    actual = model.calculateMinAndMaxDistance();

    QVERIFY2(expected == actual, qPrintable(model.error_message));

    // test 5:
    //
    // escriptor_source.rows != matches.size()
    model.descriptor_source = cv::Mat(5,5, CV_8U, data);

    vectormatches.push_back(first);
    vectormatches.push_back(second);
    model.matches = vectormatches;

    expected = -2;
    actual = model.calculateMinAndMaxDistance();

    QVERIFY2(expected == actual, qPrintable(model.error_message));

    // test 6
    //
    // verify that min and max values are properly found
    model.descriptor_source = cv::Mat(5,5, CV_8U, data);

    vectormatches.clear();
    vectormatches.push_back(first);
    vectormatches.push_back(second);
    vectormatches.push_back(third);
    vectormatches.push_back(fourth);
    vectormatches.push_back(fifth);

    model.matches = vectormatches;

    expected = 1;
    actual = model.calculateMinAndMaxDistance();

    // verify that method return 1
    QVERIFY2(expected == actual, "calculateMinAndMaxDistance() failed on correct input");

    float expected_min = 0.1;
    float expected_max = 0.8;

    float actual_min = model.min_dist;
    float actual_max = model.max_dist;

    // verify that min and max ar properly found
    QVERIFY2(expected_min == actual_min, "calculateMinAndMaxDistance() failed. Expected min_dist != actual min_dist");
    QVERIFY2(expected_max == actual_max, "calculateMinAndMaxDistance() failed. Expected min_dist != actual min_dist");
}

void UnitTest::surfLogic_calculateMinAndMaxDistanceMutation(){
    // mutation 1:
    //
    // if(descriptor_source.rows <= 0){}

    // mutation 2:
    //
    // if(descriptor_source.rows != matches.size()){}

    // setup
    SurfLogic model;
    int expected;
    int actual;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};

    cv::DMatch first = cv::DMatch(1,1,0.1);
    cv::DMatch second = cv::DMatch(1,1,0.2);
    cv::DMatch third = cv::DMatch(1,1,0.4);
    cv::DMatch fourth = cv::DMatch(1,1,0.8);
    cv::DMatch fifth = cv::DMatch(1,1,0.6);

    vector<cv::DMatch> vectormatches;

    // test  mutation 1
    //
    // <= is changed with <
    model.descriptor_source = cv::Mat(0,0, CV_8U, data);

    actual = model.calculateMinAndMaxDistance();
    expected = -1;

    QCOMPARE(actual, expected);

    // test mutation 1:
    //
    // <= is changed with ==
    model.descriptor_source = cv::Mat(0,0, CV_8U, data);

    actual = model.calculateMinAndMaxDistance();
    expected = -1;

    QCOMPARE(actual, expected);

    // test mutation 1:
    //
    // <= is changed with >=
    model.descriptor_source = cv::Mat(5,5, CV_8U, data);

    vectormatches.clear();
    vectormatches.push_back(first);
    vectormatches.push_back(second);
    vectormatches.push_back(third);
    vectormatches.push_back(fourth);
    vectormatches.push_back(fifth);

    model.matches = vectormatches;

    actual = model.calculateMinAndMaxDistance();
    expected = 1;

    QCOMPARE(actual, expected);

    // test mutation 2:
    //
    // != is changed with ==
    model.descriptor_source = cv::Mat(5,5, CV_8U, data);

    vectormatches.clear();
    vectormatches.push_back(first);
    vectormatches.push_back(second);
    vectormatches.push_back(third);
    vectormatches.push_back(fourth);
    vectormatches.push_back(fifth);

    model.matches = vectormatches;

    actual = model.calculateMinAndMaxDistance();
    expected = 1;

    QCOMPARE(actual, expected);

    // test mutation 2:
    //
    // != is changed with <=
    model.descriptor_source = cv::Mat(5,5, CV_8U, data);

    vectormatches.clear();
    vectormatches.push_back(first);
    vectormatches.push_back(second);
    vectormatches.push_back(third);
    vectormatches.push_back(fourth);
    vectormatches.push_back(fifth);

    model.matches = vectormatches;

    actual = model.calculateMinAndMaxDistance();
    expected = 1;

    QCOMPARE(actual, expected);
}

void UnitTest::surfLogic_filterMatches(){
    // posible fails:
    //
    // 1. descriptor_source.rows = 0
    // 2. descriptor_source.rows = 1
    // 3. matches.size != descriptor_source.rows
    // 4. wrong filtering, not finding the one that should be found

    // setup
    SurfLogic model;
    int expected;
    int actual;
    int data[] = {5, 10, 15, 20, 25,
                  30, 35, 40, 45, 50,
                  55, 60, 70, 75, 80,
                  90, 100, 150, 250, 200,
                  95, 105, 155, 255, 205};

    cv::DMatch first = cv::DMatch(1,1,0.1);
    cv::DMatch second = cv::DMatch(1,1,0.2);
    cv::DMatch third = cv::DMatch(1,1,0.4);
    cv::DMatch fourth = cv::DMatch(1,1,0.8);
    cv::DMatch fifth = cv::DMatch(1,1,0.6);

    vector<cv::DMatch> vectormatches;

    // test 1
    //
    // descriptor_source = 0;
    model.descriptor_source = cv::Mat();
    model.matches = vectormatches;

    expected = -1;
    actual = model.filterMatches();

    QVERIFY2(expected == actual, "filterMatches() failed. descriptor_source.rows = 0");


    // test 3:
    //
    // match.size != description_sourcerows
    model.descriptor_source = cv::Mat(5, 5, CV_8U, data);

    vectormatches.clear();
    vectormatches.push_back(first);
    vectormatches.push_back(second);

    model.matches = vectormatches;

    expected = -1;
    actual = model.filterMatches();

    QVERIFY2(expected == actual, "filterMatches() failed. descriptor_source.rows != matches.size()");

    // test 4:
    //
    // wrong filtering, not finding the one that should be found
    model.descriptor_source = cv::Mat(5, 5, CV_8U, data);

    vectormatches.clear();
    vectormatches.push_back(first);
    vectormatches.push_back(second);
    vectormatches.push_back(third);
    vectormatches.push_back(fourth);
    vectormatches.push_back(fifth);

    model.matches = vectormatches;

    // call method for calculating minimal and maximal distances
    model.calculateMinAndMaxDistance();
    model.good_matches_threshold = 0.2;

    expected = 1;
    actual = model.filterMatches();

    // verify that method return 1
    QVERIFY2(expected == actual, "filterMatches() failed. return -1 when executed with good values");

    // verify that method have calculated right values
    int expected_good_matches = 2;
    int actual_good_matches = model.good_matches_number;

    QVERIFY2(expected_good_matches == actual_good_matches, "filterMatches() failed. good matches aren't filtered properly");
    qDebug() << qPrintable(QString::number(expected_good_matches));
    qDebug() << qPrintable(QString::number(actual_good_matches));
}

void UnitTest::surfLogic_drawKeyPointsAndMatches(){
    // posible fails:
    //
    // 1. source_image is missing or empty
    // 2. scene_image is missing or empty
    // 3. keypoints_source is missing or empty
    // 4. keypoints_scene is missing or empty
    // 5. good_matches is missing or empty

    // setup
    SurfLogic model;

    int expected;
    int actual;

    int data[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
                 60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    // test 1:
    //
    // img_source is missing or empty
    model.img_source = cv::Mat();

    expected = -1;
    actual = model.drawKeyPointsAndMatches();

    QVERIFY2(expected == actual, qPrintable(QString(model.error_message)));

    // test 2:
    //
    // scene is missing or empty
    model.img_source = cv::Mat(5,5, CV_8U, cv::Scalar(255));
    model.img_scene = cv::Mat();

    expected = -2;
    actual = model.drawKeyPointsAndMatches();

    QVERIFY2(expected == actual, qPrintable(QString(model.error_message)));

    // test 3:
    //
    // keypoints_source is missing or empty
    model.img_source = cv::Mat(5,5, CV_8U, cv::Scalar(255));
    model.img_scene = cv::Mat(5,5, CV_8U, cv::Scalar(255));

    model.keypoints_source = vector<cv::KeyPoint>();

    expected = -3;
    actual = model.drawKeyPointsAndMatches();

    QVERIFY2(actual == expected, qPrintable(QString(model.error_message)));

    // test 4:
    //
    // keypoints_scene is missing or empty
    model.img_source = cv::Mat(5,5, CV_8U, cv::Scalar(255));
    model.img_scene = cv::Mat(5,5, CV_8U, cv::Scalar(255));

    cv::KeyPoint point_first = cv::KeyPoint(1, 1, 1.3);
    cv::KeyPoint point_second = cv::KeyPoint(1, 1, 1.3);

    model.keypoints_source = vector<cv::KeyPoint>();
    model.keypoints_scene = vector<cv::KeyPoint>();

    model.keypoints_source.push_back(point_first);
    model.keypoints_source.push_back(point_second);

    expected = -4;
    actual = model.drawKeyPointsAndMatches();

    QVERIFY2(expected == actual, qPrintable(QString(model.error_message)));

    // test 5:
    //
    // good_matches is missing or empty
    model.img_source = cv::Mat(5,5, CV_8U, cv::Scalar(255));
    model.img_scene = cv::Mat(5,5, CV_8U, cv::Scalar(255));

    point_first = cv::KeyPoint(1, 1, 1.3);
    point_second = cv::KeyPoint(1, 1, 1.3);

    model.keypoints_source = vector<cv::KeyPoint>();
    model.keypoints_scene = vector<cv::KeyPoint>();

    model.keypoints_source.push_back(point_first);
    model.keypoints_source.push_back(point_second);

    model.keypoints_scene.push_back(point_first);
    model.keypoints_scene.push_back(point_second);

    model.good_matches = vector<cv::DMatch>();

    expected = -5;
    actual = model.drawKeyPointsAndMatches();

    QVERIFY(actual == expected);

    // test 6:
    //
    // method is executed without error
    model.img_source = cv::Mat(5,5, CV_8U, cv::Scalar(255));
    model.img_scene = cv::Mat(5,5, CV_8U, cv::Scalar(255));

    point_first = cv::KeyPoint(1, 1, 1.3);
    point_second = cv::KeyPoint(1, 1, 1.3);

    model.keypoints_source = vector<cv::KeyPoint>();
    model.keypoints_scene = vector<cv::KeyPoint>();

    model.keypoints_source.push_back(point_first);
    model.keypoints_source.push_back(point_second);

    model.keypoints_scene.push_back(point_first);
    model.keypoints_scene.push_back(point_second);

    cv::DMatch match_first = cv::DMatch(1, 1, 0.3);
    cv::DMatch match_second = cv::DMatch(1, 1, 0.4);
    cv::DMatch match_third = cv::DMatch(1, 1, 0.6);
    cv::DMatch match_fourth = cv::DMatch(1, 1, 0.8);

    model.good_matches = vector<cv::DMatch>();

    model.good_matches.push_back(match_first);
    model.good_matches.push_back(match_second);
    model.good_matches.push_back(match_third);
    model.good_matches.push_back(match_fourth);

    expected = 1;
    actual = model.drawKeyPointsAndMatches();

    QVERIFY(expected == actual);
    QVERIFY(model.img_processed.empty() == false);
}

void UnitTest::surfLogic_localiseObject(){
    // posible failures
    //
    // good_matches is empty

}
