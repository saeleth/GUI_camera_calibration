#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dimenzijedialog.h"
#include <QMainWindow>
#include <mainwindow.h>
#include "choosetype.h"
#include "qcheckbox.h"
#include "qlabel.h"
#include "ui_mainwindow.h"
#include <iostream>

////opencv biblioteke
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DodajSliku(QString ime);

    void UkloniSlike();

    void SingleCalibration(std::vector<cv::Mat> vec_slika);

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_pushButton_calibrate_clicked();

    void ShowTheScroll();

    void NadjiCoskove();

    void on_actionHelp_triggered();

    void on_actionWhat_s_this_triggered();

    void on_actionExport_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *MainLabel;

    // Za dinamicke widgete, hashmap and the rest
    QHash<QPushButton*, QVBoxLayout*> mButtonToLayoutMap; // hash mapa za povezivanje layouta u kojem se nalaze dinamicki widgeti
    std::vector<QCheckBox*> check_boxovi;
    std::vector<std::tuple<QPixmap, QLabel*>> odabrane_slike;



    //// Varijable za pronalazak coskova
    //vektor za vektore 3D tacaka za svaku checkerboard sliku
    std::vector<std::vector<cv::Point3f>> objpoints;

    // vektor za vektore 2D tacaka za svaku checkerboard sliku
    std::vector<std::vector<cv::Point2f>> imgpoints;

    // 3D koordinate (in world)
    std::vector<cv::Point3f> objp;

    int CHECKERBOARD[2]{1, 1}; /// BROJ UNUTRASNJIH COSKOVA CHECKERBOARDA

    // parametri za kalibraciju
    cv::Mat cameraMatrix, distCoeffs, R, T, izlaz;
    std::vector<std::vector<double>> izlaz_write;
};
#endif // MAINWINDOW_H
