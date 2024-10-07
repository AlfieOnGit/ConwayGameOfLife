#include "Grid.h"

#include <iostream>

Grid::Grid(int const length, int const height)
{
    this->length = length;
    this->height = height;

    this->arr = new bool*[length];
    for (int i = 0; i < length; i++)
    {
        this->arr[i] = new bool[height] { false };
    }
}

Grid::~Grid()
{
    for (int i = 0; i < length; i++)
    {
        delete arr[i];
    }
    delete arr;
}

void Grid::print() const
{
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < length; x++)
        {
            std::cout << arr[x][y] << ' ';
        }
        std::cout << '\n';
    }
}

bool Grid::get(int const x, int const y) const
{
    if (x < 0 || x >= length || y < 0 || y >= height)
    {
        throw std::out_of_range("Coordinate out of range");
    }

    return arr[x][y];
}


void Grid::set(int const x, int const y, bool const val) const
{
    if (x < 0 || x >= length || y < 0 || y >= height)
    {
        throw std::out_of_range("Coordinate out of range");
    }

    arr[x][y] = val;
}
