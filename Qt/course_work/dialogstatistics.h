#ifndef DIALOGSTATISTICS_H
#define DIALOGSTATISTICS_H

#include <QDialog>

namespace Ui {
class DialogStatistics;
}

class DialogStatistics : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStatistics(QWidget *parent = nullptr);
    ~DialogStatistics();
    QStringList m_list_months = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                                "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
private slots:
    void on_pushButton_clicked();

    void on_tabWidget_currentChanged(int index);
    void on_comboBox_currentIndexChanged(int index);

signals:
    void signal_chart();
public:
    Ui::DialogStatistics *ui;
    int currentMonth;
};

#endif // DIALOGSTATISTICS_H
