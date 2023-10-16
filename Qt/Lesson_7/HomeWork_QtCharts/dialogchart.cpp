#include "dialogchart.h"
#include "ui_dialogchart.h"

DialogChart::DialogChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChart)
{
    ui->setupUi(this);

    vbox = new QVBoxLayout(this);
    wid_chart = new QWidget(this);
    layout = new QGridLayout(this);
    vbox->addWidget(wid_chart);
    vbox->addWidget(ui->gb_butns);
    this->setLayout(vbox);
}

DialogChart::~DialogChart()
{
    delete ui;
}

void DialogChart::on_pb_cleane_clicked()
{
    emit sig_pb_cleane();
}


void DialogChart::on_pb_builde_clicked()
{
    emit sig_pb_builde();
}

