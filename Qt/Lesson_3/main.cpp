#include "mainwindow.h"
#include <QtCore>
#include <QtNetwork>
#include <QtSql>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
