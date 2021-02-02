//
// Created by FordChen on 2021/1/12.
//

#include "ThreadHelper.h"

ThreadHelper *ThreadHelper::instance() {
    static ThreadHelper threadHelper;
    return &threadHelper;
}

void ThreadHelper::setMRenderDegree(float mRenderDegree) {
    QMutexLocker locker(&m_mutex);
    m_renderDegree = mRenderDegree;
}

ThreadHelper::ThreadHelper() {

}

ThreadHelper::~ThreadHelper() {

}

float ThreadHelper::getMRenderDegree() const {
    return m_renderDegree;
}
