/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Command.hpp
*/
#ifndef COMMAND_HPP_
#define COMMAND_HPP_
#include <string>
#include <unordered_map>
#include <ostream>
#include "Player.hpp"
#include "Graphical.hpp"
#pragma once
using namespace std;
class Command
{

public:
    Command(string buffer);
    // ~Command();
    int *handle_msz(string buffer);
    int *handle_bct(string buffer);
    string handle_tna(string buffer);
    Player handle_pnw(string buffer);
    Player handle_ppo(string buffer);
    Player handle_plv(string buffer);
    Player::Inventory handle_pin(string buffer);
    string handle_pex(string buffer);
    string handle_pbc(string buffer);
    Graphical::Incantation handle_pic(string buffer);
    Graphical::Incantation handle_pie(string buffer);
    int handle_pfk(string buffer);
    Player::Res handle_pdr(string buffer);
    Player handle_pgt(string buffer);
    int handle_pdi(string buffer);
    Player::Egg handle_enw(string buffer);
    Player::Egg handle_ebo(string buffer);
    int handle_edi(string buffer);
    int handle_sgt(string buffer);
    int handle_sst(string buffer);
    string handle_seg(string buffer);
    string handle_smg(string buffer);
    string handle_suc();
    string handle_spb();
    void execute(string buffer);
private:
    string _buffer;
    // std::mutex worldMutex;
    std::unordered_map<int, Player> players;
};

#endif /* _COMMAND_HPP_ */  // TODO: remove this line