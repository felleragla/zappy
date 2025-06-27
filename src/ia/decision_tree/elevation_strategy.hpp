/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** ELEVATION_STRATEGY_HPP
*/

#ifndef ELEVATION_STRATEGY_HPP
    #define ELEVATION_STRATEGY_HPP
    #include "../shared/game_state.hpp"
    #include <memory>

class ElevationStrategy {
public:
    static bool shouldElevate(const std::shared_ptr<GameState>& gameState, int playerX, int playerY, int playerId);
    static std::string prepareElevation();
};
#endif
