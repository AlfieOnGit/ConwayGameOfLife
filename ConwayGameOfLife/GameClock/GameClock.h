#pragma once
#include <iostream>
#include <thread>

template <typename T> class GameClock
{
public:
    GameClock(void(T::*func)(), T *obj);
    void start();
    void join();
private:
    T* obj;
    void(T::*func)();
    std::thread thread;
    int loops = 5; // TODO: Set to 0
    int DELAY = 1; // How many seconds between executions
    void run() const;
};

template <typename T>
GameClock<T>::GameClock(void(T::*func)(), T* obj)
{
    this->obj = obj;
    this->func = func;
}

template <typename T>
void GameClock<T>::start()
{
    thread = std::thread(&GameClock::run, this);
}

template <typename T>
void GameClock<T>::join()
{
    std::cout << "Joined!\n";
    thread.join();
}

template <typename T>
void GameClock<T>::run() const
{
    for (int i = 0; i < loops; i++)
    {
        (obj->*func)();
        std::this_thread::sleep_for(std::chrono::seconds(DELAY));
    }
}
