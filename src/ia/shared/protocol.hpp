/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** PROTOCOL_HPP
*/

#ifndef PROTOCOL_HPP
    #define PROTOCOL_HPP
    #include <string>
    #include <vector>
    #include <unordered_map>
    #include <map>
    #include <string>
    #include <map>
    #include <unordered_map>
    #include <vector>

enum class ResourceType {
    FOOD, LINEMATE, DERAUMERE, SIBUR,
    MENDIANE, PHIRAS, THYSTAME
};

class ProtocolParser {
public:
    ProtocolParser();
    
    // Parsing des réponses du serveur
    std::map<ResourceType, int> parseInventory(const std::string& response) const;
    std::vector<std::vector<std::string>> parseLook(const std::string& response) const;
    std::pair<int, std::string> parseBroadcast(const std::string& response) const;
    std::string parseConnectNbr(const std::string& response) const;
    bool parseIncantationResult(const std::string& response) const;

    // Construction des commandes client
    static std::string buildForwardCommand();
    static std::string buildRightCommand();
    static std::string buildLeftCommand();
    static std::string buildLookCommand();
    static std::string buildInventoryCommand();
    static std::string buildBroadcastCommand(const std::string& message);
    static std::string buildConnectNbrCommand();
    static std::string buildForkCommand();
    static std::string buildEjectCommand();
    std::string buildTakeCommand(ResourceType resource) const;
    std::string buildSetCommand(ResourceType resource) const;
    static std::string buildIncantationCommand();

private:
    const std::unordered_map<ResourceType, std::string> _resourceNames;
    const std::unordered_map<std::string, ResourceType> _nameToResource;

    // Helpers
    std::vector<std::string> splitTiles(const std::string& tileStr) const;
    //ResourceType stringToResource(const std::string& str) const;
};

#endif