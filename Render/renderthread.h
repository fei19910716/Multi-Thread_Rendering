#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QObject>
#include <QThread>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QMutex>

#include "render.h"
#include "TextureBuffer.h"

class GLWidget;
class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(QOffscreenSurface* surface,QOpenGLContext* context,QObject* parent=nullptr);
    ~RenderThread();

    void setNewSize(int width, int height);
    void run() override;
    void setRenderDegree(float degree);

signals:
    void imageReady();

private:
    RenderThread(const RenderThread &) = delete;
    RenderThread &operator =(const RenderThread &) = delete;
    RenderThread(const RenderThread &&) = delete;
    RenderThread &operator =(const RenderThread &&) = delete;

    QOffscreenSurface* m_renderSurface;
    QOpenGLContext* m_renderContext;
    QOpenGLContext* m_mainContext;
    QMutex m_mutex;
    unsigned int m_width;
    unsigned int m_height;
    bool  m_running = true;
    Render* m_render= nullptr;
};

#endif // RENDERTHREAD_H
