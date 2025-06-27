/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** NETWORK_HPP
*/
#ifndef NETWORK_HPP
    #define NETWORK_HPP
    #include <string>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdexcept>

class NetworkManager {
public:
    NetworkManager(const std::string& host, int port);
    ~NetworkManager();

    void connect();
    void disconnect();
    void send(const std::string& message);
    std::string receive();

    bool isConnected() const { return _connected; }

private:
    int _sockfd;
    struct sockaddr_in _serverAddr;
    bool _connected = false;
    std::string _host;
    int _port;
};
#endif