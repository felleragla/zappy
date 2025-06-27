/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** RECEIVER_HPP
*/

#ifndef RECEIVER_HPP
    #define RECEIVER_HPP
    #include <thread>
    #include <atomic>
    #include "network_manager.hpp"
    #include "../shared/concurrent_queue.hpp"

class Receiver {
public:
    Receiver(NetworkManager& network, ConcurrentQueue<std::string>& responseQueue);
    ~Receiver();
    void start();
    void stop();
    bool popResponse(std::string& response);

private:
    void run();

    NetworkManager& _network;
    ConcurrentQueue<std::string>& _responseQueue;
    std::thread _thread;
    std::atomic<bool> _running{false};
};
#endif