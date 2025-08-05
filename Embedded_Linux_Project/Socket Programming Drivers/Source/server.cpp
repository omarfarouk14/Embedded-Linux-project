/*
Author: Omar Ali
Date: 25/06/2025
File: server.cpp
Description:
            -> This file implements the server-side logic for a TCP socket communication in C++.
            -> It manages a server channel that listens for incoming connections, handles client requests,
                and sends responses based on the received commands.
            -> The server can set a new threshold and respond with the current temperature.
            -> It uses the ServerChannel class to manage socket communication and the TCPSocket class for TCP operations.
*/

#include "../Include/serverChannel.hpp"
#include "../Include/TCPsocket.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>

class ServerApp {
public:
    ServerApp(const std::string& ip, int port)
        : running(true),
          currentThreshold(30.0),
          lastSentThreshold(0.0),
          lastTemperature(0.0),
          serverChannel(std::make_shared<ServerChannel>(std::make_shared<TCPSocket>(ip, port))) {}

    void run() {
        serverChannel->start();
        std::thread loopThread(&ServerApp::serverLoop, this);

        std::string input;
        while (running) {
            std::cout << "Enter new threshold (e.g., 40) or 'q' to quit: ";
            std::getline(std::cin, input);
            if (input == "q") {
                running = false;
                break;
            }
            try {
                currentThreshold = std::stod(input);
                std::cout << "Threshold set to: " << currentThreshold << "°C\n";
            } catch (...) {
                std::cout << "Invalid input. Please enter a number or 'q' to quit.\n";
            }
        }

        loopThread.join();
        serverChannel->stop();
        std::cout << "Server shutting down...\n";
    }

private:
    void serverLoop() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (currentThreshold != lastSentThreshold) {
                std::string status = (lastTemperature > currentThreshold) ? "ON" : "OFF";
                std::string message = "set threshold " + std::to_string(currentThreshold) + " " + status;
                serverChannel->send(message);
                std::cout << "Sent: " << message << std::endl;
                lastSentThreshold = currentThreshold;
            } else {
                // Send current status with get Temp command to keep client updated
                std::string status = (lastTemperature > currentThreshold) ? "ON" : "OFF";
                std::string message = "get Temp " + status;
                serverChannel->send(message);
                std::cout << "Sent: " << message << std::endl;
                std::string tempStr = serverChannel->receive();
                lastTemperature = std::stod(tempStr);
                std::string newStatus = (lastTemperature > currentThreshold) ? "ON" : "OFF";
                std::cout << "Received temperature: " << lastTemperature << "°C, LED Status: " << newStatus << std::endl;
            }
        }
    }

    std::atomic<bool> running;
    double currentThreshold;
    double lastSentThreshold;
    double lastTemperature;
    std::shared_ptr<ServerChannel> serverChannel;
};

int main(int argc, char* argv[]) {
    std::string ip = "192.168.7.1";
    int port = 8080;
    if (argc > 1) ip = argv[1];
    if (argc > 2) port = std::stoi(argv[2]);
    std::cout << "Server starting on " << ip << ":" << port << "...\n";
    ServerApp app(ip, port);
    app.run();
    return 0;
}
