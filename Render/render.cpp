#include "render.h"
#include "../Util/FpsTimer.h"
namespace  {

     float vertices[] = {
            //     ---- 位置 ----
            0.5f,  0.5f, 0.0f,   // 右上
            0.5f, -0.5f, 0.0f,     // 右下
            -0.5f, -0.5f, 0.0f,      // 左下
            -0.5f,  0.5f, 0.0f,      // 左上
    };

     unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    //shader
     char vertexShaderSource[] =
            "#version 330 core\n"
            "layout (location = 0) in vec2 vPos;\n"
            "uniform mat4 rotate;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = rotate * vec4(vPos.x, vPos.y, 0.0, 1.0);\n"
            "}\n";
     char fragmentShaderSource[] =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\n";
}
Render::Render(QObject *parent):
    QObject (parent)
{
    init();
}

void Render::init()
{
    initializeOpenGLFunctions();

//    glEnable(GL_DEBUG_OUTPUT);
//    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//    glDebugMessageCallback(glDebugOutput, nullptr);

    qDebug() << reinterpret_cast<const char *>(glGetString(GL_VERSION));

    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    //vbo
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //ebo
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //rbo
    glGenRenderbuffers(1, &m_rbo);
    adjustSize(m_width,m_height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);


    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

}
/*
 * 根据新的size重新生成Texture和rbo
 */
void Render::adjustSize(int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    if (width > height)
    {
        glViewport((width - height) / 2,0,height,height);
    }
    else
    {
        glViewport(0,(width - height) / 2,width,width);
    }
}

void Render::render(int width, int height)
{
    //FpsTimer timer("Render one frame");
    if (m_width != width || m_height != height)
    {
        m_width = width;
        m_height = height;
        adjustSize(m_width,m_height);
    }
    glClearColor(0.2f, 1.0f, 1.0f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

//    static float degree = 0.0f;
//    degree += 0.01f;

    QMatrix4x4 rotate;
    rotate.setToIdentity();
    rotate.rotate(ThreadHelper::instance()->getMRenderDegree(), 0, 0, 1);

    m_program->bind();
    m_program->setUniformValue("rotate", rotate);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //free data
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_program->release();
    glFinish();

}
