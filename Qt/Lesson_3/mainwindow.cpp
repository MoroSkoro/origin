#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog = new Dialog_log(this);
    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(QDialog::Accepted == dialog->exec())
        ui->lb_status_conect->setText("База данных подключена");
    else ui->lb_status_conect->setText("База данных не подключена");
}

void MainWindow::timerEvent(QTimerEvent * event)
{
    setWindowTitle(QTime::currentTime().toString("hh:mm:ss"));
}

