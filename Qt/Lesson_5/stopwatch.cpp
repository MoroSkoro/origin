#include "stopwatch.h"

Stopwatch::Stopwatch(QObject* parent)
    : QObject{parent}
{

   _s.setHMS(0,0,0,0);
    connect(_timer, SIGNAL(timeout()), SLOT(updateTimer()));
}

void Stopwatch::updateTimer(){
   _s=_s.addMSecs(100);
    ++i;
   if(i<10){
       ++_ms;
    }
    if(i==10){
       _ms=0;
       _ss++;
       i=0;
    }
}

void Stopwatch::m_time_start(){
    _timer->start(100);
}

void Stopwatch::m_time_stop(){
    _timer->stop();
}

void Stopwatch::m_time_reset(){
    _s.setHMS(0,0,0);
    _ss = 0;
    _ms = 0;
    i = 0;
}
