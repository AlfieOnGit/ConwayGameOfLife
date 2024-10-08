#include "FlipStack.h"

template <typename T>
FlipStack<T>::FlipStack(int max_height)
{
    this->max_height = max_height;
    left_stack = new T[max_height];
    right_stack = new T[max_height];
}

template <typename T>
FlipStack<T>::~FlipStack()
{
    delete[] left_stack;
    delete[] right_stack;
}

template <typename T>
void FlipStack<T>::flip()
{
    currently_left = !currently_left;
}

template <typename T>
bool FlipStack<T>::append(T item)
{
    if (get_current_height() >= max_height) return false;
    get_current_stack()[get_current_height()++] = item;
    return true;
}

template <typename T>
T FlipStack<T>::pop()
{
    if (get_current_height() == 0) return nullptr;
    T hold = get_current_stack()[get_current_height()];
    get_current_stack()[get_current_height()--] = nullptr;
    return hold;
}

template <typename T>
void FlipStack<T>::clear_current_stack()
{
    for (int i = 0; i < get_current_height(); i++)
    {
        get_current_stack()[i] = nullptr;
    }
    get_current_height() = 0;
}

template <typename T>
T *&FlipStack<T>::get_current_stack()
{
    return currently_left ? left_stack : right_stack;
}

template <typename T>
int& FlipStack<T>::get_current_height()
{
    return currently_left ? left_height : right_height;
}
