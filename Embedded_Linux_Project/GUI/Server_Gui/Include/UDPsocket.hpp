/*
Author: omar ali
Date: 25/06/2025
File: UDPsocket.hpp
Description:
            -> This file defines the UDPSocket class declaration, which implements the Socket interface for UDP socket programming in C++.
            -> It provides methods for waiting for a connection, sending and receiving messages, shutting down the socket,
                and connecting to a server or client.
            -> The class includes default values for IP address and port, and manages both server and client sockets.
            -> This class is intended to be used for UDP socket operations in network programming.
*/

#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP

#include "socket.hpp"
#include <string>
#include <netinet/in.h>

class UDPSocket : public Socket {
public:
    UDPSocket(const std::string& ip = "127.0.0.1", int port = 8080);
    ~UDPSocket();
    void waitForConnect() override;
    void connect() override;
    void send(const std::string& message) override;
    std::string receive() override;
    void shutdown() override;
private:
    int socketFd;
    std::string ip;
    int port;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
};

#endif // UDPSOCKET_HPP