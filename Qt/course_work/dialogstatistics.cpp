#include "dialogstatistics.h"
#include "ui_dialogstatistics.h"

DialogStatistics::DialogStatistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStatistics)
{
    ui->setupUi(this);
    ui->comboBox->addItems(m_list_months);
}

DialogStatistics::~DialogStatistics()
{
    delete ui;
}

void DialogStatistics::on_pushButton_clicked()
{
    this->hide();
}


void DialogStatistics::on_tabWidget_currentChanged(int index)
{
    if(index==0){
        ui->comboBox->setCurrentIndex(0);
        currentMonth= ui->comboBox->currentIndex();
        emit signal_chart();
    }
}

void DialogStatistics::on_comboBox_currentIndexChanged(int index)
{
    currentMonth= ui->comboBox->currentIndex();
    emit signal_chart();
}

