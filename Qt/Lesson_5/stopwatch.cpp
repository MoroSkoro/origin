#include "stopwatch.h"

Stopwatch::Stopwatch(QObject* parent)
    : QObject{parent}
{
    connect(_timer, &QTimer::timeout, this, &Stopwatch::updateTimer);
}

void Stopwatch::updateTimer(){
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
    _ss = 0;
    _ms = 0;
    i = 0;

    _cikle_ss=0;
    _cikle_ms=0;
    _cikles=0;
}

void Stopwatch::cikle_start(){
    if(_cikles==0){
       _last_ss=_ss;
       _last_ms=_ms;
       _show_ss=_last_ss;
       _show_ms=_last_ms;
    }
    else{
       _cikle_ss = _ss;
       _cikle_ms = _ms;
       _show_ss = _cikle_ss - _last_ss;
       if(_cikle_ms >= _last_ms){_show_ms = _cikle_ms - _last_ms;}
       else{
           --_show_ss;
           _show_ms = 100+_cikle_ms - _last_ms;
       }
       _last_ss = _cikle_ss;
       _last_ss = _cikle_ss;
    }
    ++_cikles;
}
