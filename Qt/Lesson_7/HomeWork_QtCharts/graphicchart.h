#ifndef GRAPHICCHART_H
#define GRAPHICCHART_H

#include <QObject>
#include <QLineSeries>
#include <QtCharts>
#include <QChartView>

#define FIRST_GRAPH 0

class GraphicChart : public QObject
{
    Q_OBJECT
public:
    GraphicChart(uint32_t Canals_number = 0);

    void AddDataToGrahp(QVector<double> x, QVector<double> y, uint32_t canalNum);
    void ClearGraph(QChart* chart);
    void UpdateGraph(QChart* chart);


//signals:

//private:

    QList<QLineSeries*> ptrGraph;
    uint32_t canalsNum = 0;
};

#endif // GRAPHICCHART_H
