#ifndef Server_HPP
#define Server_HPP

#include <QObject>
#include <QTimer>
#include "Include/serverChannel.hpp"
#include "Include/TCPsocket.hpp"

class Server : public QObject {
    Q_OBJECT

public:
    Server(const std::string& ip, int port, QObject* parent = nullptr);
    ~Server();

public slots:
    void start();
    void onThresholdChanged(double newThreshold);

signals:
    void temperatureReceived(double temperature);

private slots:
    void timerSlot();

private:
    std::shared_ptr<ServerChannel> serverChannel;
    QTimer* timer;
    double currentThreshold;
    double lastSentThreshold;
    double lastTemperature;
};

#endif // Server_HPP
