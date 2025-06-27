/*
** EPITECH PROJECT, 2025
** files
** File description:
** TIME_MANAGER_CPP
*/

#include "./include/time_manager.hpp"
#include "../../include/gui/Error.hpp"

const std::map<std::string, int> TimeManager::_actionDelays = {
    {"Forward", 7},    {"Right", 7},     {"Left", 7},
    {"Look", 7},       {"Inventory", 1}, {"Broadcast", 7},
    {"Connect_nbr", 0}, {"Fork", 42},     {"Eject", 7},
    {"Take", 7},        {"Set", 7},       {"Incantation", 300}
};

bool TimeManager::canExecute(const std::string& actionType) const
{
    return timeUntilNextAction(actionType) <= std::chrono::milliseconds(0);
}

std::chrono::milliseconds TimeManager::timeUntilNextAction(const std::string& actionType) const
{
    auto now = std::chrono::steady_clock::now();
    auto requiredDelay = getDelay(actionType);
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastAction);
    return requiredDelay - elapsed;
}

void TimeManager::resetActionTimer()
{
    _lastAction = std::chrono::steady_clock::now();
}

void TimeManager::setFrequency(int newFreq)
{
    if (newFreq <= 0)
        throw Error("Frequency must be positive");
    _freq = newFreq;
}
