//#pragma once
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
    QTime _s;
    QString _mg;

public:
    explicit Stopwatch(QObject *parent = nullptr);

    void m_time_start ();
    void m_time_stop ();
    void m_time_reset();

public slots:
    void updateTimer();
};

#endif // STOPWATCH_H
