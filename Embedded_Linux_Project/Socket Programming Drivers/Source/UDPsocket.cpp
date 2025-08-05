/*
Author: Omar Ali
Date: 25/06/2025
File: UDPsocket.cpp
Description:
            -> 
*/


#include "../Include/UDPsocket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>

UDPSocket::UDPSocket(const std::string& ip, int port) : ip(ip), port(port), socketFd(-1) {}

UDPSocket::~UDPSocket() {
    shutdown();
}

void UDPSocket::waitForConnect() {
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd < 0) throw std::runtime_error("Socket creation failed");

    struct sockaddr_in bindAddr;
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_addr.s_addr = INADDR_ANY;
    bindAddr.sin_port = htons(port);

    if (bind(socketFd, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) < 0) {
        throw std::runtime_error("Bind failed");
    }

    // Receive initial "hello" message from client
    char buffer[1024];
    socklen_t clientLen = sizeof(clientAddr);
    int bytesRead = recvfrom(socketFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientLen);
    if (bytesRead < 0) throw std::runtime_error("Receive failed");

    // "Connect" to the client's address for subsequent communication
    if (::connect(socketFd, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) {
        throw std::runtime_error("Connect failed");
    }
}

void UDPSocket::connect() {
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd < 0) throw std::runtime_error("Socket creation failed");

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address");
    }

    if (::connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Connect failed");
    }

    // Send initial "hello" message to the server
    std::string hello = "hello";
    if (::send(socketFd, hello.c_str(), hello.length(), 0) < 0) {
        throw std::runtime_error("Send failed");
    }
}

void UDPSocket::send(const std::string& message) {
    if (socketFd < 0) throw std::runtime_error("Socket not connected");
    if (::send(socketFd, message.c_str(), message.length(), 0) < 0) {
        throw std::runtime_error("Send failed");
    }
}

std::string UDPSocket::receive() {
    if (socketFd < 0) throw std::runtime_error("Socket not connected");
    char buffer[1024];
    int bytesRead = recv(socketFd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0) throw std::runtime_error("Receive failed");
    buffer[bytesRead] = '\0';
    return std::string(buffer);
}

void UDPSocket::shutdown() {
    if (socketFd >= 0) {
        close(socketFd);
        socketFd = -1;
    }
}