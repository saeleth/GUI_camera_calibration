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
#include "moje_funkcije.h"
#include "QCheckBox"
#include "qcheckbox.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>


using namespace cv;
bool calibration_type; // 0 for single, 1 for stereo


bool loaded_imgs = 0;
QString m_Name = "img"; // folder name where the images will be stored for the time being

QString calib1d = "calib1d";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_calibrate->hide();
    ui->pushButton->hide();
    ui->groupBox->hide();
    ui->label_check_params->hide();
    //  ui->frame->hide();

    ////////////////////
    ChooseType biraj;
    biraj.setModal(true);
    if (QDialog::Accepted == biraj.exec()) {
        calibration_type = biraj.SingleOrStereo();
    }
    ui->scrollArea->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void OcistiDirektorij(QString folder_name) {
    QDir dir(folder_name);
    dir.removeRecursively();

}

void LoadNoveSlikeDirektorij(std::vector<Mat> nove_slike, QString folder_name) {
    QString filePath = "";
    QDir dir(filePath);
    dir.mkdir(folder_name);
    for(int i=0; i<int(nove_slike.size()); i++) {
        imwrite(folder_name.toStdString()+"\\"+std::to_string(i)+".bmp", nove_slike.at(i));
    }
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::question(this, "Exit", "Are you sure you want to exit?");
    if(QMessageBox::Yes) {
        QCoreApplication::exit();
        //    QString filePath = "";
        //QString filePath = QDir::homePath();
        QDir dir(m_Name);
        dir.removeRecursively();
    }
    // delete ui->scrollArea;
}



//std::vector<Mat> loadImagesFromDirectory(QString ime) {
//    QDir directory(ime);
//    QStringList file_name = directory.entryList(QStringList() << "*.bmp" << "*.bmp", QDir::Files);
//    std::vector<Mat> files_img;
//    std::vector<std::string> vec;
//    foreach(QString str, file_name) {
//        vec.push_back(str.toStdString());
//    }

//    for(int i=0; i<file_name.length(); i++) {
//        std::string path = vec.at(i);
//        std::string ime_novo = ime.toStdString();
//        Mat slika = imread(ime_novo+path, IMREAD_COLOR);
//        files_img.push_back(slika);
//    }
//    return files_img;
//}

void MainWindow::NadjiCoskove() {
    //   int CHECKERBOARD[2]{9,5};

    //    // Creating vector to store vectors of 3D points for each checkerboard image
    //    std::vector<std::vector<Point3f>> objpoints;
    objpoints.clear();

    //    // Creating vector to store vectors of 2D points for each checkerboard image
    //    std::vector<std::vector<Point2f>> imgpoints;
    imgpoints.clear();

    // Definisanje 3D tačaka za world coordinates
    //    std::vector<Point3f> objp;
    objp.clear();
    for(int i{0}; i<CHECKERBOARD[1]; i++)
    {
        for(int j{0}; j<CHECKERBOARD[0]; j++)
            objp.push_back(Point3f(j,i,0)*15);
    }

    Mat frame, gray;
    // vector to store the pixel coordinates of detected checker board corners
    std::vector<Point2f> corner_pts;
    bool success;

    // loopanje kroz slike u direktoriju
    QStringList imena_slika;
    std::vector<Mat> slike = loadImagesFromDirectory("img/", imena_slika);
    std::vector<Mat> prihvacene_slike;
    std::vector<Mat> untouched_prihvacene_slike;
    for(int i{0}; i<int(slike.size()); i++)
    {
        //frame = imread("img/"+imena_slika.at(i).toStdString(), IMREAD_COLOR);
        frame  = slike.at(i).clone();
        //cv::resize(frame, frame, Size(800,600), INTER_LINEAR);
        cvtColor(frame, gray, COLOR_BGR2GRAY);


        // trazenje cosokova
        success = findChessboardCorners(gray, Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, CALIB_CB_ADAPTIVE_THRESH +  CALIB_CB_FAST_CHECK + CALIB_CB_NORMALIZE_IMAGE);


        // ako je zeljeni broj coskova detektovan , dorade se koordinate pixela i prikazu na slici checkerboarda
        if(success)
        {
            TermCriteria criteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.001);

            // refining pixel coordinates for given 2d points.
            cornerSubPix(gray, corner_pts, Size(11,11), Size(-1,-1),criteria);

            // Displaying the detected corner points on the checker board
            drawChessboardCorners(frame, Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, success);

            prihvacene_slike.push_back(frame);
            untouched_prihvacene_slike.push_back(slike.at(i));

            objpoints.push_back(objp);
            imgpoints.push_back(corner_pts);
        }
    }
    QString informacije_coskovi = "Total images processed: " + QString::number(slike.size()) + "\n";
    informacije_coskovi += "Added images: "+QString::number(prihvacene_slike.size()) + "\n";
    informacije_coskovi += "Rejected images: "+ QString::number(slike.size()-prihvacene_slike.size());
    QMessageBox::information(this, "Info", informacije_coskovi);
    OcistiDirektorij(calib1d);
    OcistiDirektorij(m_Name);
    LoadNoveSlikeDirektorij(prihvacene_slike, calib1d);
    LoadNoveSlikeDirektorij(untouched_prihvacene_slike, m_Name);
}

