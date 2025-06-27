/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Camera.cpp
*/

#include "../../include/gui/Camera.hpp"

Camera::Camera() : position_(0.0f, 0.0f) {
}

void Camera::setPosition(const sf::Vector2f& position) {
    position_ = position;
}

void Camera::move(const sf::Vector2f& offset) {
    position_ += offset;
}

sf::Vector2f Camera::worldToScreen(const sf::Vector2f& worldPos, const sf::Vector2u& windowSize) const {
    sf::Vector2f center(windowSize.x / 2.0f, windowSize.y / 2.0f);
    sf::Vector2f relative = worldPos - position_;
    return center + relative;
}

sf::Vector2f Camera::screenToWorld(const sf::Vector2f& screenPos, const sf::Vector2u& windowSize) const {
    sf::Vector2f center(windowSize.x / 2.0f, windowSize.y / 2.0f);
    sf::Vector2f relative = screenPos - center;
    return position_ + relative;
}

sf::View Camera::getView(const sf::Vector2u& windowSize) const {
    sf::View view;
    view.setCenter(position_);
    view.setSize(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
    return view;
}