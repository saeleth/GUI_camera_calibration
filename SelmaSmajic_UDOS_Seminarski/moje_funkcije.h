#ifndef MOJE_FUNKCIJE_H
#define MOJE_FUNKCIJE_H

#include "mainwindow.h"
#include "qlineedit.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <vector>
#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <algorithm>
#include <math.h>
#include <QAction>
#include "dimenzijedialog.h"
#include "choosetype.h"
#include "dimenzijedialogstereo.h"
#include <QtGui>
#include "imagedisplay.h"

using namespace cv;

std::vector<Mat> loadImagesFromDirectory(QString ime, QStringList &imena_slika);

#endif // MOJE_FUNKCIJE_H
