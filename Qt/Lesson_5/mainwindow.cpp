#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pButton_start->setCheckable(true);
    ui->pButton_start->setChecked(false);
    ui->pButton_start->setStyleSheet("QPushButton {background-color:lightgreen}");
    ui->pButton_cikle->setCheckable(true);
    ui->pButton_cikle->setEnabled(false);

    ui->lb_time->setText("Время: 00.0");

    st = new Stopwatch(this);
    connect(st->_timer, &QTimer::timeout, this, &MainWindow::slotUpdateTime);
    connect(this, &MainWindow::cikle_click, st, st->cikle_start);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotUpdateTime(){
    s=st->_s;
    ms=st->_ms;
    ss=st->_ss;
    ui->lb_time->setText("Время: "+mg_ss.number(ss)+"."+mg_ms.number(ms));

    if(ui->pButton_cikle->isChecked()){
        if(st->cikle_true){
            ui->textB_time->setText(cikle_mg+"\nКруг: "+cikles.number(st->_cikles)+", время: "+cikle_ss.number(st->_cikle_ss)
        +"."+cikle_ms.number(st->_cikle_ms)+" сек");
        }
    }
}

void MainWindow::on_pButton_start_clicked()
{
    if(ui->pButton_start->isChecked()){
        st->m_time_start();
        ui->pButton_start->setStyleSheet("QPushButton {background-color:lightcoral}");
        ui->pButton_start->setText("Стоп");
        ui->pButton_cikle->setEnabled(true);
    }

    else{
        st->m_time_stop();
        ui->pButton_start->setStyleSheet("QPushButton {background-color:lightgreen}");
        ui->pButton_start->setText("Старт");
        ui->pButton_cikle->setEnabled(false);
    }
}


void MainWindow::on_pButton_reset_clicked(){
    if(ui->pButton_start->isChecked()){
        st->m_time_reset();
        ui->textB_time->setText("");
        cikle_mg="";
        ui->pButton_cikle->setChecked(false);
    }
    else{
        st->m_time_reset();
        cikle_mg="";
        ui->lb_time->setText("Время: 0.00");
        ui->textB_time->setText("");
        ui->pButton_cikle->setChecked(false);

    }
}


void MainWindow::on_pButton_cikle_clicked(){
    if(ui->pButton_cikle->isChecked()){
        emit cikle_click();
    }
    else {
        if(st->cikle_true){
            cikle_mg = cikle_mg+"\nКруг: "+cikles.number(st->_cikles)+", время: "+cikle_ss.number(st->_cikle_ss)
            +"."+cikle_ms.number(st->_cikle_ms)+" сек";
            ui->textB_time->setText(cikle_mg);
        }
    }
}
