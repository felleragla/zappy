/*
** EPITECH PROJECT, 2025
** files
** File description:
** TIME_MANAGER_HPP
*/

#ifndef TIME_MANAGER_HPP
    #define TIME_MANAGER_HPP
    #include <map>
    #include <chrono>
    #include <thread>
    #include <stdexcept>

class TimeManager {
private:
    std::chrono::steady_clock::time_point _lastAction; 
    int _freq;
    static const std::map<std::string, int> _actionDelays;

public:
    TimeManager(int freq = 100) : _freq(freq), _lastAction(std::chrono::steady_clock::now()) {}

    bool canExecute(const std::string& actionType) const;
    void resetActionTimer();
    int getFrequency() const { return _freq; }
    void setFrequency(int newFreq);
    std::chrono::milliseconds timeUntilNextAction(const std::string& actionType) const;

private:
    std::chrono::milliseconds getDelay(const std::string& actionType) const {                                                     
        try {
            int units = 0;
            return std::chrono::milliseconds((units * 1000) / _freq);
        } catch (const std::out_of_range&) {
            throw std::invalid_argument("Unknown action type: " + actionType);
        }
    }
};

// Initialisation des délais statiques (complète selon le sujet Zappy)
// const std::map<std::string, int> TimeManager::_actionDelays = {
//     {"Forward", 7},    {"Right", 7},     {"Left", 7},
//     {"Look", 7},       {"Inventory", 1}, {"Broadcast", 7},
//     {"Connect_nbr", 0}, {"Fork", 42},     {"Eject", 7},
//     {"Take", 7},        {"Set", 7},       {"Incantation", 300}
// };
#endif
