#include "dialog_log.h"
#include "ui_dialog_log.h"

Dialog_log::Dialog_log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_log)
{
    ui->setupUi(this);
}

Dialog_log::~Dialog_log()
{
    delete ui;
}
