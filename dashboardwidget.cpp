#include "dashboardwidget.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QTableWidget>
#include <QTableWidgetItem>

DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent)
{
    // Main layout
    mainLayout = new QVBoxLayout(this);

    // Title
    titleLabel = new QLabel("Water Quality Monitor", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; padding: 10px;");
    mainLayout->addWidget(titleLabel);

    // Navigation bar
    navBarLayout = new QHBoxLayout();

    dataPageButton = new QPushButton("Data Page", this);
    pollutantOverviewButton = new QPushButton("Pollutant Overview", this);
    popsButton = new QPushButton("POPs", this);
    litterIndicatorsButton = new QPushButton("Litter Indicators", this);
    fluorinatedCompoundsButton = new QPushButton("Fluorinated Compounds", this);
    complianceDashboardButton = new QPushButton("Compliance Dashboard", this);

    navBarLayout->addWidget(dataPageButton);
    navBarLayout->addWidget(pollutantOverviewButton);
    navBarLayout->addWidget(popsButton);
    navBarLayout->addWidget(litterIndicatorsButton);
    navBarLayout->addWidget(fluorinatedCompoundsButton);
    navBarLayout->addWidget(complianceDashboardButton);

    languageSelector = new QComboBox(this);
    languageSelector->addItems({"English", "French", "German"});
    navBarLayout->addWidget(languageSelector);

    mainLayout->addLayout(navBarLayout);

    // Stacked widget for pages
    stackedWidget = new QStackedWidget(this);
    dataPage = createDataPage();
    stackedWidget->addWidget(dataPage);
    stackedWidget->addWidget(createDummyPage("Pollutant Overview"));
    stackedWidget->addWidget(createDummyPage("Persistent Organic Pollutants (POPs)"));
    stackedWidget->addWidget(createDummyPage("Environmental Litter Indicators"));
    stackedWidget->addWidget(createDummyPage("Fluorinated Compounds"));
    stackedWidget->addWidget(createDummyPage("Compliance Dashboard"));

    mainLayout->addWidget(stackedWidget);

    // Footer
    footerLayout = new QHBoxLayout();

    userLabel = new QLabel("<a href=\"https://credits.example.com\">User Guides</a>", this);
    userLabel->setTextFormat(Qt::RichText);
    userLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    userLabel->setOpenExternalLinks(true);

    helpLabel = new QLabel("<a href=\"https://environment.data.gov.uk/water-quality/view/doc/reference\">Help</a>", this);
    helpLabel->setTextFormat(Qt::RichText);
    helpLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    helpLabel->setOpenExternalLinks(true);

    creditsLabel = new QLabel("<a href=\"https://credits.example.com\">Credits</a>", this);
    creditsLabel->setTextFormat(Qt::RichText);
    creditsLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    creditsLabel->setOpenExternalLinks(true);

    footerLayout->addStretch();
    footerLayout->addWidget(userLabel);
    footerLayout->addWidget(helpLabel);
    footerLayout->addWidget(creditsLabel);
    footerLayout->addStretch();

    mainLayout->addLayout(footerLayout);

    // Connect signals
    connect(languageSelector, &QComboBox::currentTextChanged, this, &DashboardWidget::handleLanguageChanged);
    connect(dataPageButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentWidget(dataPage); });
    connect(pollutantOverviewButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentIndex(1); });
    connect(popsButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentIndex(2); });
    connect(litterIndicatorsButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentIndex(3); });
    connect(fluorinatedCompoundsButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentIndex(4); });
    connect(complianceDashboardButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentIndex(5); });
}

QWidget* DashboardWidget::createDataPage()
{
    QWidget* page = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(page);

    QPushButton* loadCsvButton = new QPushButton("Load CSV File", page);
    layout->addWidget(loadCsvButton);

    dataTable = new QTableWidget(page);
    layout->addWidget(dataTable);

    connect(loadCsvButton, &QPushButton::clicked, this, &DashboardWidget::loadCsvData);

    return page;
}

void DashboardWidget::loadCsvData()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv)");
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Failed to open CSV file!");
        return;
    }

    // Clear the table before loading new data
    dataTable->clearContents();
    dataTable->setRowCount(0);

    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList items = line.split(',');

        if (row == 0)
        {
            dataTable->setColumnCount(items.size());
            dataTable->setHorizontalHeaderLabels(items);
        }
        else
        {
            dataTable->insertRow(dataTable->rowCount());
            for (int col = 0; col < items.size(); ++col)
            {
                dataTable->setItem(row - 1, col, new QTableWidgetItem(items[col]));
            }
        }
        ++row;
    }

    file.close();
}


QWidget* DashboardWidget::createDummyPage(const QString& pageTitle)
{
    QWidget* page = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(page);

    QLabel* label = new QLabel(pageTitle, page);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 18px; font-weight: bold; padding: 20px;");

    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}


void DashboardWidget::handleNavigation()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;
    if (button == dataPageButton)
        stackedWidget->setCurrentIndex(0); // Adjust index if needed

    if (button == pollutantOverviewButton)
        stackedWidget->setCurrentIndex(0);
    else if (button == popsButton)
        stackedWidget->setCurrentIndex(1);
    else if (button == litterIndicatorsButton)
        stackedWidget->setCurrentIndex(2);
    else if (button == fluorinatedCompoundsButton)
        stackedWidget->setCurrentIndex(3);
    else if (button == complianceDashboardButton)
        stackedWidget->setCurrentIndex(4);
}

void DashboardWidget::handleLanguageChanged(const QString &language)
{
    emit languageChanged(language);
}
