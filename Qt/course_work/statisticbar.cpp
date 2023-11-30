#include "statisticbar.h"

StatisticBar::StatisticBar(QObject *parent)
    : QObject{parent}
{
    statisticInYear = new QBarSet("Статистика прилетов/вылетов за год");
    series = new QBarSeries();
    chartBar = new QChart();
    axisX = new QBarCategoryAxis();
    axisY = new QValueAxis();

}

void StatisticBar::buildHistogram(){
    series->append(statisticInYear);
    chartBar->addSeries(series);
    chartBar->setTitle("Статистика вылетов и прилетов каждый месяц за год");
    chartBar->setAnimationOptions(QChart::SeriesAnimations);
    axisX->append(categories);
    chartBar->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisY->setRange(0,450);
    chartBar->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chartBar->legend()->setVisible(false);
    chartBar->legend()->setAlignment(Qt::AlignRight);
}
