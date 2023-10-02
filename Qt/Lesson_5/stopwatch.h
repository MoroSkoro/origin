#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    QTimer *_timer = new QTimer(this);
    int _ss =0;
    int _ms =0;
    int i=0;
    int _cikles=0;
    int _cikle_ss;
    int _cikle_ms;
    int cikle_i=0;
    bool cikle_true = false;
    QTime _s;
    QString _mg;

public:
    explicit Stopwatch(QObject *parent = nullptr);

    void m_time_start ();
    void m_time_stop ();
    void m_time_reset();

public slots:
    void updateTimer();
    void cikle_start();
};

#endif // STOPWATCH_H
