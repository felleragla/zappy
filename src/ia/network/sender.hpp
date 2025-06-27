/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** SENDER_HPP
*/

#ifndef SENDER_HPP
    #define SENDER_HPP
    #include "network_manager.hpp"
    #include "../shared/concurrent_queue.hpp"
    #include <thread>
    #include <atomic>
    #include <iostream>

class Sender {
public:
    Sender(NetworkManager& network, ConcurrentQueue<std::string>& commandQueue);
    ~Sender();

    void start();
    void stop();
    bool sendCommand(const std::string& command);
private:
    void run();

    NetworkManager& _network;
    ConcurrentQueue<std::string>& _commandQueue;
    std::thread _thread;
    std::atomic<bool> _running{false};
};
#endif