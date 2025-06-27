/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** SENDER_CPP
*/

#include "sender.hpp"

Sender::Sender(NetworkManager& network, ConcurrentQueue<std::string>& commandQueue)
    : _network(network), _commandQueue(commandQueue) {}

Sender::~Sender() {
    stop();
}

void Sender::start() {
    _running = true;
    _thread = std::thread(&Sender::run, this);
}

void Sender::stop() {
    if (_running) {
        _running = false;
        _commandQueue.stop();
        if (_thread.joinable()) _thread.join();
    }
}

void Sender::run() {
    std::string command;
    while (_running) {
        if (_commandQueue.pop(command)) {
            try {
                _network.send(command + "\n");
            } catch (const std::exception& e) {
                // Gérer l'erreur (ex: reconnect)
                break;
            }
        }
    }
}

bool Sender::sendCommand(const std::string& command)
{
    try {
        _commandQueue.push(command);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to queue command: " << e.what() << std::endl;
        return false;
    }
}