#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QStackedWidget>
#include <QTableWidget> 


class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    DashboardWidget(QWidget *parent = nullptr);

signals:
    void languageChanged(const QString &language);

private slots:
    void handleNavigation();
    void handleLanguageChanged(const QString &language);
    void loadCsvData();

private:
    QTableWidget* dataTable;
    QWidget* dataPage;
    QVBoxLayout* mainLayout;
    QHBoxLayout* navBarLayout;
    QStackedWidget* stackedWidget;
    QHBoxLayout* footerLayout;

    QLabel* titleLabel;
    QComboBox* languageSelector;

    QPushButton* dataPageButton;
    QPushButton* pollutantOverviewButton;
    QPushButton* popsButton;
    QPushButton* litterIndicatorsButton;
    QPushButton* fluorinatedCompoundsButton;
    QPushButton* complianceDashboardButton;

    QLabel* userLabel;
    QLabel* helpLabel;
    QLabel* creditsLabel;
    
    QWidget* createDataPage();
    QWidget* createDummyPage(const QString& pageTitle);
};

#endif // DASHBOARDWIDGET_H
