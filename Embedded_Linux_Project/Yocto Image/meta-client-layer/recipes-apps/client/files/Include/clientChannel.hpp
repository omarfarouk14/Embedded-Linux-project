/*
Author: Mohamed Newir
Date: 15/06/2025
File: clientChannel.hpp
Description:
            -> This file defines the ClientChannel class, which extends the Channel class for client-side communication.
            -> It includes methods for starting, stopping, sending, and receiving messages over a socket.
            -> The class uses a shared pointer to manage the socket instance, ensuring proper memory management
                and cleanup of derived classes.
            -> The class is designed to handle client-specific communication logic, such as connecting to a server and managing client-side operations.
            -> The class is designed to be used in conjunction with the Socket class, which provides the underlying socket functionality.
            -> The class is designed to be extended by specific client implementations, allowing for flexibility in client communication.
*/


#ifndef CLIENTCHANNEL_HPP
#define CLIENTCHANNEL_HPP

#include "channel.hpp"

class ClientChannel : public Channel {
public:
    ClientChannel(std::shared_ptr<Socket> socket);
    void start() override;
    void stop() override;
    void send(const std::string& message) override;
    std::string receive() override;
};

#endif // CLIENTCHANNEL_HPP