#include "server.hpp"


Server::Server(const std::string& ip, int port, QObject* parent)
    : QObject(parent), currentThreshold(30.0), lastSentThreshold(0.0), lastTemperature(0.0) {
    serverChannel = std::make_shared<ServerChannel>(std::make_shared<TCPSocket>(ip, port));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Server::timerSlot);
}

Server::~Server() {
    serverChannel->stop();
}

void Server::start() {
    serverChannel->start();
    timer->start(1000);
}

void Server::onThresholdChanged(double newThreshold) {
    currentThreshold = newThreshold;
}

void Server::timerSlot() {
    std::string status = (lastTemperature > currentThreshold) ? "ON" : "OFF";
    if (currentThreshold != lastSentThreshold) {
        std::string message = "set threshold " + std::to_string(currentThreshold) + " " + status;
        serverChannel->send(message);
        lastSentThreshold = currentThreshold;
    } else {
        std::string message = "get Temp " + status;
        serverChannel->send(message);
        std::string tempStr = serverChannel->receive();
        try {
            lastTemperature = std::stod(tempStr);
            emit temperatureReceived(lastTemperature);
        } catch (...) {
            // Handle invalid temperature data if needed
        }
    }
}
