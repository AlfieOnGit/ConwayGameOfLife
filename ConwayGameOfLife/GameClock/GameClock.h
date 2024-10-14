#pragma once
#include <thread>

template <typename T> class GameClock
{
public:
    GameClock(void(T::*func)(), T *obj);
    void start();
    void join();
    void set_loops(int loops);
private:
    T* obj;
    void(T::*member_func)();
    std::thread thread;
    int loops = 5; // TODO: Set to 0
    int DELAY = 1; // How many seconds between executions
    void run() const;
};

template <typename T>
GameClock<T>::GameClock(void(T::*func)(), T* obj)
{
    this->obj = obj;
    this->member_func = func;
}

template <typename T>
void GameClock<T>::start()
{
    thread = std::thread(&GameClock::run, this);
}

template <typename T>
void GameClock<T>::join()
{
    thread.join();
}

template <typename T>
void GameClock<T>::run() const
{
    std::this_thread::sleep_for(std::chrono::seconds(DELAY));
    for (int i = 0; i < loops; i++)
    {
        (obj->*member_func)();
        std::this_thread::sleep_for(std::chrono::seconds(DELAY));
    }
}

template <typename T>
void GameClock<T>::set_loops(int loops)
{
    this->loops = loops;
}

