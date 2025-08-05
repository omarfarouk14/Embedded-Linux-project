#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QThread>
#include <QLabel>
#include "server.hpp"
#include "Include/serverChannel.hpp"
#include "Include/TCPsocket.hpp"

class Server;
class TemperatureModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(const std::string& ip, int port, QWidget* parent = nullptr);
    ~MainWindow();

signals:
    void thresholdChanged(double newThreshold);

public slots:
    void onTemperatureReceived(double temperature);

private:
    TemperatureModel* temperatureModel;
    QLabel* ledLabel;
    double currentThreshold;
    Server* worker;
    QThread* workerThread;
};

#endif // MAINWINDOW_H
