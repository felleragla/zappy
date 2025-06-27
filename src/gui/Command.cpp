/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Command.cpp
*/

#include "../../include/gui/Command.hpp"
#include "../../include/gui/Graphical.hpp"
#include <iostream>
#include <sstream>
using namespace std;

Command::Command(string buffer)
{
    _buffer = buffer;
}

int *Command::handle_msz(string buffer)
{
    std::stringstream ss(buffer);
    int *msz = new int[2];
    std::string msz_line;
    ss >> msz_line >> msz[0] >> msz[1];
    return msz;
}

int *Command::handle_bct(string buffer)
{
    std::stringstream ss(buffer);
    int *bct = new int[9];
    std::string bct_line;
    ss >> bct_line >> bct[0] >> bct[1] >> bct[2] >> bct[3] >> bct[4] >> bct[5] >> bct[6] >> bct[7] >> bct[8];
    return bct;
}

string Command::handle_tna(string buffer)
{
    std::stringstream ss(buffer);
    std::string tna_line;
    std::string team_name;
    ss >> tna_line >> team_name; 
    return team_name;
}

Player Command::handle_pnw(string buffer)
{
    std::istringstream iss(buffer);
    std::string keyword, hash_id, team;
    int id, x, y, orientation, level;

    iss >> keyword >> hash_id >> x >> y >> orientation >> level >> team;
    id = std::stoi(hash_id.substr(1));

    Player p{id, x, y, orientation, level, team, "", "", false, sf::Clock()};
    players[id] = p;
    return p;
}

Player Command::handle_ppo(string buffer)
{
    std::istringstream iss(buffer);
    std::string keyword, hash_id;
    int id, x, y, orientation;

    iss >> keyword >> hash_id >> x >> y >> orientation;
    id = std::stoi(hash_id.substr(1));
    return Player{id, x, y, orientation, 0, "", "", "", false, sf::Clock()};
}

Player Command::handle_plv(string buffer)
{
    std::istringstream iss(buffer);
    std::string keyword, hash_id;
    int id, level;

    iss >> keyword >> hash_id >> level;
    id = std::stoi(hash_id.substr(1));
    return Player{id, 0, 0, 1, level, "", "", "", false, sf::Clock()};
}

Player::Inventory Command::handle_pin(string buffer)
{
    std::istringstream iss(buffer);
    std::string keyword, hash_id;
    int id, food, linemate, deraumere, sibur, mendiane, phiras, thystame;

    iss >> keyword >> hash_id >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    id = std::stoi(hash_id.substr(1));
    return Player::Inventory{food, linemate, deraumere, sibur, mendiane, phiras, thystame, id};
}

string Command::handle_pex(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd;
    int play;

    ss >> cmd >> play;
    std::cout << "Le joueur" << play << "effectue une expulsion." << std::endl;
    return std::to_string(play);
}

string Command::handle_pbc(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd;
    int player;
    std::string message;

    ss >> cmd >> message;
    std::cout << "Broadcast de" << player<< ":" << message << std::endl;
    return message;
}

Graphical::Incantation Command::handle_pic(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, x, y;

    ss >> cmd >> x >> y;
    return Graphical::Incantation{std::stoi(x), std::stoi(y), false, true};
}

Graphical::Incantation Command::handle_pie(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, x, y, res;
    ss >> cmd >> x >> y >> res;
    if (res == "ok") {
        return Graphical::Incantation{std::stoi(x), std::stoi(y), true, true};
    } else {
        return Graphical::Incantation{std::stoi(x), std::stoi(y), false, false};
    }
}

int Command::handle_pfk(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, player_id;
    int id;
    ss >> cmd >> player_id;
    id = std::stoi(player_id.substr(1));
    return id;
}

Player::Egg Command::handle_enw(string buffer)
{
   std::stringstream ss(buffer);
    std::string cmd, egg, player, x, y;
    int id;
    
    ss >> cmd >> egg >> player >> x >> y;
    id = std::stoi(egg.substr(1));
    return Player::Egg{std::stoi(x), std::stoi(y), false, id, std::stoi(player.substr(1))};
}


Player::Egg Command::handle_ebo(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, egg;
    int id;

    ss >> cmd >> egg;
    id = std::stoi(egg.substr(1));
    return Player::Egg{0, 0, true, id, 0};
}

int Command::handle_pdi(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, player;

    ss >> cmd >> player;
    return std::stoi(player.substr(1));
}

int Command::handle_edi(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, egg;

    ss >> cmd >> egg;
    return std::stoi(egg.substr(1));
}

string Command::handle_smg(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd, message;
    ss >> cmd >> message;
    return message;
}

int Command::handle_sgt(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd;
    int freq;
    ss >> cmd >> freq;
    return freq;
}

int Command::handle_sst(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd;
    int freq;
    ss >> cmd >> freq;
    return freq;
}

string Command::handle_seg(string buffer)
{
   std::stringstream ss(buffer);
    std::string cmd, teamName;
    ss >> cmd >> teamName;
    std::cout << "L'équipe gagnante est: " << teamName << std::endl;
    return buffer;
}


string Command::handle_suc() 
{
    return "Erreur: commande inconnue\n";
}

string Command::handle_spb() 
{
    return "Erreur: commande inconnue\n";
}

Player::Res Command::handle_pdr(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd;
    int id, r;
    string res, hash_id;

    ss >> cmd >> hash_id >> res;
    id = std::stoi(hash_id.substr(1));
    r = std::stoi(res.substr(1));
    return Player::Res{id, r};
}

Player Command::handle_pgt(string buffer)
{
    std::stringstream ss(buffer);
    std::string cmd;
    int player; 
    int item;
    
    ss >> cmd >> player >> item;
    return Player{player, 0, 0, 0, 0, "", "", "", false, sf::Clock()};
}   