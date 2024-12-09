#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QtCharts>

class DashboardCard : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardCard(const QString& title, 
                            const QString& status, 
                            QWidget *parent = nullptr);

private:
    QColor getStatusColor(const QString& status);
};

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);

private:
    void setupLayout();
    QChartView* createPollutantChart();
    QChartView* createComplianceChart();
};

#endif // DASHBOARDWIDGET_H

