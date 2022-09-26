#include "dimenzijedialogstereo.h"
#include "ui_dimenzijedialogstereo.h"
#include <QFile>
#include <QFileDialog>
#include <iostream>

dimenzijeDialogStereo::dimenzijeDialogStereo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dimenzijeDialogStereo)
{
    ui->setupUi(this);
}

dimenzijeDialogStereo::~dimenzijeDialogStereo()
{
    delete ui;
}

QString dimenzijeDialogStereo::dajFolder1() {
   QString folder = ui->lineEdit_folder1->text();
   return folder;
}


QString dimenzijeDialogStereo::dajFolder2() {
    QString folder = ui->lineEdit_folder2->text();
    return folder;
}


void dimenzijeDialogStereo::on_pushButton_folder1_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select folder", "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_folder1->setText(dir);
}


void dimenzijeDialogStereo::on_pushButton_folder2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select folder", "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_folder2->setText(dir);
}

