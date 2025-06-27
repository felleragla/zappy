/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Survival strategy implementation
*/

#include "survival_strategy.hpp"
#include "../shared/game_state.hpp"

bool SurvivalStrategy::needsFood(const GameState& gameState, int playerId) {
    auto inventory = gameState.getPlayerInventory(playerId);
    auto foodIt = inventory.find(ResourceType::FOOD);
    
    // Si on a moins de 5 unités de nourriture, on doit en chercher
    if (foodIt == inventory.end() || foodIt->second < 5) {
        return true;
    }
    
    return false;
}

std::string SurvivalStrategy::findFood(const GameState& gameState, int playerId) {
    auto playerPos = gameState.getPlayerPosition(playerId);
    int playerX = std::get<0>(playerPos);
    int playerY = std::get<1>(playerPos);
    int mapWidth = gameState.getMapWidth();
    int mapHeight = gameState.getMapHeight();
    
    // Chercher de la nourriture dans un rayon de 3 cases
    for (int radius = 0; radius <= 3; radius++) {
        for (int dx = -radius; dx <= radius; dx++) {
            for (int dy = -radius; dy <= radius; dy++) {
                if (abs(dx) + abs(dy) != radius && radius > 0) continue;
                
                int x = (playerX + dx + mapWidth) % mapWidth;
                int y = (playerY + dy + mapHeight) % mapHeight;
                
                auto tile = gameState.getTile(x, y);
                if (tile.resources.find(ResourceType::FOOD) != tile.resources.end() &&
                    tile.resources.at(ResourceType::FOOD) > 0) {
                    
                    // Calculer le chemin vers cette position
                    return calculatePath({playerX, playerY}, {x, y}, {mapWidth, mapHeight});
                }
            }
        }
    }
    
    // Si aucune nourriture trouvée, se déplacer aléatoirement
    return "Forward";
}

std::string SurvivalStrategy::calculatePath(const std::pair<int, int>& from,
                                          const std::pair<int, int>& to,
                                          const std::pair<int, int>& mapSize) {
    int dx = to.first - from.first;
    int dy = to.second - from.second;
    
    // Gérer le wrapping de la carte
    if (dx > mapSize.first / 2) dx -= mapSize.first;
    if (dx < -mapSize.first / 2) dx += mapSize.first;
    if (dy > mapSize.second / 2) dy -= mapSize.second;
    if (dy < -mapSize.second / 2) dy += mapSize.second;
    
    // Choisir la direction la plus proche
    if (abs(dx) > abs(dy)) {
        return dx > 0 ? "Right" : "Left";
    } else if (dy != 0) {
        return dy > 0 ? "Forward" : "Forward"; // Simplification: toujours forward
    }
    
    return "Forward";
}