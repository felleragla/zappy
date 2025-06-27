/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** gui.cpp
*/

#include "../../include/gui/Graphical.hpp"
#include "../../include/gui/Error.hpp"
#include "../../include/gui/Command.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <unordered_map>
#include <signal.h>

void Graphical::init()
{
    _window = new sf::RenderWindow(sf::VideoMode(1200, 600), "Zappy");
    _font = new sf::Font();
    _font->loadFromFile("resources/font.ttf");
    _tiles = new Tile[10000];
    _clock.restart();
    time = _clock.getElapsedTime().asSeconds();
}

void Graphical::drawText(const std::string &text, int x, int y)
{
    sf::Text _text;
    _text.setFont(*_font);
    _text.setString(text);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineColor(sf::Color::Black);
    _text.setOutlineThickness(1);
    _text.setCharacterSize(12);
    _text.setPosition(x, y);
    _window->draw(_text);
}

void Graphical::drawText(const std::string &text, int size, int x, int y)
{
    sf::Text _text;
    _text.setFont(*_font);
    _text.setString(text);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineColor(sf::Color::Black);
    _text.setOutlineThickness(1);
    _text.setCharacterSize(size);
    _text.setPosition(x, y);
    _window->draw(_text);
}

void Graphical::drawSprite(int x, int y, const std::string &sprite)
{
    sf::Sprite _sprite = sf::Sprite();
    sf::Texture _texture = sf::Texture();
    sf::Vector2f scale(x, y);
    sf::Vector2f position;
    _window->draw(_sprite);
}

void Graphical::clearScreen()
{
    _window->clear(sf::Color::Black);
}

int Graphical::setPlayerOrientation(int orientation)
{
    if (orientation >= 1 && orientation <= 4) {
        if (orientation == 1) {
            return 0;
        } else if (orientation == 2) {
            return 90;
        } else if (orientation == 3) {
            return 180;
        } else if (orientation == 4) {
            return 270;
        }
    }
    return 0;
}

void Graphical::drawSprite(int x, int y, double scal, const std::string &sprite)
{
    sf::Sprite _sprite = sf::Sprite();
    sf::Texture _texture = sf::Texture();
    sf::Vector2f scale(scal, scal);
    _texture.loadFromFile(sprite.c_str());
    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y); 
    _sprite.setScale(scale);
    _window->draw(_sprite);
}

void Graphical::refreshScreen()
{
    //Input();    
    //_window->clear(sf::Color::Black);   
    //_window->draw(sprite);                   
    _window->display();                      
}


bool Graphical::isOpen() const
{
    return _window->isOpen();
}

void Graphical::close()
{
    if (_window) {
        _window->close();
    }
    if (_font) {
        delete _font;
        _font = nullptr;
    }
}

int Graphical::getInput()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            close();
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Q:
                    _camera.move(sf::Vector2f(15, 0));
                    break;
                case sf::Keyboard::D:
                    _camera.move(sf::Vector2f(-15, 0));
                    break;
                case sf::Keyboard::Z:
                    _camera.move(sf::Vector2f(0, 15));
                    break;
                case sf::Keyboard::S:
                    _camera.move(sf::Vector2f(0, -15));
                    break;
            }
        }
    }
    
    return 0; 
}

