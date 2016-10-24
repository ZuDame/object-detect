#ifndef UNITTEST_H
#define UNITTEST_H

#include <QObject>

class UnitTest : public QObject
{
    Q_OBJECT
public:
    explicit UnitTest(QObject *parent = 0);

signals:

public slots:

private slots:
    // test initialisation of default values
    void surfLogic_initDefaultValues();

    // test if min and max values are reseted properly
    void surfLogic_resetMinAndMaxDistance();

    // test OpenCV loading images by it's path
    void surfLogic_loadImages();
    void surfLogic_loadImagesMutantTest();

    // test initialisation of SURF kernel on CPU
    void surfLogic_createSurfCpu();
    void surfLogic_createSurfCpuMutationTest();

    // test initialisation of SURF kernel on GPU
    void surfLogic_createSurfGpu();
    void surfLogic_createSurfGpuMutationTest();

    // test detect and describe of SURF on CPU
    void surfLogic_detectAndDescribeCPU();
    void surfLogic_detectAndDescribeCPUMutationTest();

    // test detect and describe if SURF on GPU
    void surfLogic_detectAndDescribeGPU();
    void surfLogic_detectAndDescribeGPUMutation();

    // test matching of keypoints on CPU
    void surfLogic_runMatcherCPU();
    void surfLogic_runMatcherCPUMutation();

    // test matching of keypoints on GPU
    void surfLogic_runMatcherGPU();
    void surfLogic_runMatcherGPUMutation();

    // test calculation of minimal and maximal distance
    // between matched keypoints
    void surfLogic_calculateMinAndMaxDistance();
    void surfLogic_calculateMinAndMaxDistanceMutation();

    // test filtering good matches from all matches
    void surfLogic_filterMatches();

    // test drawing keypoints and matches
    //
    // joint source and scene image
    // draw key points
    // draw lines between matching keypoints
    void surfLogic_drawKeyPointsAndMatches();

    // test localisation of object
    void surfLogic_localiseObject();

};

#endif // UNITTEST_H
