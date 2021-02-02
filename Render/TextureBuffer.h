//
// Created by FordChen on 2021/1/11.
//

#ifndef TEXTUREBUFFER_H
#define TEXTUREBUFFER_H

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QMutex>


class TextureBuffer{
public:
    static TextureBuffer *instance();

    void createTexture(QOpenGLContext *context);
    void deleteTexture(QOpenGLContext *context);
    void updateTexture(QOpenGLContext *context, int width, int height);
    void updateTexture(QOpenGLContext *context, int textureID);
    void drawTexture(QOpenGLContext *context, int vertextCount);

private:
    TextureBuffer();
    ~TextureBuffer();
    TextureBuffer(const TextureBuffer &) = delete;
    TextureBuffer &operator =(const TextureBuffer &) = delete;
    TextureBuffer(const TextureBuffer &&) = delete;
    TextureBuffer &operator =(const TextureBuffer &&) = delete;

    unsigned int m_texture;
    mutable QMutex m_mutex;
    bool m_ready;
public:
    bool isMReady() const;
};

#endif //TEXTUREBUFFER_H

