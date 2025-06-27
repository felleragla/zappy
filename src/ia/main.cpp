/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Main entry point for Zappy AI client
*/

#include "decision_tree/decision.hpp"
#include "network/network_manager.hpp"
#include "network/sender.hpp"
#include "network/receiver.hpp"
#include "shared/game_state.hpp"
#include "shared/concurrent_queue.hpp"
#include "shared/protocol.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <sstream>

struct Config {
    std::string host = "localhost";
    int port = 4242;
    std::string teamName;
};

Config parseArguments(int argc, char* argv[]) {
    Config config;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "-p" && i + 1 < argc) {
            config.port = std::stoi(argv[++i]);
        } else if (arg == "-h" && i + 1 < argc) {
            config.host = argv[++i];
        } else if (arg == "-n" && i + 1 < argc) {
            config.teamName = argv[++i];
        }
    }
    
    if (config.teamName.empty()) {
        throw std::invalid_argument("Team name is required (-n <team_name>)");
    }
    
    return config;
}

void printUsage(const char* programName) {
    std::cout << "USAGE: " << programName << " -p port -h host -n team_name\n";
    std::cout << "\tport\t\tport number\n";
    std::cout << "\thost\t\tserver hostname (default: localhost)\n";
    std::cout << "\tteam_name\tname of the team\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            printUsage(argv[0]);
            return 84;
        }
        
        Config config = parseArguments(argc, argv);
        
        std::cout << "Connecting to " << config.host << ":" << config.port 
                  << " as team " << config.teamName << std::endl;
        
        // Créer le gestionnaire réseau
        auto network = std::make_shared<NetworkManager>(config.host, config.port);
        network->connect();
        
        // Envoyer le nom de l'équipe
        network->send(config.teamName + "\n");
        
        // Recevoir la réponse du serveur (nombre de clients connectés)
        std::string response = network->receive();
        std::cout << "Server response: " << response << std::endl;
        
        // Recevoir les dimensions de la carte
        response = network->receive();
        std::cout << "Map dimensions: " << response << std::endl;
        
        // Parser les dimensions de la carte
        std::istringstream iss(response);
        int width, height;
        iss >> width >> height;
        
        // Créer les composants nécessaires
        auto commandQueue = std::make_shared<ConcurrentQueue<std::string>>();
        auto responseQueue = std::make_shared<ConcurrentQueue<std::string>>();
        auto gameState = std::make_shared<GameState>(width, height);
        
        auto sender = std::make_shared<Sender>(*network, *commandQueue);
        auto receiver = std::make_shared<Receiver>(*network, *responseQueue);
        
        // Créer le moteur de décision
        DecisionEngine engine(sender, receiver, gameState, config.teamName, config.port);
        
        // Démarrer la boucle principale de l'IA
        engine.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    
    return 0;
}