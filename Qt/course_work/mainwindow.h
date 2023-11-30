#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include "database.h"
#include "dbdata.h"
#include <QTimer>
#include <QThread>
#include <QComboBox>
#include <QSqlRecord>
#include <QDateEdit>
#include <QDate>
#include "qcomboboxmodel.h"
#include <QtAlgorithms>
#include "dialogstatistics.h"
#include "ui_dialogstatistics.h"
#include "statisticbar.h"
#include "statisticplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//private slots:
public slots:
    void on_act_addData_triggered();
    void on_act_connect_triggered();
    void ScreenDataFromDB(int typeRequest);
    void autoConnect();
    void autoConnectAnew(); //(int const r);
    void slot_AirportListRequest();
    void on_pushBut_Request_clicked();
    void date_for_statisticYear(QBarSet* s, QStringList& categories, QSqlQueryModel* m);
    void sl_monthStatistic();

signals:
    void sig_ConnectAnew();
    void sig_AirportListRequest();

private:
    Ui::MainWindow *ui;

    QVector<QString> dataForConnect; //Данные для подключения к БД.
    DbData *dataDb;
    DataBase* dataBase;
    QMessageBox* msg;
    QPixmap *pix;
    QLabel *pixLb;
    QLabel *msgLb;
    int m_howClosed_msg = QMessageBox::Cancel;
    bool m_RetryClosed_msg =false;
    QString requestAirport;
    DialogStatistics* DialogStatistic;

public:
    QList<QPair<QString,QString>> *values;
    QComboBoxModel *model;
    QString airportCode;
    QDate requestData;
    StatisticBar* yearBar;
    StatisticPlot* plot;

    QString request = "SELECT airport_name->>'ru' as \"airportName\", "
                      "airport_code FROM bookings.airports_data";

    QString request_arrival = "SELECT flight_no, scheduled_arrival, "
                              "ad.airport_name->>'ru' as \"Name\" from bookings.flights f "
                              "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                              "where f.arrival_airport  = ";

    QString request_departure = "SELECT flight_no, TO_CHAR(scheduled_departure, 'DD-MM-YYYY HH24:MI:SS'), "
                                "ad.airport_name->>'ru' as \"Name\" from bookings.flights f "
                                "JOIN bookings.airports_data ad on ad.airport_code = f.arrival_airport "
                                "WHERE f.departure_airport  = ";

    QString request_arrivall = "SELECT flight_no, TO_CHAR(scheduled_arrival, 'DD-MM-YYYY HH24:MI:SS') as \"Scheduled\", "
                              "ad.airport_name->>'ru' as \"Name\" from bookings.flights f "
                              "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                              "where f.arrival_airport  = ";

    QString request_statistic_month = "SELECT count(flight_no), date_trunc('day', scheduled_departure) as \"Day\""
                                      " from bookings.flights f"
                                      " WHERE(scheduled_departure::date > date('2016-08-31') and"
                                      " scheduled_departure::date <= date('2017-08-31')) and ( departure_airport ="
                                      " airportCode or arrival_airport = airportCode) GROUP BY \"Day\"";

    QString request_statistic_year = " SELECT count(flight_no), date_trunc('month', scheduled_departure) as \"Month\""
                                     " from bookings.flights f"
                                     " WHERE (scheduled_departure::date > date('2016-08-31') and"
                                     " scheduled_departure::date <= date('2017-08-31')) and ( departure_airport ="
                                     " airportCode or arrival_airport = airportCode) group by \"Month\"";



private slots:
    void on_pushBut_Statist_clicked();
};
#endif // MAINWINDOW_H
