/*
Author: Mohamed Newir
Date: 15/06/2025
File: client.cpp
Description:
            -> This file implements the client-side logic for a TCP socket communication in C++.
            -> It connects to a server, listens for commands, and sends responses based on the received commands.
            -> The client can receive a new threshold setting and respond with the current temperature.
            -> It uses the ClientChannel class to manage socket communication and the TCPSocket class for TCP operations.
*/


#include "../Include/clientChannel.hpp"
#include "../Include/TCPsocket.hpp"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string ip = "192.168.7.1";
    int port = 8080;
    if (argc > 1) ip = argv[1];
    if (argc > 2) port = std::stoi(argv[2]);
    ClientChannel client(std::make_shared<TCPSocket>(ip, port));
    client.start();
    std::string status;
    double threshold = 0.0;
    while (true) {
        std::string command = client.receive();
        if (command.find("set threshold") != std::string::npos) {
            std::istringstream iss(command);
            std::string cmd, set, threshStr, newStatus;
            iss >> cmd >> set >> threshStr >> newStatus;
            threshold = std::stod(threshStr);
            status = newStatus;
            std::cout << "Received new threshold: " << threshold << " °C – LED Status: " << status << "\n";
        } else if (command.find("get Temp") != std::string::npos) {
            // Parse the status from the get Temp command
            std::istringstream iss(command);
            std::string cmd, tempCmd, newStatus;
            iss >> cmd >> tempCmd >> newStatus;
            if (!newStatus.empty()) {
                status = newStatus;
            }
            std::cout << "Received command: get Temp\nEnter temperature: ";
            std::string temp;
            std::cin >> temp;
            std::cout << "Sending temperature: " << temp << " °C – LED Status: " << status << "\n";
            client.send(temp);
        }
    }

    client.stop();
    return 0;
}




