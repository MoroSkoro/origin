#include "statisticplot.h"

StatisticPlot::StatisticPlot(QObject *parent)
    : QObject{parent}
{
    ptrPoint = new QLineSeries(this);
    chart = new QChart();
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);

    chart->legend()->setVisible(false);
    chart->setTitle("График загруженности за выбранный месяц");
    axisX->setTitleText("Дни");
    axisY->setTitleText("Общее кол-во вылетов/прилетов");
}

StatisticPlot::~StatisticPlot(){
    delete chart;
}

void StatisticPlot::buildPlot(int &size){
    if(chart->series().isEmpty() == false){
        ptrPoint->clear();
        ptrPoint->detachAxis(axisX);
        ptrPoint->detachAxis(axisY);
        chart->removeSeries(ptrPoint);
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
    }

    for(int j = 0; j<size; j++){
        ptrPoint->append(x[j],y[j]);
    }
    chart->addSeries(ptrPoint);
    axisX->setLabelFormat("%i");
    axisX->setTickCount(size);
    chart->addAxis(axisX, Qt::AlignBottom);
    ptrPoint->attachAxis(axisX);
    axisX->setRange(1, size);
    axisY->setLabelFormat("%i");
    axisY->setRange(0, *std::max_element(y.begin(), y.end())+2);
    chart->addAxis(axisY, Qt::AlignLeft);
    ptrPoint->attachAxis(axisY);
}
