/*
Author: Mohamed Newir
Date: 15/06/2025
File: TCPsocket.cpp
Description:
            -> This file implements the TCPSocket class, which provides functionality for TCP socket programming in C++.
            -> It includes methods for waiting for a connection, sending and receiving messages, shutting down the socket,
                and connecting to a server or client.
            -> The class manages both server and client sockets and uses default values for IP address and port.
            -> This implementation is intended to be used for TCP socket operations in network programming.
*/


#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <exception>
#include "../Include/TCPsocket.hpp"

TCPSocket::TCPSocket(const std::string& ip, int port) :
    ip(ip), port(port), serverSocket(-1), clientSocket(-1) // Initialize server and client sockets to -1
                                                        // to indicate they are not yet created
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw std::runtime_error("Failed to create server socket");
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons( this -> port );
}

void TCPSocket::waitForConnect(){
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Failed to bind server socket");
    }
    if(listen(serverSocket, 3) < 0) {
        throw std::runtime_error("Failed to listen on server socket");
    }
    int addrLen = sizeof(serverAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddr, (socklen_t*)&(addrLen));
    if(clientSocket < 0) {
        throw std::runtime_error("Failed to accept client connection");
    }
}

void TCPSocket::send(const std::string& message){
    if(clientSocket < 0) {
        throw std::runtime_error("No connection established to send message");
    }
    if(::send(clientSocket, message.c_str(), message.length(), 0) < 0){
        throw std::runtime_error("No connection");
    }
}

std::string TCPSocket::receive(){
    char buffer[1024] = {0}; // Buffer to store received data
    if(clientSocket < 0) {
        throw std::runtime_error("No connection established to receive message");
    }
    recv(clientSocket, buffer, sizeof(buffer) -1, 0); // -1 to leave space for null terminator 
    return std::string(buffer); // Return the received message as a string
}

void TCPSocket::shutdown(){
    clientSocket >= 0 ? close(clientSocket) , clientSocket = -1 : clientSocket = -1; // Close client socket if it is open or reset it
    serverSocket >= 0 ? close(serverSocket) , serverSocket = -1 : serverSocket = -1; // Close server socket if it is open or reset it
}

void TCPSocket::connect(){
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0) {
        throw std::runtime_error("Failed to create client socket");
    }
    if(inet_pton(AF_INET, this -> ip.c_str(), &serverAddr.sin_addr) < 0){
        throw std::runtime_error("Invalid IP address format");
    }
    if(::connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Failed to connect to server");
    }
}

TCPSocket::~TCPSocket(){
    shutdown();
}