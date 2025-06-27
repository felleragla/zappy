/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** RESOURCES_STRATEGY_CPP
*/

#include "resources_strategy.hpp"
#include <cmath>

// Définition des priorités par niveau
const std::map<int, std::vector<ResourceType>> ResourceStrategy::LEVEL_PRIORITIES = {
    {1, {ResourceType::LINEMATE, ResourceType::FOOD}},
    {2, {ResourceType::DERAUMERE, ResourceType::SIBUR, ResourceType::LINEMATE}},
    {3,{ResourceType::LINEMATE, ResourceType::SIBUR, ResourceType::PHIRAS}},
    {4, {ResourceType::LINEMATE,ResourceType::DERAUMERE, ResourceType::SIBUR, ResourceType::PHIRAS}},
    {5,{ResourceType::LINEMATE, ResourceType::DERAUMERE, ResourceType::SIBUR, ResourceType::MENDIANE}},
    {6, {ResourceType::LINEMATE, ResourceType::DERAUMERE,ResourceType::PHIRAS, ResourceType::SIBUR}},
    {7, {ResourceType::LINEMATE, ResourceType::DERAUMERE, ResourceType::SIBUR, ResourceType::PHIRAS, ResourceType::MENDIANE, ResourceType::THYSTAME}}
};

ResourceType ResourceStrategy::chooseResourceToCollect(const std::shared_ptr<GameState>& gameState,
    int x, int y, int playerLevel)
{
    // 1. Vérifier les ressources manquantes pour l'élévation
    for (const auto& resource : LEVEL_PRIORITIES.at(playerLevel)) {
        auto tile = gameState->getTile(x, y);
        if (tile.resources.count(resource) && tile.resources.at(resource) > 0) {
            return resource;
        }
    }

    // 2. Si aucune ressource prioritaire, chercher la plus proche
    auto [distance, closestRes] = findClosestResource(gameState, x, y);
    return closestRes;
}

std::pair<int, ResourceType> ResourceStrategy::findClosestResource(const std::shared_ptr<GameState>& gameState,
    int playerX, int playerY)
{
    int minDistance = std::numeric_limits<int>::max();
    ResourceType bestResource = ResourceType::FOOD; // Par défaut
    
    int width = gameState->getMapWidth();
    int height = gameState->getMapHeight();

    // Parcours circulaire autour du joueur
    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            int x = (playerX + dx + width) % width;
            int y = (playerY + dy + height) % height;
            
            auto tile = gameState->getTile(x, y);
            for (const auto& [resource, quantity] : tile.resources) {
                if (quantity > 0) {
                    int dist = std::abs(dx) + std::abs(dy);
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestResource = resource;
                    }
                }
            }
        }
    }
    return {minDistance, bestResource};
}