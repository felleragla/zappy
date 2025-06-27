/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** PROTOCOL_CPP
*/

#include "protocol.hpp"
#include <sstream>
#include <algorithm>
#include <stdexcept>

ProtocolParser::ProtocolParser()
    : _resourceNames({
        {ResourceType::FOOD, "food"},
        {ResourceType::LINEMATE, "linemate"},
        {ResourceType::DERAUMERE, "deraumere"},
        {ResourceType::SIBUR, "sibur"},
        {ResourceType::MENDIANE, "mendiane"},
        {ResourceType::PHIRAS, "phiras"},
        {ResourceType::THYSTAME, "thystame"}
    }),
    _nameToResource({
        {"food", ResourceType::FOOD},
        {"linemate", ResourceType::LINEMATE},
        {"deraumere", ResourceType::DERAUMERE},
        {"sibur", ResourceType::SIBUR},
        {"mendiane", ResourceType::MENDIANE},
        {"phiras", ResourceType::PHIRAS},
        {"thystame", ResourceType::THYSTAME}
    }) {}

std::map<ResourceType, int> ProtocolParser::parseInventory(const std::string& response) const {
    std::map<ResourceType, int> inventory;
    if (response.empty() || response.front() != '[' || response.back() != ']') {
        throw std::invalid_argument("Invalid inventory format");
    }

    std::stringstream ss(response.substr(1, response.size() - 2));
    std::string item;
    
    while (std::getline(ss, item, ',')) {
        item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());
        size_t spacePos = item.find(' ');
        if (spacePos == std::string::npos) continue;

        std::string resourceName = item.substr(0, spacePos);
        int quantity = std::stoi(item.substr(spacePos + 1));
        
        if (auto it = _nameToResource.find(resourceName); it != _nameToResource.end()) {
            inventory[it->second] = quantity;
        }
    }
    return inventory;
}

std::vector<std::vector<std::string>> ProtocolParser::parseLook(const std::string& response) const {
    std::vector<std::vector<std::string>> tiles;
    if (response.empty() || response.front() != '[' || response.back() != ']') {
        throw std::invalid_argument("Invalid look format");
    }

    std::stringstream ss(response.substr(1, response.size() - 2));
    std::string tileStr;
    
    while (std::getline(ss, tileStr, ',')) {
        tiles.push_back(splitTiles(tileStr));
    }
    return tiles;
}

std::pair<int, std::string> ProtocolParser::parseBroadcast(const std::string& response) const {
    size_t commaPos = response.find(',');
    if (commaPos == std::string::npos) {
        throw std::invalid_argument("Invalid broadcast format");
    }

    int direction = std::stoi(response.substr(8, commaPos - 8));
    std::string message = response.substr(commaPos + 2);
    return {direction, message};
}

std::string ProtocolParser::parseConnectNbr(const std::string& response) const
{
    return response;
}

bool ProtocolParser::parseIncantationResult(const std::string& response) const
{
    return response.find("Elevation underway") != std::string::npos;
}

std::vector<std::string> ProtocolParser::splitTiles(const std::string& tileStr) const
{
    std::vector<std::string> objects;
    std::stringstream ss(tileStr);
    std::string object;
    
    while (ss >> object) {
        objects.push_back(object);
    }
    return objects;
}

std::string ProtocolParser::buildForwardCommand()
{ return "Forward\n"; }
std::string ProtocolParser::buildRightCommand()
{ return "Right\n"; }
std::string ProtocolParser::buildLeftCommand()
{ return "Left\n"; }
std::string ProtocolParser::buildLookCommand()
{ return "Look\n"; }
std::string ProtocolParser::buildInventoryCommand()
{ return "Inventory\n"; }
std::string ProtocolParser::buildBroadcastCommand(const std::string& message)
{ return "Broadcast " + message + "\n"; }
std::string ProtocolParser::buildConnectNbrCommand()
{ return "Connect_nbr\n"; }
std::string ProtocolParser::buildForkCommand()
{ return "Fork\n"; }
std::string ProtocolParser::buildEjectCommand()
{ return "Eject\n"; }
std::string ProtocolParser::buildTakeCommand(ResourceType resource) const
{ return "Take " + _resourceNames.at(resource) + "\n"; }
std::string ProtocolParser::buildSetCommand(ResourceType resource) const
{ return "Set " + _resourceNames.at(resource) + "\n"; }
std::string ProtocolParser::buildIncantationCommand()
{ return "Incantation\n"; }