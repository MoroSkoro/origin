#ifndef DIALOG_LOG_H
#define DIALOG_LOG_H

#include <QDialog>

namespace Ui {
class Dialog_log;
}

class Dialog_log : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_log(QWidget *parent = nullptr);
    ~Dialog_log();

private:
    Ui::Dialog_log *ui;
};

#endif // DIALOG_LOG_H
