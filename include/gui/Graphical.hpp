/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Graphical.hpp
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <arpa/inet.h>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unordered_map>
#include <chrono>
#include "Player.hpp"
#include "Camera.hpp"
class Command; // Forward declaration
#pragma once
class Graphical {
    public:
        Graphical(int port, std::string &host) {
            _port = port;
            _host = host;
            _buffer = "";
            _clock = sf::Clock();
            time = 0;
        }
        ~Graphical() {};
        void init();
        void clearScreen();
        void drawText(const std::string &text, int x, int y);
        void drawText(const std::string &text, int size, int x, int y);
        void drawSprite(int x, int y, const std::string &sprite);
        void drawSprite(int x, int y, double scale, const std::string &sprite);
        void refreshScreen();
        bool isOpen() const;
        void close();
        std::string connectServer(const std::string &host, int port);
        int getInput();
        void updateLevel(Player player);
        void updateInventory(Player::Inventory inventory, int id);
        int getPort() {
            return _port;
        }
        void drawBroadcast(Player player);
        std::string getHost() {
            return _host;
        }
        std::string getBuffer() {
            return _buffer;
        }
        void setBuffer(std::string buffer) {
            _buffer = buffer;
        }
        int setPlayerOrientation(int orientation);
        void updateRes(Player::Res res);
        void send_command(const std::string &arg);
        Player* getPlayerById(int id) {
            auto it = _players.find(id);
            if (it != _players.end())
                return &it->second;
            return nullptr;
        }
    struct Tile {
        int x, y;
        int food = 0;
        int linemate = 0;
        int deraumere = 0;
        int sibur = 0;
        int mendiane = 0;
        int phiras = 0;
        int thystame = 0;
        std::vector<int> player_ids; // ID des joueurs présents sur la tuile
        bool incanting = false;      // Si une incantation est en cours
        bool has_egg = false;        // Si un œuf est présent
    };
    struct Incantation {
        int x;
        int y;
        bool is_success = false;
        bool is_started = false;
        friend std::ostream &operator<<(std::ostream &os, const Incantation &incantation) {
            os << "Incantation.x: " << incantation.x << " " << "Incantation.y: " << incantation.y << " " << "Incantation.is_success: " << incantation.is_success << " " << "Incantation.is_started: " << incantation.is_started;
            return os;
        }
    };
    struct Team {
        std::string name;
        sf::Color color;
        bool operator==(const Team& other) const {
            return name == other.name;
        }
    };
    void drawListTeam(std::vector<Team> teams);
    void addTeam(Team team);
    std::vector<Team> getTeams() {
        return _teams;
    }
    Incantation getIncantation() {
        return _incantation;
    }
    void setIncantation(Incantation incantation) {
        _incantation = incantation;
    }
    Tile *getTiles(int x, int y) {
        return _tiles;
    }
    sf::RenderWindow *getWindow() {
        return _window;
    }
    float getTime() {
        return time;
    }
    int getSock() {
        return _sock;
    }
    void setSock(int sock) {
        _sock = sock;
    }
    void drawTile(const Tile &tile);
    void addPlayer(Player player);
    void updatePlayer(Player player);
    void drawPlayers(Command command);
    void drawIncantation(Incantation incantation);
    void layingEgg(int player_id);
    void addEgg(Player::Egg egg);
    void hatchEgg(int egg_id);
    void destroyPlayer(int id);
    void destroyEgg(int id);
    void gameOver(std::string teamName);
    sf::Clock getClock() {
        return _clock;
    }
    void setTime(float time) {
        this->time = time;
    }
    void updateCamera();
    Camera& getCamera() { return _camera; }
    
    private:    
        int _port;
        std::string _host;
        std::string _buffer;
        sf::RenderWindow *_window;
        sf::Event _event;
        sf::Font *_font;
        Tile *_tiles;
        std::unordered_map<int, Player> _players;
        std::unordered_map<int, std::chrono::steady_clock::time_point> _broadcast_timestamps;
        Incantation _incantation;
        sf::Clock _clock;
        float time;
        Camera _camera;
        std::vector<Team> _teams;
        int _sock;
};