#include "mainwindow.h"
#include <QTabWidget>
#include <QQuickWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QQmlContext>
#include <QStatusBar>

class TemperatureModel : public QStandardItemModel {
public:
    TemperatureModel(QObject* parent = nullptr) : QStandardItemModel(parent) {
        setColumnCount(2);
        setHorizontalHeaderLabels({"Index", "Temperature"});
    }

    void addTemperature(double temperature) {
        int row = rowCount();
        setItem(row, 0, new QStandardItem(QString::number(row)));
        setItem(row, 1, new QStandardItem(QString::number(temperature)));
    }
};

MainWindow::MainWindow(const std::string& ip, int port, QWidget* parent)
    : QMainWindow(parent), currentThreshold(30.0) {
    QTabWidget* tabWidget = new QTabWidget;


    // Tab 1: Real Time Monitor
    QQuickWidget* meterWidget = new QQuickWidget;
    meterWidget->rootContext()->setContextProperty("currentTemperature", 0.0);
    meterWidget->setSource(QUrl("qrc:/qml/Resources/qml/meter.qml"));
    meterWidget->setResizeMode(QQuickWidget::SizeRootObjectToView); // Make QML resize with widget
    //Set minimum size for better visibility
    meterWidget->setMinimumSize(400, 300);

    tabWidget->addTab(meterWidget, "Real Time Monitor");

    // Tab 2: Historical Analysis
    temperatureModel = new TemperatureModel(this);
    QQuickWidget* chartWidget = new QQuickWidget;
    chartWidget->rootContext()->setContextProperty("temperatureModel", temperatureModel);
    chartWidget->setSource(QUrl("qrc:/qml/Resources/qml/chart.qml"));
    tabWidget->addTab(chartWidget, "Historical Analysis");

    // Tab 3: Configuration
    QWidget* configTab = new QWidget;
    QVBoxLayout* configLayout = new QVBoxLayout(configTab);

    // Label
    QLabel* thresholdLabel = new QLabel("Set Threshold (°C):");
    thresholdLabel->setAlignment(Qt::AlignCenter);
    configLayout->addWidget(thresholdLabel);

    // Centered spin box using horizontal layout
    QHBoxLayout* centerLayout = new QHBoxLayout;
    QDoubleSpinBox* thresholdSpinBox = new QDoubleSpinBox;
    thresholdSpinBox->setRange(0.0, 100.0);
    thresholdSpinBox->setDecimals(0);
    thresholdSpinBox->setValue(currentThreshold);
    thresholdSpinBox->setFixedWidth(150);
    thresholdSpinBox->setFixedHeight(60);

    thresholdSpinBox->setFont(QFont("Arial", 20, QFont::Bold));
    centerLayout->addStretch();
    centerLayout->addWidget(thresholdSpinBox);
    centerLayout->addStretch();
    configLayout->addLayout(centerLayout);

    // Stretch to push everything to vertical center
    configLayout->addStretch(1);
    configLayout->insertStretch(0, 1);  // Stretch on top

    // Background image
    configTab->setStyleSheet(R"(
    QWidget {
        background-image: url(:/icons/Resources/icons/background.jpg);
        background-repeat: no-repeat;
    })");

    tabWidget->addTab(configTab, "Configuration");

    // Tab 4: Quick Access
    // Tab 4: Quick Access
    QWidget* quickAccessTab = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(quickAccessTab); // Main vertical layout

    // Add stretch to push content to the middle vertically
    mainLayout->addStretch();

    // First row: Facebook, LinkedIn, Instagram
    QHBoxLayout* socialMediaLayout = new QHBoxLayout;
    socialMediaLayout->addStretch(); // Stretch to the left

    QPushButton* fbButton = new QPushButton("Facebook");
    fbButton->setFont(QFont("Arial", 15, QFont::Bold));
    fbButton->setIcon(QIcon(":/icons/Resources/icons/facebook.png"));
    connect(fbButton, &QPushButton::clicked, [](){
        QDesktopServices::openUrl(QUrl("https://www.facebook.com/share/19hfjncKaN/"));
    });
    socialMediaLayout->addWidget(fbButton);

    QPushButton* linkedinButton = new QPushButton("LinkedIn");
    linkedinButton->setFont(QFont("Arial", 15, QFont::Bold));
    linkedinButton->setIcon(QIcon(":/icons/Resources/icons/linkedin.png"));
    connect(linkedinButton, &QPushButton::clicked, [](){
        QDesktopServices::openUrl(QUrl("https://www.linkedin.com/company/edges-for-training/"));
    });
    socialMediaLayout->addWidget(linkedinButton);

    QPushButton* instagramButton = new QPushButton("Instagram");
    instagramButton->setFont(QFont("Arial", 15, QFont::Bold));
    instagramButton->setIcon(QIcon(":/icons/Resources/icons/instagram.png"));
    connect(instagramButton, &QPushButton::clicked, [](){
        QDesktopServices::openUrl(QUrl("https://www.instagram.com/edgesfortraining"));
    });
    socialMediaLayout->addWidget(instagramButton);

    socialMediaLayout->addStretch(); // Stretch to the right
    mainLayout->addLayout(socialMediaLayout); // Add first row to main layout

    // Second row: Personal LinkedIn
    QHBoxLayout* personalLinkedinLayout = new QHBoxLayout;
    personalLinkedinLayout->addStretch(); // Stretch to the left

    QPushButton* myLinkedinButton = new QPushButton("Mohamed Newir");
    myLinkedinButton->setFont(QFont("Arial", 15, QFont::Bold));
    myLinkedinButton->setIcon(QIcon(":/icons/Resources/icons/linkedin.png"));
    connect(myLinkedinButton, &QPushButton::clicked, [](){
        QDesktopServices::openUrl(QUrl("https://www.linkedin.com/in/mohamed-newir-a8a572182"));
    });
    personalLinkedinLayout->addWidget(myLinkedinButton);

    personalLinkedinLayout->addStretch(); // Stretch to the right
    mainLayout->addLayout(personalLinkedinLayout); // Add second row to main layout

    // Add stretch to push content to the middle vertically
    mainLayout->addStretch();

    quickAccessTab->setLayout(mainLayout);

    // Set background
    quickAccessTab->setStyleSheet(R"(
    QWidget {
        background-image: url(:/icons/Resources/icons/background.jpg);
        background-repeat: no-repeat;
    }
)");

    tabWidget->addTab(quickAccessTab, "Quick Access");



    //tabWidget -> setStyleSheet("background-image: url(:/icons/Resources/icons/background.jpg);");

    setCentralWidget(tabWidget);

    // LED Status
    ledLabel = new QLabel("LED: OFF");
    ledLabel->setStyleSheet("background-color: red; color: white; padding: 5px;");
    statusBar()->addWidget(ledLabel);

    // Connect threshold change
    connect(thresholdSpinBox, &QDoubleSpinBox::valueChanged, [this](double value){
        currentThreshold = value;
        emit thresholdChanged(value);
    });

    // Worker thread setup
    workerThread = new QThread;
    worker = new Server(ip, port);
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::started, worker, &Server::start);
    connect(worker, &Server::temperatureReceived, this, &MainWindow::onTemperatureReceived);
    connect(this, &MainWindow::thresholdChanged, worker, &Server::onThresholdChanged);
    workerThread->start();

    // Optional background
    //setStyleSheet("QMainWindow { background-image: url(:/icons/Resources/icons/background.jpg); }");
}

MainWindow::~MainWindow() {
    workerThread->quit();
    workerThread->wait();
    delete worker;
    delete workerThread;
}

void MainWindow::onTemperatureReceived(double temperature) {
    QQuickWidget* meterWidget = qobject_cast<QQuickWidget*>(centralWidget()->findChild<QQuickWidget*>());
    if (meterWidget) {
        meterWidget->rootContext()->setContextProperty("currentTemperature", temperature);
        meterWidget->update();
    }
    temperatureModel->addTemperature(temperature);
    ledLabel->setText(temperature > currentThreshold ? "LED: ON" : "LED: OFF");
    ledLabel->setStyleSheet(temperature > currentThreshold ? "background-color: green; color: white; padding: 5px;" : "background-color: red; color: white; padding: 5px;");
}
