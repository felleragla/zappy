/*
** EPITECH PROJECT, 2025
** ZAPPY_AI
** File description:
** INVENTORY_CPP
*/

#include "./include/InventoryManager.hpp"
#include "./include/Error.hpp"

Inventorymanager::Inventorymanager()
{
    const std::string items[] = {"food", "linemate",
        "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    for (const auto& item : items) {
        _inventory[item] = 0;
    }
}

Inventorymanager::~Inventorymanager() {}

void Inventorymanager::addItem(const std::string& item)
{
    if (_inventory.find(item) == _inventory.end()) {
        throw Error("Invalid item: " + item);
    }
    _inventory[item]++;
}

void Inventorymanager::removeItem(const std::string& item)
{
    if (!hasItem(item)) {
        throw Error("Cannot remove missing item: " + item);
    }
    _inventory[item]--;
}

bool Inventorymanager::hasItem(const std::string& item, int quantity) const
{
    auto it = _inventory.find(item);
    return (it != _inventory.end()) && (it->second >= quantity);
}

int Inventorymanager::getItemCount(const std::string& item) const
{
    auto it = _inventory.find(item);
    return (it != _inventory.end()) ? it->second : 0;
}

void Inventorymanager::clear()
{
    for (auto& [item, count] : _inventory) {
        count = 0;
    }
}

void Inventorymanager::logInventory() const {
    std::cout << "=== INVENTAIRE ===" << std::endl;
    for (const auto& [item, count] : _inventory) {
        if (count > 0) {
            std::cout << "- " << item << ": " << count << std::endl;
        }
    }
}

const std::map<std::string, int>& Inventorymanager::getInventory() const
{
    return _inventory;
}