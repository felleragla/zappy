/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <ostream>
#include <SFML/System.hpp>
using namespace std;
class Player {
    public:
        Player() = default;
        Player(int id, int x, int y, int orientation, int level, std::string team, string broadcast, string lastBroadcastText, bool isBroadcasting, sf::Clock broadcastClock) {
            _id = id;
            _x = x;
            _y = y;
            _orientation = orientation;
            _level = level;
            _team = team;
            _broadcast = broadcast;
            _lastBroadcastText = lastBroadcastText;
            _isBroadcasting = isBroadcasting;
            _broadcastClock = broadcastClock;
        }
        ~Player() = default;
        int getId() const;
        int getX() const;
        int getY() const ;
        sf::Clock getBroadcastClock() const;
        int getOrientation() const;
        int getLevel() const ;
        std::string getTeam() const;
        std::string getBroadcast() const { return _broadcast; }
        std::string getLastBroadcastText() const { return _lastBroadcastText; }
        bool isBroadcasting() const { return _isBroadcasting; }
        void setId(int id);
        void setX(int x);
        void setY(int y);
        void setBroadcast(string broadcast) { _broadcast = broadcast; }
        void setLastBroadcastText(string lastBroadcastText) { _lastBroadcastText = lastBroadcastText; }
        void setIsBroadcasting(bool isBroadcasting) { _isBroadcasting = isBroadcasting; }
        void setBroadcastClock(sf::Clock broadcastClock) { _broadcastClock = broadcastClock; }
        void setOrientation(int orientation);
        void setLevel(int level);
        void setTeam(std::string team);
        void startBroadcast(const std::string& message) {
             _broadcastClock.restart();
            _isBroadcasting = true;
            _lastBroadcastText = message;
        }
        void destroyPlayer(int id);
        bool isBroadcastExpired() const {
            float elapsed = _broadcastClock.getElapsedTime().asSeconds();
            return elapsed > 3.0f;
        }
        struct Res {
            int id;
            int res;
        };
        
        void checkAndStopBroadcast() {
            if (_isBroadcasting && isBroadcastExpired()) {
                _isBroadcasting = false;
            }
        }
        struct Inventory {
            int food;
            int linemate;
            int deraumere;
            int sibur;
            int mendiane;
            int phiras;
            int thystame;
            int id;
        };
        void setInventory(Inventory inventory) {
            _inventory = inventory;
        }
        Inventory getInventory() const {
            return _inventory;
        }   
        void layingEgg() {
            _layingEgg = true;
        }
        bool isLayingEgg() const {
            return _layingEgg;
        }
        struct Egg {
            int x;
            int y;
            bool isHatched = false;
            int id;
            int playerId;
            friend ostream& operator<<(ostream& os, const Egg& egg) {
                os << "Egg: " << egg.x << ", " << egg.y << ", " << egg.isHatched << ", " << egg.id << ", " << egg.playerId;
                return os;
            }
            
        };
        void addEgg(int x, int y, int id, int playerId) {
            _eggs[id] = Egg{x, y, false, id, playerId};
        }
        void hatchEgg(int id) {
            _eggs[id].isHatched = true;
        }
        bool isEggHatched(int id) const {
            return _eggs.at(id).isHatched;
        }
        void removeEgg(int id) {
            _eggs.erase(id);
        }
        std::unordered_map<int, Egg> getEggs() const {
            return _eggs;
        }
    private:
        int _id;
        int _x;
        int _y;
        int _orientation;
        int _level;
        std::string _team;
        Inventory _inventory;
        string _broadcast;
        string _lastBroadcastText;
        bool _isBroadcasting;
        sf::Clock _broadcastClock;
        bool _layingEgg = false;
        std::unordered_map<int, Egg> _eggs;
};

#endif