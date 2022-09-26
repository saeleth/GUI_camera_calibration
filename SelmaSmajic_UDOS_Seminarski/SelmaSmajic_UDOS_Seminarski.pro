QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += C:\OpenCV\opencv\build\include

LIBS += C:\OpenCV\opencv\release\bin\libopencv_core455.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_highgui455.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_imgcodecs455.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_imgproc455.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_calib3d455.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_video455.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_videoio455.dll

SOURCES += \
    choosetype.cpp \
    dimenzijedialog.cpp \
    dimenzijedialogstereo.cpp \
    imagedisplay.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    choosetype.h \
    dimenzijedialog.h \
    dimenzijedialogstereo.h \
    imagedisplay.h \
    mainwindow.h \
    moje_funkcije.h

FORMS += \
    choosetype.ui \
    dimenzijedialog.ui \
    dimenzijedialogstereo.ui \
    imagedisplay.ui \
    mainwindow.ui

TRANSLATIONS += \
    SelmaSmajic_UDOS_Seminarski_bs_BA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
