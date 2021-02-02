//
// Created by FordChen on 2021/1/11.
//

#include "FpsTimer.h"


FpsTimer::FpsTimer(const std::string &taskName, const FpsTimer::LightTimerType timerType)
    :m_taskName(taskName)
    {

    m_begin = std::chrono::high_resolution_clock::now();

}

FpsTimer::~FpsTimer() {

    long long microSec=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
    //double MilliSec = microSec* 0.001;
    double Second=microSec* 0.000001;

    std::cout<<m_taskName<<" cost time: "<<Second<<std::endl;
}

