#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

#include "Render/renderthread.h"
#include "Util/ThreadHelper.h"


class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent=nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width,int height) override;

    void genTextureFromImage(const QString& path);
    void genTextureFromStb_image(const QString& path);

public slots:
    void setRotate(float value);

private:
    void initRenderThread();

private:

    RenderThread* m_thread=nullptr;
    QOpenGLShaderProgram* m_program=nullptr;

    GLuint m_textureID;
    GLuint m_vao;
    int texture_w;
    int texture_h;

};

#endif // GLWIDGET_H
