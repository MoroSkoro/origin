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

void Dialog_log::on_buttonBox_accepted()
{
    ui->lineE_nameBD->setText("Postgres");
    accept();
}


void Dialog_log::on_buttonBox_rejected()
{
    reject();
}

