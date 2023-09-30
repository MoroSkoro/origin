#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotUpdateTime();

    void on_pButton_start_clicked();

    void on_pButton_reset_clicked();

    void on_pButton_cikle_clicked();

private:
    Ui::MainWindow *ui;
    Stopwatch*  st;
    QTime s;
    QString mg_ss, mg_ms;
    int ms;
    int ss;
};
#endif // MAINWINDOW_H
