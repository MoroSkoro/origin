#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    modelQuery = new QSqlQueryModel();

}

DataBase::~DataBase()
{
    delete dataBase;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());


    ///Тут должен быть код ДЗ


    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request, int& typeRequest){

    QSqlError err;
    switch (typeRequest) {

    case requestAllFilms:{
        simpleQuery = new QSqlTableModel(this, *dataBase);

        simpleQuery->setTable("film");
        simpleQuery->setEditStrategy(QSqlTableModel::OnFieldChange);
        simpleQuery->setHeaderData(1, Qt::Horizontal, tr("Название фильма"));
        simpleQuery->setHeaderData(2, Qt::Horizontal, tr("Описание фильма"));

        if(simpleQuery->select() == false){
            err = simpleQuery->lastError();
        }
        break;
    }
    case requestHorrors:{
        modelQuery->setQuery(request, *dataBase);

        modelQuery->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        modelQuery->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));
        modelQuery->setHeaderData(2, Qt::Horizontal, tr("Год выпуска"));
        modelQuery->setHeaderData(3, Qt::Horizontal, tr("Жанр"));

        if(modelQuery->lastError().isValid()){
            err = modelQuery->lastError();
        }

        break;
    }
    case requestComedy:{
        modelQuery->setQuery(request, *dataBase);

        modelQuery->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        modelQuery->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));
        modelQuery->setHeaderData(2, Qt::Horizontal, tr("Год выпуска"));
        modelQuery->setHeaderData(3, Qt::Horizontal, tr("Жанр"));

        if(modelQuery->lastError().isValid()){
            err = modelQuery->lastError();
        }

        break;
    }
    default:
        break;
    }

    emit sig_SendStatusRequest(err);
}


/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
