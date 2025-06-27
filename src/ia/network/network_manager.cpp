/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** NETWORK_CPP
*/

#include "network_manager.hpp"
#include <iostream>

NetworkManager::NetworkManager(const std::string& host, int port) 
    : _host(host), _port(port) {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) {
        throw std::runtime_error("Socket creation failed");
    }
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port);
    inet_pton(AF_INET, _host.c_str(), &_serverAddr.sin_addr);
}

NetworkManager::~NetworkManager() {
    disconnect();
}

void NetworkManager::connect() {
    if (::connect(_sockfd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0) {
        throw std::runtime_error("Connection failed");
    }
    _connected = true;
}

void NetworkManager::disconnect() {
    if (_connected) {
        close(_sockfd);
        _connected = false;
    }
}

void NetworkManager::send(const std::string& message) {
    if (!_connected) throw std::runtime_error("Not connected");
    ::send(_sockfd, message.c_str(), message.size(), 0);
}

std::string NetworkManager::receive() {
    char buffer[4096] = {0};
    ssize_t bytesRead = recv(_sockfd, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
        disconnect();
        throw std::runtime_error("Connection closed or error");
    }
    return std::string(buffer, bytesRead);
}