/*
** EPITECH PROJECT, 2025
** files
** File description:
** PROTOCOL_PARSER_CPP
*/

#include "./include/protocol_parser.hpp"
#include "./include/Error.hpp"

std::vector<std::vector<std::string>> ProtocolParser::parseLook(const std::string& response)
{
    std::string tile;
    std::vector<std::vector<std::string>> tiles;
    std::string content = response.substr(1, response.size() - 2);
    std::istringstream iss(content);

    while (std::getline(iss, tile, ',')) {
        tile.erase(std::remove_if(tile.begin(), tile.end(), ::isspace), tile.end());
        if (!tile.empty()) {
            std::vector<std::string> items;
            std::istringstream tileStream(tile);
            std::string item;
            while (tileStream >> item) items.push_back(item);
            tiles.push_back(items);
        } else {
            tiles.push_back({});
        }
    }
    return tiles;
}

void ProtocolParser::parseInventory(const std::string& response)
{
    std::string content = response.substr(1, response.size() - 2);
    std::istringstream iss(content);
    std::string itemStr;

    _inventory.clear();

    while (std::getline(iss, itemStr, ',')) {
        itemStr.erase(0, itemStr.find_first_not_of(' '));
        std::istringstream itemStream(itemStr);
        std::string name;
        int quantity;

        if (itemStream >> name >> quantity) {
            for (int i = 0; i < quantity; ++i) {
                _inventory.addItem(name);
            }
        }
    }
}

std::pair<int, std::string> ProtocolParser::parseBroadcast(const std::string& response)
{
    size_t space_pos = response.find(' ');
    size_t comma_pos = response.find(',');

    if (space_pos == std::string::npos || comma_pos == std::string::npos)
        throw Error("Invalid broadcast format");
    int direction = std::stoi(response.substr(space_pos + 1, comma_pos - space_pos - 1));
    std::string message = response.substr(comma_pos + 2);
    return {direction, message};
}

int ProtocolParser::parseConnectNbr(const std::string& response)
{
    return std::stoi(response);
}

std::pair<bool, int> ProtocolParser::parseIncantation(const std::string& response)
{
    if (response == "ko")
        return {false, 0};
    size_t colon_pos = response.find(':');
    if (colon_pos == std::string::npos)
        return {true, std::stoi(response.substr(response.rfind(' ') + 1))};
    return {true, std::stoi(response.substr(colon_pos + 2))};
}

bool ProtocolParser::parseEject(const std::string& response)
{
    return response == "ok";
}

std::pair<int, int>ProtocolParser::parseCoordinates(const std::string& response)
{
    std::istringstream iss(response);
    int x, y;
    iss >> x >> y;
    return {x, y};
}

bool ProtocolParser::parseTake(const std::string& response)
{
    return response == "ok";
}