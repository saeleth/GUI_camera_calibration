#ifndef DIMENZIJEDIALOG_H
#define DIMENZIJEDIALOG_H

#include <QDialog>

namespace Ui {
class dimenzijeDialog;
}

class dimenzijeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dimenzijeDialog(QWidget *parent = nullptr);
    ~dimenzijeDialog();
    double dajDimenzije();
    int dajKolone();
    int dajRedove();

private slots:

private:
    Ui::dimenzijeDialog *ui;
};

#endif // DIMENZIJEDIALOG_H
