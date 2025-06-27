/*
** EPITECH PROJECT, 2025
** files
** File description:
** NETWORK_CPP
*/

#include "./include/network.hpp"
#include "./include/Error.hpp"
#include <poll.h>

NetworkManager::NetworkManager(const std::string& host, int port)
{
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &_server_addr.sin_addr);
}

void NetworkManager::connect()
{
    if (::connect(_socket_fd, (struct sockaddr*)&_server_addr, sizeof(_server_addr)) < 0) {
        throw Error("Connection failed");
    }
}

void NetworkManager::send(const std::string& message)
{
    std::string msg = message + "\n";
    ::send(_socket_fd, msg.c_str(), msg.size(), 0);
}

bool NetworkManager::hasData() const {
    struct pollfd pfd = {_socket_fd, POLLIN, 0};
    return poll(&pfd, 1, 0) > 0;
}

std::string NetworkManager::receive()
{
    char buffer[4096];
    ssize_t bytes = recv(_socket_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0)
        throw Error("Connection lost");
        buffer[bytes] = '\0';
    std::cout << std::string(buffer).substr(0, bytes - 1) << std::endl; // Remove trailing \n
    return std::string(buffer).substr(0, bytes - 1); // Remove trailing \n
}

NetworkManager::~NetworkManager()
{
    close(_socket_fd);
}