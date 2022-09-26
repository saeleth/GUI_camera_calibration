#ifndef CHOOSETYPE_H
#define CHOOSETYPE_H

#include <QDialog>

namespace Ui {
class ChooseType;
}

class ChooseType : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseType(QWidget *parent = nullptr);
    bool SingleOrStereo();
    ~ChooseType();

private slots:
    void on_pushButton_single_clicked();

    void on_pushButton_stereo_clicked();

private:
    Ui::ChooseType *ui;
};

#endif // CHOOSETYPE_H
