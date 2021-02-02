#include "glwidget.h"

#include <QGLWidget>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdParty/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "thirdParty/stb_image.h"

#include <QOffscreenSurface>


namespace  {

    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    static const char* vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "layout (location = 2) in vec2 aTexCoord;\n"
            "out vec3 ourColor;\n"
            "out vec2 TexCoord;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos, 1.0);\n"
            "    ourColor = aColor;\n"
            "    TexCoord = aTexCoord;\n"
            "}\n";
    static const char* fragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"

            "in vec3 ourColor;\n"
            "in vec2 TexCoord;\n"
            "uniform sampler2D ourTexture;\n"
            "void main()\n"
            "{\n"
            "    FragColor = texture(ourTexture, TexCoord);\n"
            "}\n";
}

GLWidget::GLWidget(QWidget* parent):QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    initRenderThread();
    initializeOpenGLFunctions();

    glViewport(0, 0, width(), height());

    m_program=new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource);
    m_program->link();

    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);

    GLuint vbo,ebo;
    glGenBuffers(1,&vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //genTextureFromImage("/Users/fordchen/Desktop/test_opengl/light.png");
    //genTextureFromStb_image("/Users/fordchen/Desktop/test_opengl/light.png");

    glBindVertexArray(0);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

}

void GLWidget::paintGL()
{

    glClearColor(0.3f,0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    m_program->bind();
    glBindVertexArray(m_vao);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    if(TextureBuffer::instance()->isMReady())
        TextureBuffer::instance()->drawTexture(this->context(), 6);

//    unsigned char * data = new unsigned char[width()*height()*4];
//    glBindTexture(GL_TEXTURE_2D,m_textureID);
//    //glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,data); // 将绑定纹理数据拷贝到data，TODO// 读取错误
//    glReadPixels(0,0,width(),height(),GL_RGBA,GL_UNSIGNED_BYTE,data);
//
//    stbi_write_png("/Users/fordchen/Desktop/out.png",width(),height(),4,data,0);

    glBindVertexArray(0);
    m_program->release();


//    glActiveTexture(GL_TEXTURE0);
//    //glDrawArrays(GL_TRIANGLES, 0, 6 /*sizeof(vertices) / sizeof(float) / 4*/);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);


}

void GLWidget::resizeGL(int width, int height)
{

    //glViewport(0, 0, width, height);
    m_thread->setNewSize(width, height);

}

void GLWidget::genTextureFromImage(const QString &path)
{

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    QImage texImage, tempImage;
    bool isLoadOK = tempImage.load(path);
    if(isLoadOK){
        texImage = QGLWidget::convertToGLFormat(tempImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage.width(), tempImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void GLWidget::genTextureFromStb_image(const QString &path)
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLWidget::initRenderThread()
{
    qDebug()<<"GLWidget::initRenderThread() start.";
    auto context = this->context();
    auto mainSurface = context->surface();

    auto renderSurface = new QOffscreenSurface(nullptr,this);
    renderSurface->setFormat(mainSurface->format());
    renderSurface->create();

    context->doneCurrent();
    m_thread = new RenderThread(renderSurface,context,this);
    context->makeCurrent(mainSurface);

    connect(m_thread,&RenderThread::imageReady, this, [this]() { update(); },Qt::QueuedConnection);
    m_thread->start();

    qDebug() << "GLWidget::initRenderThread() end";

}

void GLWidget::setRotate(float value) {
    ThreadHelper::instance()->setMRenderDegree(value);
}

