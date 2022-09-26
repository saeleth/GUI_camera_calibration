#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include "qlabel.h"
#include <QDialog>

namespace Ui {
class imageDisplay;
}

class imageDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit imageDisplay(QWidget *parent = nullptr);
    ~imageDisplay();

private:
    Ui::imageDisplay *ui;
    QLabel *MainLabel;
};

#endif // IMAGEDISPLAY_H
