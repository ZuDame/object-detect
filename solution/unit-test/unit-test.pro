#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T04:28:14
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = unit-test
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += testcase

TEMPLATE = app


SOURCES += main.cpp \
    unittest.cpp

HEADERS += \
    unittest.h

#########################################################
#                                                      `#
#           pass arguments to enable gcov loging        #
#                                                       #
#########################################################
#QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0

#QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0
#LIBS += -lgcov

#########################################################
#                                                      `#
#             Link the static library                   #
#                                                       #
#########################################################

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-solution-Desktop-Debug/busines-logic/release/ -lbusines-logic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-solution-Desktop-Debug/busines-logic/debug/ -lbusines-logic
else:unix: LIBS += -L$$PWD/../../build-solution-Desktop-Debug/busines-logic/ -lbusines-logic

INCLUDEPATH += $$PWD/../busines-logic
DEPENDPATH += $$PWD/../busines-logic

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-solution-Desktop-Debug/busines-logic/release/libbusines-logic.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-solution-Desktop-Debug/busines-logic/debug/libbusines-logic.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-solution-Desktop-Debug/busines-logic/release/busines-logic.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-solution-Desktop-Debug/busines-logic/debug/busines-logic.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../build-solution-Desktop-Debug/busines-logic/libbusines-logic.a


#########################################################
#                                                      `#
#   Include OpenCV-3.1 libraries on Ubuntu-14.04        #
#                                                       #
#########################################################
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_cudabgsegm -lopencv_cudaobjdetect -lopencv_cudastereo -lopencv_stitching -lopencv_cudafeatures2d -lopencv_superres -lopencv_cudacodec -lopencv_videostab -lopencv_cudaoptflow -lopencv_cudalegacy -lopencv_cudawarping -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_cvv -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_viz -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_photo -lopencv_imgcodecs -lopencv_cudaimgproc -lopencv_cudafilters -lopencv_imgproc -lopencv_cudaarithm -lopencv_core -lopencv_cudev


#########################################################
#                                                      `#
#   Include OpenCV-3.1 librarues on Windows10           #
#                                                       #
#########################################################
#INCLUDEPATH +=C:\\opencv-3.1.0\\my_build\\install\include
#LIBS += -LC:\\opencv-3.1.0\\my_build\\lib\\Debug\
#-lopencv_ccalib310d \
#-lopencv_core310d \
#-lopencv_cudaarithm310d \
#-lopencv_cudabgsegm310d \
#-lopencv_cudacodec310d \
#-lopencv_cudafeatures2d310d \
#-lopencv_cudafilters310d \
#-lopencv_cudaimgproc310d \
#-lopencv_cudalegacy310d \
#-lopencv_cudaobjdetect310d \
#-lopencv_cudaoptflow310d \
#-lopencv_cudastereo310d \
#-lopencv_cudawarping310d \
#-lopencv_cudev310d \
#-lopencv_datasets310d \
#-lopencv_dnn310d \
#-lopencv_dpm310d \
#-lopencv_face310d \
#-lopencv_features2d310d \
#-lopencv_flann310d \
#-lopencv_fuzzy310d \
#-lopencv_highgui310d \
#-lopencv_imgcodecs310d \
#-lopencv_imgproc310d \
#-lopencv_line_descriptor310d \
#-lopencv_ml310d \
#-lopencv_objdetect310d \
#-lopencv_optflow310d \
#-lopencv_photo310d \
#-lopencv_plot310d \
#-lopencv_reg310d \
#-lopencv_rgbd310d \
#-lopencv_saliency310d \
#-lopencv_shape310d \
#-lopencv_stereo310d \
#-lopencv_stitching310d \
#-lopencv_structured_light310d \
#-lopencv_superres310d \
#-lopencv_surface_matching310d \
#-lopencv_text310d \
#-lopencv_tracking310d \
#-lopencv_ts310d \
#-lopencv_video310d \
#-lopencv_videoio310d \
#-lopencv_xfeatures2d310d \
#-lopencv_ximgproc310d \
#-lopencv_xobjdetect310d \
#-lopencv_xphoto310d \
#-lopencv_aruco310d \
#-lopencv_bgsegm310d \
#-lopencv_calib3d310d
