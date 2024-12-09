#include "mainwindow.hpp"
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Water Quality Monitor");
    setMinimumSize(800, 600);

    dashboardWidget = new DashboardWidget(this);
    setCentralWidget(dashboardWidget);

    createMenuBar();
    createToolBar();
    createStatusBar();
}

void MainWindow::createMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* exitAction = fileMenu->addAction(tr("E&xit"));
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, [this]() {
        QMessageBox::about(this, tr("About Water Quality Monitor"),
            tr("Water Quality Monitoring Application\n"
               "Tracking pollutant levels and compliance"));
    });
}

void MainWindow::createToolBar()
{
    QToolBar* toolbar = addToolBar(tr("Main Toolbar"));
    QComboBox* languageSelector = new QComboBox(this);
    languageSelector->addItems({"English", "French", "German"});
    toolbar->addWidget(languageSelector);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

