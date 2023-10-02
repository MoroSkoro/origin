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

signals:
    void cikle_click();

private slots:
    void slotUpdateTime();

    void on_pButton_start_clicked();

    void on_pButton_reset_clicked();

    void on_pButton_cikle_clicked();

private:
    Ui::MainWindow *ui;
    Stopwatch*  st;
    QString mg_ss, mg_ms;
    QString cikles, cikle_ss, cikle_ms;
    QString cikle_mg ="";
    int ms;
    int ss;
};
#endif // MAINWINDOW_H
