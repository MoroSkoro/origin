#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Leson_4");

    ui->rB_1->setText("Волна_1");
    ui->rB_2->setText("Волна_2");

    for(int i = 0; i<10; ++i){
        ui->cBox->addItem("Значение " + QString::number(i+1));
    }

    ui->prBar->setMinimum(0);
    ui->prBar->setMaximum(10);
    ui->prBar->setValue(0);

    ui->pb_1->setText("ВЫКЛ");
    ui->pb_1->setCheckable(true);
    ui->pb_1->toggled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_1_toggled(bool checked){
    qint8 v = ui->prBar->value();
    if(ui->pb_1->isChecked()){
        ui->pb_1->setStyleSheet("QPushButton {background-color:lightgreen}");
        ui->pb_1->setText("ВКЛ");
        if(v < 10){
            v+=1;
            ui->prBar->setValue(v);
        }
        else {
            v=0;
            ui->prBar->setValue(v);
        }
    }
    else {
        ui->pb_1->setStyleSheet("QPushButton {background-color:lightcoral}");
        ui->pb_1->setText("ВЫКЛЮЧЕНО");
    }
}
