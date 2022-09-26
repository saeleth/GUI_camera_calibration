#include "imagedisplay.h"
#include "qboxlayout.h"
#include "qmessagebox.h"
#include "ui_imagedisplay.h"
#include "QCheckBox"
#include "qcheckbox.h"
#include "moje_funkcije.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>


using namespace cv;

std::vector<Mat> loadImagesFromDirectory(QString ime, QStringList &imena_slika) {
    QDir directory(ime);
    QStringList file_name = directory.entryList(QStringList() << "*.bmp" << "*.BMP", QDir::Files);
    imena_slika = file_name;
    std::vector<Mat> files_img;
    std::vector<std::string> vec;
    foreach(QString str, file_name) {
        vec.push_back(str.toStdString());
    }

    for(int i=0; i<file_name.length(); i++) {
        std::string path = vec.at(i);
        std::string ime_novo = ime.toStdString();
        Mat slika = imread(ime_novo+path, IMREAD_COLOR);
        files_img.push_back(slika);
    }
    return files_img;
}


imageDisplay::imageDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageDisplay)
{
    ui->setupUi(this);

    setMinimumSize(100,100);

    QLabel *MainLabel = new QLabel(this);
    QVBoxLayout *MainLayout = new QVBoxLayout(this);
    MainLayout->addWidget(MainLabel);
    QVBoxLayout* VerFramesLayout = new QVBoxLayout(MainLabel);
    // this->setLayout(VerFramesLayout);
    ui->scrollArea->setLayout(VerFramesLayout);
    ui->scrollAreaWidgetContents->setLayout(VerFramesLayout);
    VerFramesLayout->setStretch(0, 2);
    //  ui->scrollArea->verticalScrollBar()->setLayout(VerFramesLayout);

  //  QList<QPixmap> PixList;
    QStringList imena_slika;
    std::vector<Mat> slike = loadImagesFromDirectory("img/", imena_slika);

    foreach(QString ime, imena_slika){
        // stavljaj slicice, njihov naziv, i checkbox u svakoj iteraciji
        QImage image("img/"+ime);
        QImage newImage = image.scaled(150, 150, Qt::KeepAspectRatio);
        QPixmap pix = QPixmap::fromImage(newImage);

        QLabel *PixLabel = new QLabel(MainLabel);
        PixLabel->setScaledContents(false);
        PixLabel->setPixmap(pix);
        VerFramesLayout->addWidget(PixLabel);

        QLabel *naziv_slike = new QLabel(MainLabel);
        naziv_slike->setText(ime);
        VerFramesLayout->addWidget(naziv_slike);

        QCheckBox *cekiraj = new QCheckBox(MainLabel);
        VerFramesLayout->addWidget(cekiraj);
    }

//    foreach(QPixmap pix, PixList){
//        // put the pixmaps one next to the other


//        QLabel *PixLabel = new QLabel(MainLabel);
//        PixLabel->setScaledContents(false);
//        PixLabel->setPixmap(pix);
//        VerFramesLayout->addWidget(PixLabel);
//        QLabel *naziv_slike = new QLabel(MainLabel);
//        naziv_slike->setText("");
//        VerFramesLayout->addWidget(naziv_slike);
//        QCheckBox *cekiraj = new QCheckBox(MainLabel);
//        VerFramesLayout->addWidget(cekiraj);
//    }

}

imageDisplay::~imageDisplay()
{
    delete ui;
}


