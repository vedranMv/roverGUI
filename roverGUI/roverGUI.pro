#-------------------------------------------------
#
# Project created by QtCreator 2017-03-12T00:33:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = roverGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cqtopencvviewergl.cpp \
    ocvgraph.cpp \
    roverinterface.cpp

HEADERS  += mainwindow.h \
    roverinterface.h \
    cqtopencvviewergl.h \
    ocvgraph.h

FORMS    += mainwindow.ui

INCLUDEPATH += /opt/ros/kinetic/include/opencv-3.2.0-dev
LIBS += -L/opt/ros/kinetic/lib -lopencv_stitching3 -lopencv_superres3 -lopencv_videostab3 -lopencv_aruco3 -lopencv_bgsegm3 -lopencv_bioinspired3 -lopencv_ccalib3 -lopencv_cvv3 -lopencv_datasets3 -lopencv_dpm3 -lopencv_face3 -lopencv_fuzzy3 -lopencv_hdf3 -lopencv_line_descriptor3 -lopencv_optflow3 -lopencv_plot3 -lopencv_reg3 -lopencv_saliency3 -lopencv_stereo3 -lopencv_structured_light3 -lopencv_phase_unwrapping3 -lopencv_rgbd3 -lopencv_viz3 -lopencv_surface_matching3 -lopencv_text3 -lopencv_xfeatures2d3 -lopencv_shape3 -lopencv_video3 -lopencv_ximgproc3 -lopencv_calib3d3 -lopencv_features2d3 -lopencv_flann3 -lopencv_xobjdetect3 -lopencv_objdetect3 -lopencv_ml3 -lopencv_xphoto3 -lopencv_highgui3 -lopencv_videoio3 -lopencv_imgcodecs3 -lopencv_photo3 -lopencv_imgproc3 -lopencv_core3

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

RESOURCES += \
    imgs.qrc
