#include "stopwatch.h"

Stopwatch::Stopwatch(QObject* parent)
    : QObject{parent}
{

   _s.setHMS(0,0,0,0);
    connect(_timer, &QTimer::timeout, this, &Stopwatch::updateTimer);
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

    if(cikle_true){
       ++cikle_i;
       if(cikle_i<10){
           ++_cikle_ms;
       }
       if(cikle_i==10){
           _cikle_ms=0;
           _cikle_ss++;
           cikle_i=0;
       }
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

    _cikle_ss=0;
    _cikle_ms=0;
    cikle_i=0;
    cikle_true = false;
    _cikles=0;
}

void Stopwatch::cikle_start(){
    _cikle_ss=0;
    _cikle_ms=0;
    cikle_i=0;
    cikle_true = true;
    ++_cikles;
}
