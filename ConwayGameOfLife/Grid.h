#pragma once

#include <iostream>

template <typename T> class Grid
{
public:
    Grid(int length, int height);
    ~Grid();
    // Checks if coordinates are within the bounds of the grid.
    bool is_valid(int x, int y) const;
    T get(int x, int y) const;
    void set(int x, int y, T val) const;
    int get_length() const;
    int get_height() const;
private:
    int length, height;
    T **arr; // 2D boolean array: The actual grid behind the object (usage: use "arr[x][y]" to retrieve bool value).
};

template <typename T>
Grid<T>::Grid(int const length, int const height)
{
    this->length = length;
    this->height = height;

    this->arr = new bool*[length];
    for (int i = 0; i < length; i++)
    {
        this->arr[i] = new bool[height] { false };
    }
}

template <typename T>
Grid<T>::~Grid()
{
    for (int i = 0; i < length; i++)
    {
        delete arr[i];
    }
    delete arr;
}

template <typename T>
bool Grid<T>::is_valid(int const x, int const y) const
{
    return x >= 0 && x < length && y >= 0 && y < height;
}

template <typename T>
T Grid<T>::get(int const x, int const y) const
{
    if (!is_valid(x, y))
    {
        throw std::out_of_range("Coordinate out of range");
    }

    return arr[x][y];
}


template <typename T>
void Grid<T>::set(int const x, int const y, T const val) const
{
    if (!is_valid(x, y))
    {
        throw std::out_of_range("Coordinate out of range");
    }

    arr[x][y] = val;
}

template <typename T>
int Grid<T>::get_length() const
{
    return length;
}

template <typename T>
int Grid<T>::get_height() const
{
    return height;
}
