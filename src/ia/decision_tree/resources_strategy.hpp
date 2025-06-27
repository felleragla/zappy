/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** RESOURCES_STRATEGY_HPP
*/

#ifndef RESOURCES_STRATEGY_HPP
    #define RESOURCES_STRATEGY_HPP
    #include "../shared/game_state.hpp"
    #include "../shared/protocol.hpp"
    #include <utility>
    #include <memory>
    #include <string>

class ResourceStrategy {
public:
    // Choix de la ressource à collecter en fonction de la position et du niveau
    static ResourceType chooseResourceToCollect(const std::shared_ptr<GameState>& gameState, 
        int playerX, int playerY, int playerLevel);
    
    // Trouve la ressource la plus proche (retourne {distance, ressource})
    static std::pair<int, ResourceType> findClosestResource(const std::shared_ptr<GameState>& gameState,
        int playerX, int playerY);
private:
    static const std::map<int, std::vector<ResourceType>> LEVEL_PRIORITIES;
};
#endif