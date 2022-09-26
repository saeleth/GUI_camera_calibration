#ifndef DIMENZIJEDIALOGSTEREO_H
#define DIMENZIJEDIALOGSTEREO_H

#include <QDialog>

namespace Ui {
class dimenzijeDialogStereo;
}

class dimenzijeDialogStereo : public QDialog
{
    Q_OBJECT

public:
    explicit dimenzijeDialogStereo(QWidget *parent = nullptr);
    QString dajFolder1();
    QString dajFolder2();
    ~dimenzijeDialogStereo();

private slots:
    void on_pushButton_folder1_clicked();

    void on_pushButton_folder2_clicked();

private:
    Ui::dimenzijeDialogStereo *ui;
};

#endif // DIMENZIJEDIALOGSTEREO_H
