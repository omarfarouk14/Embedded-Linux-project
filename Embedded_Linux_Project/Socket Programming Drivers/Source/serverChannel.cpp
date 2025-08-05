/*
Author: Omar Ali
Date: 25/06/2025
File: serverChannel.cpp
Description:
            -> This file implements the ServerChannel class, which extends the Channel class for server-side communication.
            -> It includes methods for starting, stopping, sending, and receiving messages over a socket.
            -> The class uses a shared pointer to manage the socket instance, ensuring proper memory management
                and cleanup of derived classes.
            -> The class is designed to handle server-specific communication logic, such as waiting for client connections and managing 
                server-side operations.
            -> The class is designed to be used in conjunction with the Socket class, which provides the underlying socket functionality.
            -> The class is designed to be extended by specific server implementations, allowing for flexibility in server communication.
            -> The class is intended to be used in network programming scenarios where a server needs to communicate with clients.      
*/


#include "../Include/serverChannel.hpp"

ServerChannel::ServerChannel(std::shared_ptr<Socket> socket) : Channel(socket) {}

void ServerChannel::start() {
    channelSocket->waitForConnect();
    send("set threshold 30 OFF"); // Initial threshold
}

void ServerChannel::stop() {
    channelSocket->shutdown();
}

void ServerChannel::send(const std::string& message) {
    channelSocket->send(message);
}

std::string ServerChannel::receive() {
    return channelSocket->receive();
}