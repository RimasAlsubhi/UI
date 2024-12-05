#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Water Quality Monitor");
    setMinimumSize(800, 600);

    // Set up the dashboard widget
    DashboardWidget* dashboard = new DashboardWidget(this);
    setCentralWidget(dashboard);
}
