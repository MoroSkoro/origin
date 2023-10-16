


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QtGlobal>
#include <QtConcurrent>
#include <algorithm>
#include "dialogchart.h"
#include "ui_dialogchart.h"
#include "qcustomplot.h"
#include "graphic.h"

#define NUM_GRAPH 2
#define CANALS_NUM 2
#define FD 1000.0 //частота дискретизации

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Метод считывает данные из исходного файла
    QVector<uint32_t> ReadFile(QString path, uint8_t numberChannel);
    //Метод преобразует данные физические величины, В?
    QVector<double> ProcessFile(QVector<uint32_t> dataFile);
    //Метод ищет Максимумы
    QVector<double> FindMax(QVector<double> resultData);
    //Метод ищет минимумы
    QVector<double> FindMin(QVector<double> resultData);
    //Метод отображает результаты
    void DisplayResult(QVector<double> mins, QVector<double> maxs);


signals:
    void sig_yDataReady();

private slots:
    void on_pb_path_clicked();
    void on_pb_start_clicked();
    void sl_chartReady();
public slots:
    void sl_pb_clear_clicked();
    void sl_pb_updGraph_clicked();
    void on_pb_chart_clicked();

private:
    Ui::MainWindow *ui;
    QString pathToFile = "";
    uint8_t numberSelectChannel = 0xEA;

    QVector<uint32_t> readData;
    QVector<double> procesData;
    QVector<double> mins, maxs;
    QVector<double> y_data;
    DialogChart* d;

    //void ViewGraph(void);

    QCPGraph* graphic;
    Graphic* graphClass;

};
#endif // MAINWINDOW_H