void MainWindow::ShowTheScroll() {    
    NadjiCoskove();

    QStringList imena_slika;
    std::vector<Mat> slike = loadImagesFromDirectory("calib1d/", imena_slika);

    ui->scrollArea->setWidgetResizable(true);

    QFrame *inner = new QFrame(ui->scrollArea);
    ui->scrollArea->setWidget(inner);

    QVBoxLayout* MainLayout = new QVBoxLayout(inner);
    //    MainLayout = qobject_cast<QVBoxLayout*>(inner);

    ui->scrollArea->show();
    foreach(QString ime, imena_slika){
        // stavljaj slicice, njihov naziv, i dugme za brisanje u svakoj iteraciji

        QVBoxLayout *SubLayout = new QVBoxLayout(inner); /// layout u koji stavljamo set widgeta

        QLabel* PixLabel = new QLabel(inner);
        QImage image("calib1d/"+ime);
        QImage newImage = image.scaled(700, 700, Qt::KeepAspectRatio);
        QPixmap pix = QPixmap::fromImage(newImage);

        PixLabel->setScaledContents(false);
        PixLabel->setPixmap(pix);

        SubLayout->addWidget(PixLabel);

        //// DODAJ NAZIV SLIKE
        QLabel *naziv_slike = new QLabel(inner);
        naziv_slike->setText(ime);
        SubLayout->addWidget(naziv_slike);

        //// DODAJ CHECKBOX
        QPushButton *cekiraj = new QPushButton("Remove image " + ime,
                                               inner);
        //   check_boxovi.push_back(cekiraj);
        SubLayout->addWidget(cekiraj);

        MainLayout->insertLayout(0, SubLayout);

        mButtonToLayoutMap.insert(cekiraj, SubLayout);

        QObject::connect(
                    cekiraj, &QPushButton::clicked,
                    this, &MainWindow::UkloniSlike
                    );
    }
}

