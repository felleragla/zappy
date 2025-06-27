/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** DECISION_CPP
*/

#include <thread>
#include "decision.hpp"
#include "../shared/protocol.hpp"

DecisionEngine::DecisionEngine(
    std::shared_ptr<Sender> sender,
    std::shared_ptr<Receiver> receiver,
    std::shared_ptr<GameState> gameState,
    const std::string& teamName,
    int playerId
) : _playerId(playerId), _sender(sender), _receiver(receiver), _gameState(gameState), _protocol(std::make_shared<ProtocolParser>()), _teamName(teamName), _elevation(std::make_shared<ElevationStrategy>()), _resources(std::make_shared<ResourceStrategy>()) {}

void DecisionEngine::run() {
    _running = true;
    while (_running) {
        processResponses();
        decideNextAction();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Évite la surcharge CPU
    }
}

void DecisionEngine::processResponses() {
    std::string response;
    while (_receiver->popResponse(response)) {
        updateStateFromResponse(response);
    }
}

void DecisionEngine::updateStateFromResponse(const std::string& response) {
    try {
        if (response.find("[player") != std::string::npos || response.find("[") != std::string::npos) {
            // Mise à jour de la vision - analyser les cases visibles
            auto tiles = _protocol->parseLook(response);
            updateVisionData(tiles);
        }
        else if (response.find("[food") != std::string::npos || response.find("linemate") != std::string::npos) {
            auto inventory = _protocol->parseInventory(response);
            _gameState->updatePlayerInventory(_playerId, inventory);
        }
        else if (response.find("message") != std::string::npos) {
            auto [direction, msg] = _protocol->parseBroadcast(response);
            processTeamMessage(direction, msg);
        }
        else if (response == "ok") {
            // Commande exécutée avec succès
        }
        else if (response == "ko") {
            // Commande échouée - adapter la stratégie
            handleFailedCommand();
        }
        else if (response.find("Elevation underway") != std::string::npos) {
            // Incantation en cours
            _isElevating = true;
        }
        else if (response.find("Current level:") != std::string::npos) {
            // Niveau mis à jour après élévation
            _isElevating = false;
            updatePlayerLevel(response);
        }
        else if (response == "dead") {
            stop();
        }
        else if (response.find("eject:") != std::string::npos) {
            // Éjecté par un autre joueur
            handleEjection();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing response: " << e.what() << std::endl;
    }
}

void DecisionEngine::decideNextAction() {
    auto playerPos = _gameState->getPlayerPosition(_playerId);
    int x = std::get<0>(playerPos);
    int y = std::get<1>(playerPos);
    int level = std::get<2>(playerPos);
    auto inventory = _gameState->getPlayerInventory(_playerId);
    auto tile = _gameState->getTile(x, y);

    // 1. Vérifier la survie - priorité absolue
    if (inventory[ResourceType::FOOD] < 3) {
        if (tile.resources.count(ResourceType::FOOD) && tile.resources.at(ResourceType::FOOD) > 0) {
            _sender->sendCommand(_protocol->buildTakeCommand(ResourceType::FOOD));
            return;
        }
        // Chercher de la nourriture
        exploreForResource(ResourceType::FOOD);
        return;
    }

    // 2. Stratégie de reproduction - créer des œufs si nécessaire
    if (shouldFork(level, inventory)) {
        _sender->sendCommand(_protocol->buildForkCommand());
        return;
    }

    // 3. Vérifier si on peut s'élever
    if (_elevation->shouldElevate(_gameState, x, y, _playerId)) {
        _sender->sendCommand(_protocol->buildIncantationCommand());
        return;
    }

    // 4. Collecter les ressources nécessaires pour l'élévation
    ResourceType neededResource = getNeededResourceForLevel(level, inventory);
    if (neededResource != ResourceType::FOOD) {
        if (tile.resources.count(neededResource) && tile.resources.at(neededResource) > 0) {
            _sender->sendCommand(_protocol->buildTakeCommand(neededResource));
            return;
        }
        // Chercher la ressource nécessaire
        exploreForResource(neededResource);
        return;
    }

    // 5. Coordination d'équipe - diffuser des informations
    if (shouldBroadcast()) {
        std::string message = "level:" + std::to_string(level) + ",pos:" + std::to_string(x) + "," + std::to_string(y);
        _sender->sendCommand(_protocol->buildBroadcastCommand(message));
        return;
    }

    // 6. Exploration intelligente
    intelligentExploration();
}

bool DecisionEngine::shouldFork(int level, const std::map<ResourceType, int>& inventory) {
    // Fork seulement si on a assez de nourriture et qu'on est à un niveau approprié
    return (level >= 2 && inventory.at(ResourceType::FOOD) > 10 && 
            (level == 2 || level == 4 || level == 6)); // Niveaux stratégiques
}

ResourceType DecisionEngine::getNeededResourceForLevel(int level, const std::map<ResourceType, int>& inventory) {
    // Retourne la première ressource manquante pour le niveau actuel
    switch (level) {
        case 1:
            if (inventory.at(ResourceType::LINEMATE) < 1) return ResourceType::LINEMATE;
            break;
        case 2:
            if (inventory.at(ResourceType::LINEMATE) < 1) return ResourceType::LINEMATE;
            if (inventory.at(ResourceType::DERAUMERE) < 1) return ResourceType::DERAUMERE;
            if (inventory.at(ResourceType::SIBUR) < 1) return ResourceType::SIBUR;
            break;
        case 3:
            if (inventory.at(ResourceType::LINEMATE) < 2) return ResourceType::LINEMATE;
            if (inventory.at(ResourceType::SIBUR) < 1) return ResourceType::SIBUR;
            if (inventory.at(ResourceType::PHIRAS) < 2) return ResourceType::PHIRAS;
            break;
        case 4:
            if (inventory.at(ResourceType::LINEMATE) < 1) return ResourceType::LINEMATE;
            if (inventory.at(ResourceType::DERAUMERE) < 1) return ResourceType::DERAUMERE;
            if (inventory.at(ResourceType::SIBUR) < 2) return ResourceType::SIBUR;
            if (inventory.at(ResourceType::PHIRAS) < 1) return ResourceType::PHIRAS;
            break;
        case 5:
            if (inventory.at(ResourceType::LINEMATE) < 1) return ResourceType::LINEMATE;
            if (inventory.at(ResourceType::DERAUMERE) < 2) return ResourceType::DERAUMERE;
            if (inventory.at(ResourceType::SIBUR) < 1) return ResourceType::SIBUR;
            if (inventory.at(ResourceType::MENDIANE) < 3) return ResourceType::MENDIANE;
            break;
        case 6:
            if (inventory.at(ResourceType::LINEMATE) < 1) return ResourceType::LINEMATE;
            if (inventory.at(ResourceType::DERAUMERE) < 2) return ResourceType::DERAUMERE;
            if (inventory.at(ResourceType::SIBUR) < 3) return ResourceType::SIBUR;
            if (inventory.at(ResourceType::PHIRAS) < 1) return ResourceType::PHIRAS;
            break;
        case 7:
            if (inventory.at(ResourceType::LINEMATE) < 2) return ResourceType::LINEMATE;
            if (inventory.at(ResourceType::DERAUMERE) < 2) return ResourceType::DERAUMERE;
            if (inventory.at(ResourceType::SIBUR) < 2) return ResourceType::SIBUR;
            if (inventory.at(ResourceType::MENDIANE) < 2) return ResourceType::MENDIANE;
            if (inventory.at(ResourceType::PHIRAS) < 2) return ResourceType::PHIRAS;
            if (inventory.at(ResourceType::THYSTAME) < 1) return ResourceType::THYSTAME;
            break;
    }
    return ResourceType::FOOD; // Aucune ressource spécifique nécessaire
}

void DecisionEngine::exploreForResource(ResourceType resource) {
    (void)resource; // Éviter l'avertissement de paramètre non utilisé
    // Utiliser la commande Look pour voir les alentours
    _sender->sendCommand(_protocol->buildLookCommand());
    
    // Mouvement intelligent basé sur la vision
    // Pour l'instant, mouvement aléatoire amélioré
    int move = rand() % 4;
    switch (move) {
        case 0: _sender->sendCommand(_protocol->buildForwardCommand()); break;
        case 1: _sender->sendCommand(_protocol->buildLeftCommand()); break;
        case 2: _sender->sendCommand(_protocol->buildRightCommand()); break;
        case 3: _sender->sendCommand(_protocol->buildInventoryCommand()); break; // Vérifier l'inventaire
    }
}

bool DecisionEngine::shouldBroadcast() {
    // Diffuser périodiquement pour coordonner l'équipe
    static int broadcastCounter = 0;
    return (++broadcastCounter % 20 == 0); // Tous les 20 cycles
}

void DecisionEngine::intelligentExploration() {
    // Exploration plus intelligente - éviter de tourner en rond
    static int lastMove = -1;
    static int sameMovesCount = 0;
    
    int move = rand() % 3;
    
    // Éviter de répéter le même mouvement trop souvent
    if (move == lastMove) {
        sameMovesCount++;
        if (sameMovesCount > 3) {
            move = (move + 1) % 3; // Changer de direction
            sameMovesCount = 0;
        }
    } else {
        sameMovesCount = 0;
    }
    
    lastMove = move;
    
    switch (move) {
        case 0: _sender->sendCommand(_protocol->buildForwardCommand()); break;
        case 1: _sender->sendCommand(_protocol->buildLeftCommand()); break;
        case 2: _sender->sendCommand(_protocol->buildRightCommand()); break;
    }
}

void DecisionEngine::updateVisionData(const std::vector<std::vector<std::string>>& tiles) {
    _lastVision = tiles;
    // Analyser les cases visibles pour optimiser les déplacements
    // La première case est toujours la position actuelle du joueur
}

void DecisionEngine::processTeamMessage(int direction, const std::string& message) {
    (void)direction; // Éviter l'avertissement de paramètre non utilisé pour l'instant
    // Traiter les messages de coordination d'équipe
    if (message.find("level:") != std::string::npos) {
        // Message de statut d'un coéquipier
        // Extraire niveau et position pour coordination
    }
    else if (message.find("help") != std::string::npos) {
        // Demande d'aide d'un coéquipier
        // Considérer se diriger vers la source du message
    }
    else if (message.find("incantation") != std::string::npos) {
        // Invitation à une incantation
        // Se diriger vers la source si on a le bon niveau
    }
}

void DecisionEngine::handleFailedCommand() {
    // Gérer les échecs de commandes
    // Par exemple, si on ne peut pas prendre un objet, il n'est peut-être plus là
    // Adapter la stratégie en conséquence
}

void DecisionEngine::updatePlayerLevel(const std::string& response) {
    // Extraire le nouveau niveau du message "Current level: X"
    size_t pos = response.find("Current level: ");
    if (pos != std::string::npos) {
        int newLevel = std::stoi(response.substr(pos + 15, 1));
        auto playerPos = _gameState->getPlayerPosition(_playerId);
        int x = std::get<0>(playerPos);
        int y = std::get<1>(playerPos);
        _gameState->updatePlayer(_playerId, x, y, newLevel);
    }
}

void DecisionEngine::handleEjection() {
    // Gérer l'éjection par un autre joueur
    // Recalculer la position et adapter la stratégie
    _sender->sendCommand(_protocol->buildLookCommand());
}

void DecisionEngine::stop() {
    _running = false;
}