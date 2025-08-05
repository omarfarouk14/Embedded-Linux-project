/*
Author: Mohamed Newir
Date: 15/06/2025
File: channel.hpp
Description:
            ->  This file defines the Channel class, which serves as an abstract base class for communication channels.
            ->  It includes methods for starting, stopping, sending, and receiving messages over a socket.
            ->  The class uses a shared pointer to manage the socket instance, ensuring proper memory management
                and cleanup of derived classes.
            ->  The class is designed to be extended by specific channel implementations, such as ClientChannel or ServerChannel.
*/

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "socket.hpp"
#include <string>
#include <memory>
class Channel {
public:
    Channel(std::shared_ptr<Socket> socket) : channelSocket(std::move(socket)) {}
    virtual ~Channel() = default; // Virtual destructor for proper cleanup of derived classes
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void send(const std::string& message) = 0;
    virtual std::string receive() = 0;
protected:
    std::shared_ptr<Socket> channelSocket; // protected member to hold the socket instance
};

#endif // CHANNEL_HPP