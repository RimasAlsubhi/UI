#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include "dashboardwidget.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    
    DashboardWidget* dashboardWidget;
};

#endif // MAINWINDOW_H

