/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** DECISION_HPP
*/

#ifndef DECISION_HPP
    #define DECISION_HPP
    #include <memory>
    #include <vector>
    #include "../network/sender.hpp"
    #include "../network/receiver.hpp"
    #include "../shared/game_state.hpp"
    #include "resources_strategy.hpp"
    #include "elevation_strategy.hpp"

class DecisionEngine {
public:
    DecisionEngine(
        std::shared_ptr<Sender> sender,
        std::shared_ptr<Receiver> receiver,
        std::shared_ptr<GameState> gameState,
        const std::string& teamName,
        int playerId
    );
    void run();
    void stop();

private:
    void processResponses();
    void decideNextAction();
    void updateStateFromResponse(const std::string& response);
    
    // Nouvelles méthodes pour une IA améliorée
    bool shouldFork(int level, const std::map<ResourceType, int>& inventory);
    ResourceType getNeededResourceForLevel(int level, const std::map<ResourceType, int>& inventory);
    void exploreForResource(ResourceType resource);
    bool shouldBroadcast();
    void intelligentExploration();
    
    // Méthodes de gestion des réponses avancées
    void updateVisionData(const std::vector<std::vector<std::string>>& tiles);
    void processTeamMessage(int direction, const std::string& message);
    void handleFailedCommand();
    void updatePlayerLevel(const std::string& response);
    void handleEjection();

    int _playerId;
    std::shared_ptr<Sender> _sender;
    std::shared_ptr<Receiver> _receiver;
    std::shared_ptr<GameState> _gameState;
    std::shared_ptr<ProtocolParser> _protocol;
    std::string _teamName;
    std::shared_ptr<ElevationStrategy> _elevation;
    std::shared_ptr<ResourceStrategy> _resources;
    std::atomic<bool> _running{false};
    bool _isElevating{false};
    std::vector<std::vector<std::string>> _lastVision;
};
#endif