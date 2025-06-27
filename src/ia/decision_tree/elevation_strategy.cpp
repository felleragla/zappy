/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** DECISION_CPP
*/

#include "elevation_strategy.hpp"
#include "../shared/protocol.hpp"

bool ElevationStrategy::shouldElevate(const std::shared_ptr<GameState>& gameState, int playerX, int playerY, int playerId)
{
    std::lock_guard<std::mutex> lock(gameState->getMutex());
    
    const auto& tile = gameState->getTile(playerX, playerY);
    const int currentLevel = gameState->getPlayerLevel(playerId);
    
    // Vérification du nombre de joueurs et des ressources nécessaires selon le niveau
    switch (currentLevel) {
        case 1:
            return tile.players.size() >= 1 &&
                   tile.resources.count(ResourceType::LINEMATE) && 
                   tile.resources.at(ResourceType::LINEMATE) >= 1 &&
                   tile.resources.count(ResourceType::DERAUMERE) && 
                   tile.resources.at(ResourceType::DERAUMERE) >= 1;

        case 2:
            return tile.players.size() >= 2 &&
                   tile.resources.count(ResourceType::LINEMATE) && 
                   tile.resources.at(ResourceType::LINEMATE) >= 2 &&
                   tile.resources.count(ResourceType::DERAUMERE) && 
                   tile.resources.at(ResourceType::DERAUMERE) >= 1 &&
                   tile.resources.count(ResourceType::SIBUR) && 
                   tile.resources.at(ResourceType::SIBUR) >= 1 &&
                   tile.resources.count(ResourceType::MENDIANE) && 
                   tile.resources.at(ResourceType::MENDIANE) >= 1;

        case 3:
            return tile.players.size() >= 2 &&
                   tile.resources.count(ResourceType::LINEMATE) && 
                   tile.resources.at(ResourceType::LINEMATE) >= 2 &&
                   tile.resources.count(ResourceType::SIBUR) && 
                   tile.resources.at(ResourceType::SIBUR) >= 1 &&
                   tile.resources.count(ResourceType::PHIRAS) && 
                   tile.resources.at(ResourceType::PHIRAS) >= 2;
        case 4:
            return tile.players.size() >= 4 &&
                   tile.resources.count(ResourceType::LINEMATE) && 
                   tile.resources.at(ResourceType::LINEMATE) >= 1 &&
                   tile.resources.count(ResourceType::DERAUMERE) && 
                   tile.resources.at(ResourceType::DERAUMERE) >= 1 &&
                   tile.resources.count(ResourceType::SIBUR) && 
                   tile.resources.at(ResourceType::SIBUR) >= 2 &&
                   tile.resources.count(ResourceType::PHIRAS) && 
                   tile.resources.at(ResourceType::PHIRAS) >= 1;

        case 5:
            return tile.players.size() >= 4 &&
                tile.resources.at(ResourceType::LINEMATE) >= 4 &&
                tile.resources.at(ResourceType::DERAUMERE) >= 1 &&
                tile.resources.at(ResourceType::SIBUR) >= 2 &&
                tile.resources.at(ResourceType::MENDIANE) >= 1 &&
                tile.resources.at(ResourceType::PHIRAS) >= 3;
         case 6:
            return (tile.players.size() >= 6) &&
                   (tile.resources.at(ResourceType::LINEMATE) >= 6) &&
                   (tile.resources.at(ResourceType::DERAUMERE) >= 1) &&
                   (tile.resources.at(ResourceType::SIBUR) >= 2) &&
                   (tile.resources.at(ResourceType::MENDIANE) >= 3) &&
                   (tile.resources.at(ResourceType::PHIRAS) >= 1);

        case 7:
            return (tile.players.size() >= 6) &&
                   (tile.resources.at(ResourceType::LINEMATE) >= 6) &&
                   (tile.resources.at(ResourceType::DERAUMERE) >= 2) &&
                   (tile.resources.at(ResourceType::SIBUR) >= 2) &&
                   (tile.resources.at(ResourceType::MENDIANE) >= 2) &&
                   (tile.resources.at(ResourceType::PHIRAS) >= 2) &&
                   (tile.resources.at(ResourceType::THYSTAME) >= 1);

        default:
            return false;
    }
}

std::string ElevationStrategy::prepareElevation()
{
    return "Incantation";
}