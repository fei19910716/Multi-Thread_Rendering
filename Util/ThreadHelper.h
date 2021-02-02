//
// Created by FordChen on 2021/1/12.
//

#ifndef MYWINDOW_THREADHELPER_H
#define MYWINDOW_THREADHELPER_H

#include <QMutex>

class ThreadHelper {
public:
    static ThreadHelper* instance();



private:
    ThreadHelper();
    ~ThreadHelper();

    ThreadHelper(const ThreadHelper& threadHelper)=delete;
    ThreadHelper& operator=(const ThreadHelper& threadHelper)=delete;
    ThreadHelper(const ThreadHelper&& threadHelper)=delete;
    ThreadHelper& operator=(const ThreadHelper&& threadHelper)=delete;

private:
    float m_renderDegree=0.0f;
public:
    float getMRenderDegree() const;

public:
    void setMRenderDegree(float mRenderDegree);

private:
    QMutex m_mutex;
};


#endif //MYWINDOW_THREADHELPER_H
