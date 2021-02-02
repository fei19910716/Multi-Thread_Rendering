#include "mainwindow.h"
#include "cmake-build-debug/Learn-OpenGL_autogen/include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget_=new GLWidget();
    glWidget_->update();
    connect(ui->horizontalSlider,&QSlider::valueChanged,glWidget_,&GLWidget::setRotate,Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

GLWidget *MainWindow::getGlWidget() const {
    return glWidget_;
}

void MainWindow::setGlWidget(GLWidget *glWidget) {
    glWidget_ = glWidget;
}
