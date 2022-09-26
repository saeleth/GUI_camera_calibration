#include "dimenzijedialog.h"
#include "ui_dimenzijedialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>


dimenzijeDialog::dimenzijeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dimenzijeDialog)
{
    ui->setupUi(this);
}

dimenzijeDialog::~dimenzijeDialog()
{
    delete ui;
}

double dimenzijeDialog::dajDimenzije() {
    QString dimensions = ui->lineEdit_checkSize->text();
    double dimenzija = dimensions.toDouble();
    return dimenzija;
}

int dimenzijeDialog::dajKolone() {
    QString kolone = ui->lineEdit_cols->text();
    int kolona = kolone.toInt();
    return kolona;
}

int dimenzijeDialog::dajRedove() {
    QString redovi = ui->lineEdit_rows->text();
    int red = redovi.toInt();
    return red;
}
