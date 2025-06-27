/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Survival strategy header
*/

#ifndef SURVIVAL_STRATEGY_HPP
    #define SURVIVAL_STRATEGY_HPP

#include <string>
#include <utility>

class GameState;

class SurvivalStrategy {
    public:
        // Vérifie si le joueur a besoin de nourriture
        static bool needsFood(const GameState& gameState, int playerId);
        
        // Trouve et retourne la commande pour aller chercher de la nourriture
        static std::string findFood(const GameState& gameState, int playerId);
        
    private:
        // Calcule le chemin optimal entre deux points
        static std::string calculatePath(const std::pair<int, int>& from,
            const std::pair<int, int>& to, const std::pair<int, int>& mapSize);
};
#endif