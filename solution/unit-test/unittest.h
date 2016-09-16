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

    // test initialisation of SURF kernel on CPU
    void surfLogic_createSurfCpu();

    // test initialisation of SURF kernel on GPU
    void surfLogic_createSurfGpu();

    // test detect and describe if SURF on CPU
    void surfLogic_detectAndDescribeCPU();

    // test detect and describe if SURF on GPU
    void surfLogic_detectAndDescribeGPU();

    // test matching of keypoints on CPU
    void surfLogic_runMatcherCPU();

    // test matching of keypoints on GPU
    void surfLogic_runMatcherGPU();

    // test calculation of minimal and maximal distance
    // between matched keypoints
    void surfLogic_calculateMinAndMaxDistance();

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
