#pragma once

#include <fstream>

template <typename T> class Grid
{
public:
    Grid(int length, int height);
    Grid(int length, int height, T default_value);
    ~Grid();
    // Checks if coordinates are within the bounds of the grid.
    bool is_valid(int x, int y) const;
    T get(int x, int y) const;
    void set(int x, int y, T val) const;
    void clear();
    void copy_values(Grid const *grid);
    void save(std::ofstream &file);
    int get_length() const;
    int get_height() const;
protected:
    T DEFAULT_VALUE = false;
private:
    int length, height;
    T **arr; // 2D T array: The actual grid behind the object (usage: use "arr[x][y]" to retrieve T value).
};

template <typename T>
Grid<T>::Grid(int const length, int const height): Grid(length, height, T(0)) { }

template <typename T>
Grid<T>::Grid(int const length, int const height, T const default_value)
{
    this->DEFAULT_VALUE = default_value;
    this->length = length;
    this->height = height;

    this->arr = new bool*[length];
    for (int i = 0; i < length; i++)
    {
        this->arr[i] = new bool[height] { DEFAULT_VALUE };
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
void Grid<T>::clear()
{
    for (int x = 0; x < length; x++) for (int y = 0; y < height; y++)
    {
        arr[x][y] = DEFAULT_VALUE;
    }
}

template <typename T>
void Grid<T>::copy_values(Grid const *grid)
{
    int const min_length = std::min(this->get_length(), grid->get_length());
    int const min_height = std::min(this->get_height(), grid->get_height());
    for (int x = 0; x < min_length; x++) for (int y = 0; y < min_height; y++)
    {
        arr[x][y] = grid->get(x, y);
    }
}

template <typename T>
void Grid<T>::save(std::ofstream &file)
{
    for (int x = 0; x < length; x++)
    {
        for (int y = 0; y < height; y++)
        {
            file << arr[x][y] << ' ';
        }
        file << '\n';
    }
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