std::string Graphical::connectServer(const std::string &host, int port) 
{
    sockaddr_in serv_addr{};
    char buffer[1024];
    std::string buffer_str;

    setSock(socket(AF_INET, SOCK_STREAM, 0));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr);
    if (connect(getSock(), (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        throw Error("Connexion au serveur échouée");
    send(getSock(), "GRAPHIC\n", 8, 0);
    printf("GRAPHIC\n");
    while (recv(getSock(), buffer, sizeof(buffer) - 1, 0) > 0)
        buffer_str += buffer;
    std::cout << "buffer_str: " << buffer_str << std::endl;
    return buffer_str;
}

void Graphical::send_command(const std::string &arg) 
{
    if (getSock() < 0)
        throw Error("socket non connecté");
    if (send(getSock(), arg.c_str(), arg.size(), 0) < 0)
        throw Error("impossible d'envoyer la commande");
    return;
}

void Graphical::drawTile(const Tile &tile)
{
    drawSprite(tile.x * 66, tile.y * 66, 1, "resources/herbe.jpeg");
    for (int i = 0; i < tile.food; ++i) {
        drawSprite(tile.x * 66 + (i * 4), tile.y * 66, 0.8, "resources/food.png");
    }
    for (int i = 0; i < tile.linemate; ++i)
        drawSprite(tile.x * 66 + (i * 4), tile.y * 66 + 25, 0.3, "resources/linemate.png");
    for (int i = 0; i < tile.deraumere; ++i)
        drawSprite(tile.x * 66 + 20 + (i * 4), tile.y * 66 + 25,  0.3,"resources/deraumere.png");
    for (int i = 0; i < tile.sibur; ++i)
        drawSprite(tile.x * 66 + 40 + (i * 4), tile.y * 66 + 25 ,  0.3,"resources/sibur.png");
    for (int i = 0; i < tile.mendiane; ++i)
        drawSprite(tile.x * 66 + (i * 4), tile.y * 66 + 45, 0.3, "resources/mendiane.png");
    for (int i = 0; i < tile.phiras; ++i)
        drawSprite(tile.x * 66 + 20 + (i * 4), tile.y * 66 + 45 , 0.3, "resources/phiras.png");
    for (int i = 0; i < tile.thystame; ++i)
        drawSprite(tile.x * 66 + 40 + (i * 4), tile.y * 66 + 45, 0.3, "resources/thystame.png");
}

void Graphical::addPlayer(Player player)
{
    _players[player.getId()] = player;
}

void Graphical::updatePlayer(Player player)
{
    if (_players.find(player.getId()) != _players.end()) {
        _players[player.getId()].setId(player.getId());
        _players[player.getId()].setX(player.getX());
        _players[player.getId()].setY(player.getY());
        _players[player.getId()].setOrientation(player.getOrientation());
    }
}

void Graphical::updateLevel(Player player)
{
    if (_players.find(player.getId()) != _players.end()) {
        _players[player.getId()].setLevel(player.getLevel());
    }
}

sf::Color getColor(const std::string& team)
{
    int somme = 0;
    for (char c : team) {
        somme += static_cast<unsigned char>(c);
    }
    int colorIndex = somme % 8;

    switch (colorIndex) {
        case 0:
            return sf::Color::Blue;
        case 1:
            return sf::Color::Red;
        case 2:
            return sf::Color::Green;
        case 3:
            return sf::Color::Yellow;
        case 4:
            return sf::Color::Magenta;
        case 5:
            return sf::Color::Cyan;
        case 6:
            return sf::Color(255, 165, 0);
        case 7:
            return sf::Color(128, 0, 128);
        default:
            return sf::Color::White;
    }
}

void Graphical::drawBroadcast(Player player)
{
    if (!player.isBroadcasting()) return;
    if (player.isBroadcastExpired()) return;

    sf::RectangleShape broadcast_rect;
    sf::Text broadcast_text;
    broadcast_text.setFont(*_font);
    broadcast_text.setString(player.getLastBroadcastText());
    broadcast_text.setFillColor(sf::Color::Black);
    broadcast_text.setCharacterSize(10);
    sf::FloatRect text_bounds = broadcast_text.getLocalBounds();
    float rect_width = text_bounds.width + 10;
    float rect_height = text_bounds.height + 5;
    broadcast_rect.setSize(sf::Vector2f(rect_width, rect_height));
    broadcast_rect.setFillColor(sf::Color::White);
    broadcast_rect.setOutlineColor(sf::Color::Black);
    broadcast_rect.setOutlineThickness(1);
    float rect_x = player.getX() * 66 + 33 - rect_width / 2; 
    float rect_y = player.getY() * 66 - rect_height - 10; 
    broadcast_rect.setPosition(rect_x - 60, rect_y + 10);
    broadcast_text.setPosition(rect_x - 55, rect_y + 10);
    if (_clock.getElapsedTime().asSeconds() < 3.0) {
        _window->draw(broadcast_rect);
        _window->draw(broadcast_text);
    }
}

void Graphical::drawIncantation(Incantation incantation)
{
    float incantation_time = _clock.getElapsedTime().asSeconds();
    sf::CircleShape circle(40);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(4);
    circle.setPosition(incantation.x * 66 - 72, incantation.y * 66 - 10);
    circle.setOutlineColor(sf::Color::Black);
    if (incantation.is_started) {
        if (incantation.is_success) {
            circle.setOutlineColor(sf::Color::Green);
            if (incantation_time - time > 3.0) {
                incantation.is_success = false;
                return;
            }
        } else {
            circle.setOutlineColor(sf::Color::Red);
        }
        _window->draw(circle);
    }
}

void Graphical::drawPlayers(Command command)
{
    size_t pos_pbc = 0;
    while ((pos_pbc = getBuffer().find("pbc", pos_pbc)) != std::string::npos) {
        size_t end_pbc = getBuffer().find('\n', pos_pbc);
        std::string pbc_line = getBuffer().substr(pos_pbc, end_pbc - pos_pbc);
        std::istringstream iss(pbc_line);
        std::string cmd, broadcast_player_id, message;
        iss >> cmd >> broadcast_player_id >> message;
        try {
            int id_brd = std::stoi(broadcast_player_id.substr(1));
            if (_players.find(id_brd) != _players.end()) {
                _players[id_brd].startBroadcast(message);
            }
        } catch (const std::exception& e) {
            printf("Erreur lors de la conversion de l'ID du joueur : %s\n", e.what());
        }
        pos_pbc = (end_pbc != std::string::npos) ? end_pbc + 1 : getBuffer().length();
    }
    for (const auto& pair : _players) {
        sf::CircleShape circle(12);
        sf::RectangleShape broadcast(sf::Vector2f(100, 100));
        circle.setFillColor(getColor(pair.second.getTeam()));
        const Player& player = pair.second;
        sf::Sprite playerSprite;
        sf::Texture playerTexture;
        playerTexture.loadFromFile("resources/trantor.png");
        playerSprite.setTexture(playerTexture);
        playerSprite.setScale(0.8f, 0.8f);
        playerSprite.setPosition(player.getX() * 66, player.getY() * 66);
        playerSprite.setRotation(setPlayerOrientation(player.getOrientation()));
        circle.setPosition(player.getX() * 66 - 40, player.getY() * 66 + 13);
        _window->draw(playerSprite);
        _window->draw(circle);
        drawText(std::to_string(player.getLevel()), player.getX() * 66 - 30, player.getY() * 66 + 16);
        drawBroadcast(pair.second);
    }
}

void Graphical::updateInventory(Player::Inventory inventory, int id)
{
    if (_players.find(id) != _players.end()) {
        _players[id].setInventory(inventory);
    }
}

void Graphical::layingEgg(int player_id)
{
    if (_players.find(player_id) != _players.end()) {
        _players[player_id].layingEgg();
    }
    if (_players[player_id].isLayingEgg()) {
        sf::CircleShape circle(15);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(3);
        circle.setPosition(_players[player_id].getX() * 66 - 43, _players[player_id].getY() * 66 + 10);
        _window->draw(circle);
    }
}

void Graphical::addEgg(Player::Egg egg)
{
    _players[egg.playerId].addEgg(egg.x, egg.y, egg.id, egg.playerId);
    if (!_players[egg.playerId].isEggHatched(egg.id)) {
        drawSprite(egg.x * 66 + 21, egg.y * 66 + 8, 0.5, "resources/egg.png");
    }
}

void Graphical::hatchEgg(int egg_id)
{
    if (_players.find(egg_id) != _players.end()) {
        _players[egg_id].hatchEgg(egg_id);
    }
    if (_players[egg_id].isEggHatched(egg_id)) {
        _players[egg_id].removeEgg(egg_id);
    }
}

void Graphical::destroyPlayer(int id)
{
    if (_players.find(id) != _players.end()) {
        _players[id].destroyPlayer(id);
        _players.erase(id);
    }
}

void Graphical::destroyEgg(int id)
{
    for (auto& pair : _players) {
        pair.second.removeEgg(id);
    }
}

void Graphical::gameOver(std::string teamName)
{
    drawText("Game Over", 30, 400, 200);
    drawText("La team " + teamName + " a win.", 30, 400, 230);
}

void Graphical::updateCamera()
{
    if (_window) {
        sf::Vector2u windowSize = _window->getSize();
        sf::View cameraView = _camera.getView(windowSize);
        _window->setView(cameraView);
    }
}

void Graphical::addTeam(Team team)
{
    team.color = getColor(team.name);
    if (std::find(_teams.begin(), _teams.end(), team) == _teams.end()) {
        _teams.push_back(team);
    }
}

void Graphical::drawListTeam(std::vector<Team> teams)
{
    if (!_window)
        return;
    sf::Vector2u windowSize = _window->getSize();
    float rect_width = 300;
    float rect_height = 40 * teams.size() + 20;
    float rect_x = windowSize.x - rect_width - 10; 
    float rect_y = 10; 
    sf::View oldView = _window->getView();
    sf::View uiView(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    _window->setView(uiView);
    sf::RectangleShape background(sf::Vector2f(rect_width, rect_height));
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2);
    background.setPosition(rect_x, rect_y);
    _window->draw(background);
    int i = 0;
    for (const auto& team : teams) {
        float y = rect_y + 10 + i * 40;
        sf::RectangleShape name_rect(sf::Vector2f(180, 30));
        name_rect.setFillColor(sf::Color::Black);
        name_rect.setOutlineColor(sf::Color::White);
        name_rect.setOutlineThickness(1);
        name_rect.setPosition(rect_x + 10, y);
        _window->draw(name_rect);
        sf::Text team_name;
        if (_font) {
            team_name.setFont(*_font);
        }
        team_name.setString(team.name);
        team_name.setCharacterSize(18);
        team_name.setFillColor(sf::Color::White);
        team_name.setPosition(rect_x + 20, y + 4);
        _window->draw(team_name);
        sf::RectangleShape color_rect(sf::Vector2f(40, 30));
        color_rect.setFillColor(team.color);
        color_rect.setOutlineColor(sf::Color::White);
        color_rect.setOutlineThickness(1);
        color_rect.setPosition(rect_x + 200, y);
        _window->draw(color_rect);
        i++;
    }
    _window->setView(oldView);
}

void Graphical::updateRes(Player::Res res)
{
    if (_players.find(res.id) != _players.end()) {
        _players[res.id].setInventory(Player::Inventory{0, 0, 0, 0, 0, 0, 0, res.res});
    }
}