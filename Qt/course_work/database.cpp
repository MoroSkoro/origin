#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    //Выделяем память под объекты классов.
    //Объект QSqlDatabase является основным классом низкого уровня,
    //в котором настраивается подключение к БД.
    dataBase = new QSqlDatabase();
    modelAirportQuery = new QSqlQueryModel(this);
    modelStatisticYearQuery = new QSqlQueryModel(this);
    modelStatisticMonthQuery = new QSqlQueryModel(this);
    AirportQuery = new QSqlQuery();

    //QTableWidget необходим для формирования отображения ответа и передачи его в форму.
    //tableWidget = new QTableWidget();

}

DataBase::~DataBase()
{
    delete AirportQuery;
    delete dataBase;
    //delete tableWidget;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    /*  Класс QSqlDatabase представляет из себя интерфейс между
        кодом и БД. Он организует соединение с БД. Для подключения
        в конструктор класса необходимо передать драйвер БД и имя.
        В объекте может храниться несколько подключений, они различаются именами.
    */
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
bool DataBase::ConnectToDataBase(QVector<QString> data)
{
    //Для подключения необходимо передать параметры БД в объект класса.
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    //Для подключения к БД используется метод open(), который возвращает true в случае успешного подключения.
    return dataBase->open();
}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    //Сначала выбираем имя БД
    *dataBase = QSqlDatabase::database(nameDb);
    //Метод close() закрывает соединение с БД
    dataBase->close();
}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
QSqlError DataBase::RequestToDB(QString &request)
{
    /*  Для фоомирования запроса будем использовать
     *  объект QSqlQuery.
     *  В конструктор передадим адрес объекта QSqlDatabase
    */
    *AirportQuery = QSqlQuery(*dataBase);
    /*
       Выполнение запроса выполняется при помощи
       метода exec. В случае успешного запроса он вернет true.
       Если возникает какая либо ошибка, ее можно посмотреть
       при помощи метода lastError. Этот метод возвращает
       экземпляр класса QSqlError.
    */

    if(AirportQuery->exec(request)){
        QSqlError err;
        return err;
    }
    else{
        return AirportQuery->lastError();
    }
}

QSqlError DataBase::ModelRequest(QString &request, QSqlQueryModel* model){
    model->setQuery(request, *dataBase);
    if(model->lastError().isValid()){
        QSqlError err;
        err = model->lastError();
        return err;
    }
    else{
        return model->lastError();
    }
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
   return dataBase->lastError();
}
