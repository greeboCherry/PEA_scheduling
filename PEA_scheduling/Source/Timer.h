#pragma once
class Timer
{
public:

    double PCFreq = 0.0;
    __int64 CounterStart = 0;

    Timer();
    ~Timer();
    void StartCounter();
    double GetCounter();
};

