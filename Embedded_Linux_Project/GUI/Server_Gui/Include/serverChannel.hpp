/*
Author: omar ali
Date: 25/06/2025
File: serverChannel.hpp
Description:
            -> This file defines the ServerChannel class, which extends the Channel class for server-side communication.
            -> It includes methods for starting, stopping, sending, and receiving messages over a socket.
            -> The class uses a shared pointer to manage the socket instance, ensuring proper memory management
                and cleanup of derived classes.
            -> The class is designed to handle server-specific communication logic, such as waiting for client connections and managing 
                server-side operations.
            -> The class is designed to be used in conjunction with the Socket class, which provides the underlying socket functionality.
            -> The class is designed to be extended by specific server implementations, allowing for flexibility in server communication.
            -> The class is intended to be used in network programming scenarios where a server needs to communicate with clients.  
*/

#ifndef SERVERCHANNEL_HPP
#define SERVERCHANNEL_HPP

#include "channel.hpp"

class ServerChannel : public Channel {
public:
    ServerChannel(std::shared_ptr<Socket> socket);
    void start() override;
    void stop() override;
    void send(const std::string& message) override;
    std::string receive() override;
};

#endif // SERVERCHANNEL_HPP