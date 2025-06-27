/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** GAME_STATE_HPP
*/

#include "game_state.hpp"
#include "protocol.hpp"

GameState::GameState(int width, int height) 
    : _width(width), _height(height), _map(height, std::vector<Tile>(width)) {}

void GameState::updateTile(int x, int y, const Tile& tile)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _map[y][x] = tile; // Note: y avant x pour accès matriciel
}

Tile GameState::getTile(int x, int y) const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _map[y][x];
}

void GameState::updatePlayer(int playerId, int x, int y, int level)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _players[playerId] = {x, y, level};
}

void GameState::removePlayer(int playerId)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _players.erase(playerId);
}

std::tuple<int, int, int> GameState::getPlayerPosition(int playerId) const
{
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = _players.find(playerId);
    if (it != _players.end()) {
        return it->second;
    }
    throw std::runtime_error("Player ID " + std::to_string(playerId) + " not found");
}

int GameState::getPlayerLevel(int playerId) const {
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = _players.find(playerId);
    if (it != _players.end()) {
        return std::get<2>(it->second);
    }
    throw std::runtime_error("Player ID " + std::to_string(playerId) + " not found");
}

void GameState::updatePlayerInventory(int playerId, const std::map<ResourceType, int>& inventory) 
{
    std::lock_guard<std::mutex> lock(_inventoryMutex);
    _playerInventories[playerId] = inventory;
}

std::map<ResourceType, int> GameState::getPlayerInventory(int playerId) const
{
    std::lock_guard<std::mutex> lock(_inventoryMutex);
    auto it = _playerInventories.find(playerId);
    if (it != _playerInventories.end()) {
        return it->second;
    }
    return {};
}