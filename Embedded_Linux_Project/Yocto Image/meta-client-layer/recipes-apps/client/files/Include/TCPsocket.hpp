/*
Author: Mohamed Newir
Date: 15/06/2025
File: TCPsocket.hpp
Description:
            -> This file defines the TCPSocket class declaration, which implements the Socket interface for TCP socket programming in C++.
            -> It provides methods for waiting for a connection, sending and receiving messages, shutting down the socket,
                and connecting to a server or client.
            -> The class includes default values for IP address and port, and manages both server and client sockets.
            -> This class is intended to be used for TCP socket operations in network programming.
*/

#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include "socket.hpp"
#include <netinet/in.h>

#define DEFAULT_IP "192.168.7.1"
#define DEFAULT_PORT 8080

class TCPSocket : public Socket {

private:
        int serverSocket;  // Socket for the server
        int clientSocket; // Socket for the client
        std::string ip;  // IP address for the connection
        int port;       // Port for the connection
        struct sockaddr_in serverAddr; // Server address structure

public:
    TCPSocket(const std::string& ip = DEFAULT_IP, int port = DEFAULT_PORT);
    void waitForConnect() override;
    void send(const std::string& message) override;;
    std::string receive() override;
    void shutdown() override;
    void connect() override;
    ~TCPSocket();
};


#endif // TCPSOCKET_HPP
