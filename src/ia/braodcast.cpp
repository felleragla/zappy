/*
** EPITECH PROJECT, 2025
** ZAPPY_IA
** File description:
** BROADCAST_CPP
*/

#include "./include/broadcast.hpp"
#include "./include/Error.hpp"

void BroadcastHandler::sendBroadcast(const std::string& message)
{
    _network.send("Broadcast " + message);
}

std::vector<std::pair<int, std::string>> BroadcastHandler::receiveBroadcasts()
{
    std::vector<std::pair<int, std::string>> broadcasts;
    std::string response = _network.receive();
    if (response.find("message") == 0) {
        size_t commaPos = response.find(',');
        int direction = std::stoi(response.substr(8, commaPos - 8));
        std::string text = response.substr(commaPos + 2);
        broadcasts.emplace_back(direction, text);
    }
    return broadcasts;
}