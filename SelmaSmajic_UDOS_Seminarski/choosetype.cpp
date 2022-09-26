#include "choosetype.h"
#include "ui_choosetype.h"

ChooseType::ChooseType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseType)
{
    ui->setupUi(this);
}

ChooseType::~ChooseType()
{
    delete ui;
}

bool type = 0;

bool ChooseType::SingleOrStereo() {
    return type;
}

void ChooseType::on_pushButton_single_clicked()
{
    type = 0;
}


void ChooseType::on_pushButton_stereo_clicked()
{
    type = 1;
}

