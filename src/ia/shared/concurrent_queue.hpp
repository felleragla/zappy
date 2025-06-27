/*
** EPITECH PROJECT, 2025
** Zappy AI Network Manager
** File description:
** CONCURRENT_QUEUE_HPP
*/

#ifndef CONCURRENT_QUEUE_HPP
    #define CONCURRENT_QUEUE_HPP
    #include <queue>
    #include <mutex>
    #include <condition_variable>
    #include <string>

template <typename T>
class ConcurrentQueue {
    public:
        // Ajoute un élément à la file
        void push(const T& item);
        // Retire un élément de la file (bloquant)
        bool pop(T& item);
        // Arrête toutes les opérations bloquantes
        void stop();

    private:
        std::queue<T> _queue;
        std::mutex _mutex;
        std::condition_variable _cond;
        bool _stop = false;
};
#endif