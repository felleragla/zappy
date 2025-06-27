/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** CONCURRENT_QUEUE_CPP
*/

#include "concurrent_queue.hpp"

template <typename T>
void ConcurrentQueue<T>::push(const T& item)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(item);
    _cond.notify_one();
}

template <typename T>
bool ConcurrentQueue<T>::pop(T& item)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _cond.wait(lock, [this]() { return !_queue.empty() || _stop; });
    if (_stop)
            return false;
    item = _queue.front();
    _queue.pop();
    return true;
}

template <typename T>
void ConcurrentQueue<T>::stop()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _stop = true;
    _cond.notify_all();
}

// Instanciations explicites pour les types couramment utilisés
template class ConcurrentQueue<int>;
template class ConcurrentQueue<std::string>;
