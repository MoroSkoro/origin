#include "stopwatch.h"

Stopwatch::Stopwatch(QObject* parent)
    : QObject{parent}
{
    connect(_timer, &QTimer::timeout, this, &Stopwatch::updateTimer);
}

void Stopwatch::updateTimer(){
    ++_ms_total;
    _ss = _ms_total/10;
    _ms = _ms_total%10;
    emit lbUpdate();
}

void Stopwatch::m_time_start(){
    _timer->start(100);
}

void Stopwatch::m_time_stop(){
    _timer->stop();
}

void Stopwatch::m_time_reset(){
    _ms_total=0;
    _cikles=0;
}

void Stopwatch::cikle_start(){
    _cikle_ms=_ms_total;
    if(_cikles==0){
       _show_ss = _cikle_ms/10;
       _show_ms = _cikle_ms%10;
    }
    else{
       _show_ss = (_cikle_ms - _last_ms)/10;
       _show_ms = (_cikle_ms - _last_ms)%10;
    }
       _last_ms=_cikle_ms;

    ++_cikles;
}
