#ifndef DASHBOARDWIDGET_HPP
#define DASHBOARDWIDGET_HPP

#include <QWidget>
#include <QtCharts>
#include <QGridLayout>
#include <QLabel>

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);

private:
    QChartView* createPollutantChart();
};

#endif // DASHBOARDWIDGET_HPP