void MainWindow::UkloniSlike() { //dinamicko brisanje slika
    /// brisanje slike iz foldera onda brisanje pokazivaca za dinamicke widgete i layout
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString ime = button->text();
    ime = ime.remove("Remove image ");
    qDebug() << ime << "\n";
    QFileDevice::Permissions dozvole(QFile::permissions("img/"+ime));
    bool isOK = QFile::setPermissions("img/"+ime, dozvole);
    bool image_removed_from_file = QFile::remove("img/"+ime);

    QFileDevice::Permissions dozvole2(QFile::permissions("calib1d/"+ime));
    bool isOK2 = QFile::setPermissions("calib1d/"+ime, dozvole2);
    bool image_removed_from_file2 = QFile::remove("calib1d/"+ime);

    if (!(image_removed_from_file && isOK && image_removed_from_file2 && isOK2)) QMessageBox::critical(this, "Error", "Image not removed!");
    else {
        QVBoxLayout* layout = mButtonToLayoutMap.take(button);
        while (layout->count() != 0) {
            QLayoutItem* item = layout->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

void MainWindow::DodajSliku(QString ime) {
    // ui->scrollArea->show();

    //   QLabel *Label = new QLabel(this);
    //    QVBoxLayout *MainLayout = new QVBoxLayout(this);
    //    MainLayout->addWidget(MainLabel);
    //    QVBoxLayout* VerFramesLayout = new QVBoxLayout(MainLabel);
    //    ui->scrollArea->setLayout(VerFramesLayout);
    //    ui->scrollAreaWidgetContents_3->setLayout(VerFramesLayout);
    //    VerFramesLayout->setStretch(0, 2);

    // QHBoxLayout* HMainLayout = qobject_cast<QHBoxLayout*>(ui->frame->layout());

    QVBoxLayout* SubLayout = new QVBoxLayout(ui->scrollArea);

    //    QVBoxLayout* SubLayout = new QVBoxLayout(this);
    //  SubLayout->setStretch(0, 2);
    //    QVBoxLayout* VMainLayout = new QVBoxLayout(this);
    //    VMainLayout->addWidget(Label);

    //// DODAJ SLIKU
    ///
    QLabel* PixLabel = new QLabel(ui->scrollArea);
    //  SubLayout->addWidget(PixLabel);

    QImage image("img/"+ime);
    QImage newImage = image.scaled(700, 700, Qt::KeepAspectRatio);
    QPixmap pix = QPixmap::fromImage(newImage);

    // odabrane_slike.push_back(std::tuple(pix, PixLabel));
    PixLabel->setScaledContents(false);
    PixLabel->setPixmap(pix);
    SubLayout->addWidget(PixLabel);
    //  ui->scrollArea->setWidget(PixLabel);

    //// DODAJ NAZIV SLIKE
    ///
    QLabel *naziv_slike = new QLabel(ui->scrollArea);
    naziv_slike->setText(ime);
    SubLayout->addWidget(naziv_slike);
    //  ui->scrollArea->setWidget(naziv_slike);

    //// DODAJ CHECKBOX
    ///
    QCheckBox *cekiraj = new QCheckBox("Remove image " + ime, ui->scrollArea);
    //   check_boxovi.push_back(cekiraj);
    SubLayout->addWidget(cekiraj);
    // ui->scrollArea->setWidget(cekiraj);

    //   HMainLayout->insertLayout(0, SubLayout);


    QObject::connect(cekiraj, &QCheckBox::clicked,
                     this, &MainWindow::UkloniSlike);

    QObject::connect(cekiraj, &QCheckBox::clicked,
                     this, &MainWindow::UkloniSlike);
}


void MainWindow::on_actionOpen_triggered()
{
    if(calibration_type==0) {
        QStringList file_name = QFileDialog::getOpenFileNames(this, "Open the file");
        std::vector<Mat> files_img;
        std::vector<std::string> vec; // pathovi slika koje ce biti ucitane
        foreach(QString str, file_name) {
            vec.push_back(str.toStdString());
        }
        QString filePath = "";
        QDir dir(filePath);
        dir.mkdir(m_Name);
        for(int i=0; i<file_name.length(); i++) {
            std::string path = vec.at(i);
            Mat slika = imread(path, IMREAD_COLOR);
            files_img.push_back(slika);
            imwrite(m_Name.toStdString()+"\\"+std::to_string(i)+".bmp", slika);
        }

        if(!files_img.empty()) {
            ui->label_load->close();
            QMessageBox::information(this, "Message", "Images loaded successfully!");
            loaded_imgs = 1;
        }
        else {
            QMessageBox::warning(this, "Message", "No images were loaded!");
            loaded_imgs = 0;
        }

        if(loaded_imgs)     {
            // ako su slike uspjesno ucitane onda daj korisniku da unese parametre potrebne za kalibraciju
            dimenzijeDialog dd;
            dd.setModal(true);
            if (QDialog::Accepted == dd.exec()) {
                double check_dim = dd.dajDimenzije();
                //                int CHECKERBOARD[2]{1, 1};
                CHECKERBOARD[0] = dd.dajKolone();
                CHECKERBOARD[1] = dd.dajRedove();
                if(check_dim <= 0 || CHECKERBOARD[0] <=0 || CHECKERBOARD[1] <=0) {
                    QMessageBox::critical(this, "Error", "Invalid entry!");
                    QMessageBox::information(this, "Info", "Please load your images again!");
                }
                else {
                    ui->pushButton_calibrate->show();
                    ui->pushButton->show();
                    ui->groupBox->show();
                    ui->label_check_params->show();
                    ui->label_check_params->setText("Size of the checkerboard squares: "
                                                    +QString::number(check_dim)+"\n"+"Chessboard corners: ["+
                                                    QString::number(CHECKERBOARD[0])+"," +QString::number(CHECKERBOARD[1])+"]");
                    ShowTheScroll();

                }
            }
        }
    }
    else { // ucitavanje slika za stereo kalibraciju
        dimenzijeDialogStereo dds;
        dds.setModal(true);
        if (QDialog::Accepted == dds.exec()) {
            QString path_folder1 = dds.dajFolder1();
            QString path_folder2 = dds.dajFolder2();
            QMessageBox::information(this, "Info", "Not implemented yet");
            //  dds.setModal(false);
        }
        //        imageDisplay disp;
        //        disp.setModal(true);
        //        disp.exec();
    }

}


//void MainWindow::on_actionAbout_triggered()
//{
//    QString ukratko = "Ovo je moj tuzni pokusaj GUI-a. :-(";
//    ukratko += "\n Ali je i dalje GUI.";
//    QMessageBox::information(this, "About", ukratko);
//}

bool je_li = 0;

//// ************************************************************************************************************************************
//// FUNKCIJA DUGMICA ZA PRIKAZ SLIKA U OPENCV UI
//// ************************************************************************************************************************************
void MainWindow::on_pushButton_clicked()
{
    QStringList imena_slika;
    std::vector<Mat> files_img = loadImagesFromDirectory("img/", imena_slika);
    if(files_img.empty()) QMessageBox::warning(this, "Warning", "No images were loaded!");
    else {
        int i=0;
        //   int rows = 0, cols = 0;
        QMessageBox::information(this, "Info", "Press any key to keep scrolling through the pictures.\n Press ESC to close OpenCV UI mode.");
        while(1) {
            namedWindow("Slika "+std::to_string(i));
            imshow("Slika "+std::to_string(i), files_img.at(i));
            moveWindow("Slika "+std::to_string(i), 0, 0);
            i++;
            // cols += files_img.at(i-1).cols;
            char key=(char)waitKey(0);

            if(key==27) { destroyAllWindows(); break; }

            if(i==int(files_img.size())) {
                //waitKey(0);
                i=0; //, rows=0, cols=0;
                destroyAllWindows();
            }
            // if(getWindowProperty("Slika "+std::to_string(i), WND_PROP_VISIBLE) == false) break;
        }
    }
}

//int CHECKERBOARD[2]{9,5};

void MainWindow::SingleCalibration(std::vector<Mat> vec_slika) {
    //    Mat cameraMatrix,distCoeffs,R,T;
    cameraMatrix.release();
    distCoeffs.release();
    R.release();
    T.release();
    izlaz.release();
    izlaz_write.clear();
    Mat gray  = vec_slika.at(0);

    /*
     * Performing camera calibration by
     * passing the value of known 3D points (objpoints)
     * and corresponding pixel coordinates of the
     * detected corners (imgpoints)
    */
    calibrateCamera(objpoints, imgpoints, Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);

    //    qDebug() << "cameraMatrix : " << cameraMatrix <<endl;
    //    qDebug() << "distCoeffs : " << distCoeffs << endl;
    //    qDebug() << "Rotation vector : " << R << endl;
    //    qDebug() << "Translation vector : " << T << endl;


    std::vector<double> R_red(3);
    for (int i = 0; i < 3; i++){
        R_red[i] = R.at<double>(1,i);
    }


    Rodrigues(R_red, izlaz);
//    std::vector<std::vector<double>> izlaz_write(izlaz.rows);
    izlaz_write = std::vector<std::vector<double>>(izlaz.rows);

    //    cout << "Matrica rotacije: " << endl;
    for (int i = 0; i < izlaz.rows; i++){
        for (int j = 0; j < izlaz.cols; j++){
            izlaz_write.at(i).push_back(izlaz.at<double>(i,j));
            qDebug() << izlaz.at<double>(i,j) << " ";
        }
        qDebug() << Qt::endl;
    }
    ui->statusbar->showMessage("Calibration successful! You can now export the parameters in the Export menu.");

}

//void StereoCalibration(std::vector<Mat> &vec_slika) {
//    // stereo kalibracija slika iz dva foldera :)
//}

void MainWindow::on_pushButton_calibrate_clicked()
{
    QStringList imena_slika;
    std::vector<Mat> files_img = loadImagesFromDirectory("img/", imena_slika);
    std::vector<Mat> korisnicki_odabrane;
    NadjiCoskove();
    //    ui->scrollArea->findChildren()
    //    ShowTheScroll();
    if(files_img.empty()) QMessageBox::warning(this, "Warning", "No images were loaded!");
    else {
        if(calibration_type==0) { //onda single kalibraciju performaj
            SingleCalibration(files_img);
        }
        else { // ako je calibration_type == 1 onda stereo radi
            //  StereoCalibration(files_img);
        }
    }
}


void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this, "Help", "Sorry, I can't help you yet.");
}


void MainWindow::on_actionWhat_s_this_triggered() {
    QString ukratko = "Ovo je moj pokusaj GUI-a. :-(";
    ukratko += "\n Ali je i dalje GUI.";
    QMessageBox::information(this, "About", ukratko);
}

//// ***************************************************************************
//// EXPORTOVANJE PARAMETARA U .TXT FAJL U ODABRANI FOLDER OD STRANE KORISNIKA *
/// ****************************************************************************
void MainWindow::on_actionExport_triggered()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "Select folder", "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    std::ofstream file;
    file.open(filePath.toStdString()+"/"+"calib1d_params.txt");

    // Matrica rotacije
    std::string nameof = "Rotation matrix\n";
    for(int i=0; i<int(nameof.size()); ++i) file << nameof.at(i);
    for(int i=0;i<int(izlaz_write.size());++i){
        for(int j=0; j<int(izlaz_write.at(0).size()); ++j) {
            file <<izlaz_write.at(i).at(j)<< " ";
        }
        file << std::endl;
    }
    file << std::endl;

    nameof = "Translation vector\n";
    for(int i=0; i<int(nameof.size()); ++i) file << nameof.at(i);
    for(int i=0;i<T.rows;++i){
        for(int j=0; j<T.cols; ++j) {
            file << T.at<double>(i, j) << " ";
        }
        file << std::endl;
    }
    file << std::endl;

    nameof = "Camera matrix\n";
    for(int i=0; i<int(nameof.size()); ++i) file << nameof.at(i);
    for(int i=0;i<cameraMatrix.rows;++i){
        for(int j=0; j<cameraMatrix.cols; ++j) {
            file << cameraMatrix.at<double>(i, j) << " ";
        }
        file << std::endl;
    }
    file << std::endl;

    nameof = "Rotation vector\n";
    for(int i=0; i<int(nameof.size()); ++i) file << nameof.at(i);
    for(int i=0;i<R.rows;++i){
        for(int j=0; j<R.cols; ++j) {
            file << R.at<double>(i, j) << " ";
        }
        file << std::endl;
    }
    file << std::endl;


    nameof = "Distortion coefficients\n";
    for(int i=0; i<int(nameof.size()); ++i) file << nameof.at(i);
    for(int i=0;i<distCoeffs.rows;++i){
        for(int j=0; j<distCoeffs.cols; ++j) {
            file << distCoeffs.at<double>(i, j) << " ";
        }
        file << std::endl;
    }

    file.close();

    QMessageBox::information(this, "Info", "Export successful!");
}

