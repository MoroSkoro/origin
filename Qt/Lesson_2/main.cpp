#include <QCoreApplication>
#include <QtCore>
#include <QtNetwork>
#include <QtSql>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool exit = true;

     QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
     QSqlError err;

     QHostAddress adr;
     QTcpSocket sock;

    if (exit) {return 0;};
    return a.exec();
}
