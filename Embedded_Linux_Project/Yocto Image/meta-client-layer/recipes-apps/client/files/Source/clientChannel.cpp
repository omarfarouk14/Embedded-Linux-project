/*
Author: Mohamed Newir
Date: 15/06/2025
File: clientChannel.cpp
Description:
            -> This file implements the ClientChannel class, which extends the Channel class for client-side communication.
            -> It includes methods for starting, stopping, sending, and receiving messages over a socket.
            -> The class uses a shared pointer to manage the socket instance, ensuring proper memory management
                and cleanup of derived classes.
            -> The class is designed to handle client-specific communication logic, such as connecting to a server and managing 
                client-side operations.
            -> The class is designed to be used in conjunction with the Socket class, which provides the underlying 
                socket functionality.
            -> The class is designed to be extended by specific client implementations, allowing for flexibility in client 
                communication.
            -> The class is intended to be used in network programming scenarios where a client needs to communicate with a server.
*/

#include <iostream>
#include "../Include/clientChannel.hpp"

ClientChannel::ClientChannel(std::shared_ptr<Socket> socket) : Channel(socket) {}

void ClientChannel::start()
{
    std::cout << "Attempting to connect to the server..." << std::endl;
    channelSocket -> connect();
    std::cout << "Connected to the server." << std::endl;
}

void ClientChannel::stop()
{
    channelSocket -> shutdown();
}
void ClientChannel::send(const std::string &message)
{
    channelSocket -> send(message);
}
std::string ClientChannel::receive()
{
    return channelSocket -> receive();
}
