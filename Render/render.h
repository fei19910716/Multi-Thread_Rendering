#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

#include "../Util/ThreadHelper.h"

class Render:public QObject, public QOpenGLFunctions_3_3_Core
{
public:
    Render(QObject* parent = nullptr);
    void init();
    void adjustSize(int width, int height);
    void render(int width,int height);

public:
    Render(const Render &) = delete;
    Render &operator =(const Render &) = delete;
    Render(const Render &&) = delete;
    Render &operator =(const Render &&) = delete;

    QOpenGLShaderProgram* m_program;
    GLuint m_vao,m_vbo,m_fbo,m_texture,m_rbo,m_ebo;
    int m_width,m_height;
};

#endif // RENDER_H
