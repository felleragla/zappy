/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** GAME_STATE_HPP
*/

#ifndef GAME_STATE_HPP
    #define GAME_STATE_HPP
    #include <vector>
#include <map>
#include <mutex>
#include <string>
#include <tuple>
#include <stdexcept>
#include "protocol.hpp"

struct Tile {
    std::map<ResourceType, int> resources;
    std::vector<int> players;
};

class GameState {
public:
    GameState(int width, int height);
    
    void updateTile(int x, int y, const Tile& tile);
    Tile getTile(int x, int y) const;

    void updatePlayer(int playerId, int x, int y, int level);
    void removePlayer(int playerId);

    int getMapWidth() const { return _width; }
    int getMapHeight() const { return _height; }

    std::tuple<int, int, int> getPlayerPosition(int playerId) const;
    std::mutex& getMutex() const { return _mutex; }

    int getPlayerLevel(int playerId) const;
    void updatePlayerInventory(int playerId, const std::map<ResourceType, int>& inventory);

    std::map<ResourceType, int> getPlayerInventory(int playerId) const;

private:
    int _width;
    int _height;
    std::vector<std::vector<Tile>> _map;
    mutable std::mutex _mutex;
    std::map<int, std::tuple<int, int, int>> _players; // ID -> (x, y, level)
    std::map<int, std::map<ResourceType, int>> _playerInventories;
    mutable std::mutex _inventoryMutex;
};
#endif