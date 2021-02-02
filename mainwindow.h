#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GLWidget* glWidget_= nullptr;
public:
    GLWidget *getGlWidget() const;

    void setGlWidget(GLWidget *glWidget);

};

#endif // MAINWINDOW_H
