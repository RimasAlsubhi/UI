#include "dashboardwidget.hpp"
#include <QVBoxLayout>
#include <QLabel>

DashboardCard::DashboardCard(const QString& title, 
                              const QString& status, 
                              QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(titleLabel);

    QLabel* statusLabel = new QLabel(status);
    statusLabel->setStyleSheet(QString("background-color: %1; color: white; padding: 5px;")
                                .arg(getStatusColor(status).name()));
    layout->addWidget(statusLabel);
}

QColor DashboardCard::getStatusColor(const QString& status)
{
    if (status == "Safe") return QColor(76, 175, 80);   // Green
    if (status == "Caution") return QColor(255, 193, 7);  // Amber
    if (status == "Critical") return QColor(244, 67, 54);  // Red
    return QColor(44, 62, 80);  // Default
}

DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent)
{
    setupLayout();
}

void DashboardWidget::setupLayout()
{
    QGridLayout* gridLayout = new QGridLayout(this);

    DashboardCard* pollutantCard = new DashboardCard("Pollutant Overview", "Caution", this);
    gridLayout->addWidget(pollutantCard, 0, 0);

    DashboardCard* complianceCard = new DashboardCard("Compliance Status", "Safe", this);
    gridLayout->addWidget(complianceCard, 0, 1);

    QChartView* pollutantChart = createPollutantChart();
    gridLayout->addWidget(pollutantChart, 1, 0, 1, 2);
}

QChartView* DashboardWidget::createPollutantChart()
{
    QBarSet *set0 = new QBarSet("Safe");
    QBarSet *set1 = new QBarSet("Caution");
    QBarSet *set2 = new QBarSet("Exceeding");

    *set0 << 2000000000000000 << 100 << 100;
    *set1 << 30 << 25 << 35;
    *set2 << 30 << 15 << 15;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pollutant Levels");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories = {"1,1,2-Trichloroethane", "Chloroform", "PCBs"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

