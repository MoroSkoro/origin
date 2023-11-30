#ifndef STATISTICPLOT_H
#define STATISTICPLOT_H

#include <QObject>
#include <QLineSeries>
#include <QtCharts>
#include <QChartView>
#include <algorithm>

class StatisticPlot : public QObject
{
    Q_OBJECT
public:
    explicit StatisticPlot(QObject *parent = nullptr);
    ~StatisticPlot();

    void buildPlot(int &size);

    QLineSeries* ptrPoint;
    QVector<int> x;
    QVector<int> y;
    QChart* chart;
    QValueAxis* axisX;
    QValueAxis* axisY;

signals:
};

#endif // STATISTICPLOT_H
