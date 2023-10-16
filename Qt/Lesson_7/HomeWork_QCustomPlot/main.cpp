//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>

//int main(int argc, char *argv[])
    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)

{
    //QApplication a(argc, argv);
    int argc = 0;
    QApplication a( argc, 0 );

    MainWindow w;
    w.show();
    return a.exec();
}
