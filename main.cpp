#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile(QSurfaceFormat :: CoreProfile);
    QSurfaceFormat :: setDefaultFormat(glFormat);
    MainWindow w;
    w.show();

    return a.exec();
}
