/*
Author: Mohamed Newir
Date: 15/06/2025
File: socket.hpp
Description:
            -> This file defines the Socket interface (Abstract Class) for socket programming in C++.
            -> It declares pure virtual functions for socket operations such as waiting for a connection,
                sending messages, receiving data, shutting down the socket, and connecting.
            -> This interface is intended to be implemented by specific socket classes for different protocols (TCP/UDP).
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>

class Socket {

public:
    virtual void waitForConnect() = 0;                  // Wait for a connection from a client                         
    virtual void send(const std::string& message) = 0; // Send a message to the connected client
    virtual std::string receive() = 0;                       // Receive a message from the connected client
    virtual void shutdown() = 0;                     // Shutdown the socket connection
    virtual void connect() = 0;                     // Connect to a server or client
    virtual ~Socket() = default;                   // Virtual destructor for proper cleanup of derived classes
};

#endif // SOCKET_HPP