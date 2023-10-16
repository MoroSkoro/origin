#ifndef DIALOGCHART_H
#define DIALOGCHART_H

#include <QDialog>
#include <QGridLayout>
#include <QChartView>

namespace Ui {
class DialogChart;
}

class DialogChart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChart(QWidget *parent = nullptr);
    ~DialogChart();
Ui::DialogChart *ui;
private:

signals:
    void sig_pb_cleane();
    void sig_pb_builde();
public:
    QWidget* wid_chart;
    QVBoxLayout* vbox;
    QGridLayout *layout;


private slots:
    void on_pb_cleane_clicked();
    void on_pb_builde_clicked();
};

#endif // DIALOGCHART_H
