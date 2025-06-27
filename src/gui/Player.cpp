/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Player.cpp
*/

#include "../../include/gui/Player.hpp"

int Player::getId() const 
{ 
    return _id; 
}
int Player::getX() const 
{ 
    return _x; 
}
int Player::getY() const 
{ 
    return _y; 
}
int Player::getLevel() const 
{ 
    return _level; 
}
std::string Player::getTeam() const 
{ 
    return _team; 
}
int Player::getOrientation() const
{
    return _orientation;
}
void Player::setId(int id) 
{ 
    _id = id; 
}
void Player::setX(int x) 
{ 
    _x = x; 
}

void Player::setY(int y) 
{ 
    _y = y; 
}
void Player::setOrientation(int orientation) 
{ 
    _orientation = orientation; 
}
void Player::setLevel(int level) 
{ 
    _level = level; 
}
void Player::setTeam(std::string team) 
{ 
    _team = team; 
}
std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "Player{id =" << player.getId()   
    << ", x =" << player.getX()
    << ", y =" << player.getY()
    << ", orientation =" << player.getOrientation()
    << ", level =" << player.getLevel()
    << ", team =" << player.getTeam()
    << "}";
    return os;
}

void Player::destroyPlayer(int id)
{
    _isBroadcasting = false;
    _broadcast = "";
    _lastBroadcastText = "";
    _broadcastClock.restart();
    _id = 0;
}