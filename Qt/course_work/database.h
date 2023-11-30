#ifndef DATABASE_H
#define DATABASE_H

#include <QTableWidget>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{

    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4

};

//Типы запросов
enum requestType{

    requestAllFilms = 1,
    requestComedy = 2,
    requestHorrors = 3

};



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    bool ConnectToDataBase(QVector<QString> dataForConnect);
    void DisconnectFromDataBase(QString nameDb = "");
    QSqlError RequestToDB(QString &request);
    QSqlError ModelRequest(QString &request, QSqlQueryModel* model);
    QSqlError GetLastError(void);


signals:

   void sig_sendDataFromDB(QTableWidget *tableWg, int typeR);


//private:
public:
    QSqlDatabase* dataBase;
    QSqlQuery* AirportQuery;
    QSqlQueryModel* modelAirportQuery;
    QSqlQueryModel* modelStatisticYearQuery;
    QSqlQueryModel* modelStatisticMonthQuery;
};

#endif // DATABASE_H
