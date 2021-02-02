#include "renderthread.h"
#include <iostream>

RenderThread::RenderThread(QOffscreenSurface *surface, QOpenGLContext *context,QObject* parent):
    QThread (parent),
    m_renderSurface(surface),
    m_mainContext(context)

{
    m_renderContext = new QOpenGLContext;
    m_renderContext->setFormat(m_mainContext->format());
    m_renderContext->setShareContext(m_mainContext);
    m_renderContext->create();
    m_renderContext->moveToThread(this);

}

void RenderThread::run(){

    m_renderContext->makeCurrent(m_renderSurface);
    if(m_render== nullptr){
        m_render=new Render;
    }
    TextureBuffer::instance()->createTexture(m_renderContext);

    //Render m_render;
    while (m_running){
        int width=0;
        int height = 0;
        {
            QMutexLocker lock(&m_mutex);
            width = m_width;
            height = m_height;
        }
        m_render->render(width, height);
        //TextureBuffer::instance()->updateTexture(m_renderContext,width,height);
        TextureBuffer::instance()->updateTexture(m_renderContext,m_render->m_texture);
        emit imageReady();

    }
    TextureBuffer::instance()->deleteTexture(m_renderContext);
}

void RenderThread::setNewSize(int width, int height)
{
    QMutexLocker lock(&m_mutex);
    m_width = width;
    m_height = height;
}

RenderThread::~RenderThread() {

    m_running = false;
    this->wait();
}
