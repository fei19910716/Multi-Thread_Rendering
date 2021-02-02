//
// Created by FordChen on 2021/1/11.
//

#ifndef MYWINDOW_FPSTIMER_H
#define MYWINDOW_FPSTIMER_H
#include <iostream>
#include <string>
#include <chrono>

class FpsTimer {
public:
    enum LightTimerType {
        LightTimer_TYPE_DEFAULT = 0,
        LightTimer_TYPE_PERFORMANCE = 1,
        LightTimer_TYPE_KEY = 2
    };

    FpsTimer(const std::string &taskName, const LightTimerType timerType = FpsTimer::LightTimer_TYPE_PERFORMANCE);
    ~FpsTimer();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
    std::string m_taskName;

private:
    FpsTimer(const FpsTimer &) = delete;
    FpsTimer &operator =(const FpsTimer &) = delete;
    FpsTimer(const FpsTimer &&) = delete;
    FpsTimer &operator =(const FpsTimer &&) = delete;
};


#endif //MYWINDOW_FPSTIMER_H
