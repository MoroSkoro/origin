#ifndef STATISTICBAR_H
#define STATISTICBAR_H

#include <QObject>
#include <QtCharts>
#include <QChartView>

class StatisticBar : public QObject
{
    Q_OBJECT
public:
    explicit StatisticBar(QObject *parent = nullptr);

    void buildHistogram();

signals:

public:
    QBarSet* statisticInYear;
    QBarSeries* series;
    QChart* chartBar;
    QStringList categories;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;

};

#endif // STATISTICBAR_H
