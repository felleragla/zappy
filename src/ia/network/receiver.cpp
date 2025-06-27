/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** RECEIVER_CPP
*/

#include "receiver.hpp"

Receiver::Receiver(NetworkManager& network, ConcurrentQueue<std::string>& responseQueue)
    : _network(network), _responseQueue(responseQueue) {}

Receiver::~Receiver()
{
    stop();
}

void Receiver::start()
{
    _running = true;
    _thread = std::thread(&Receiver::run, this);
}

void Receiver::stop()
{
    if (_running) {
        _running = false;
        if (_thread.joinable()) _thread.join();
    }
}

void Receiver::run()
{
    while (_running) {
        try {
            std::string response = _network.receive();
            _responseQueue.push(response);
        } catch (const std::exception& e) {
            // Gérer la déconnexion
            break;
        }
    }
}

bool Receiver::popResponse(std::string& response)
{
    return _responseQueue.pop(response);
}
