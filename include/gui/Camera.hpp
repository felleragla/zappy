/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Camera.hpp
*/

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera();
    
    void setPosition(const sf::Vector2f& position);
    void move(const sf::Vector2f& offset);
    
    sf::Vector2f getPosition() const { return position_; }
    
    sf::Vector2f worldToScreen(const sf::Vector2f& worldPos, const sf::Vector2u& windowSize) const;
    sf::Vector2f screenToWorld(const sf::Vector2f& screenPos, const sf::Vector2u& windowSize) const;
    
    sf::View getView(const sf::Vector2u& windowSize) const;
    
private:
    sf::Vector2f position_;
};  
#endif