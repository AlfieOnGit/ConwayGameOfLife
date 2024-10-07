#include "Grid.h"

#include <iostream>

Grid::Grid(int const length, int const height)
{
    this->length = length;
    this->height = height;
    this->flip_list = new FlipList(std::min(length, height));

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
    std::cout << "========GRID========\n";
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < length; x++)
        {
            std::cout << arr[x][y] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "====================\n";
}

bool Grid::is_valid(int const x, int const y) const
{
    return x >= 0 && x < length && y >= 0 && y < height;
}

bool Grid::get(int const x, int const y) const
{
    if (!is_valid(x, y))
    {
        throw std::out_of_range("Coordinate out of range");
    }

    return arr[x][y];
}


void Grid::set(int const x, int const y, bool const val) const
{
    if (!is_valid(x, y))
    {
        throw std::out_of_range("Coordinate out of range");
    }

    arr[x][y] = val;
}

void Grid::flip(int const x, int const y) const
{
    set(x, y, !get(x, y));
}

void Grid::tick() const
{
    for (int x = 0; x < length; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (needs_flip(x, y)) this->flip_list->add_flip(x, y);
        }
        this->new_row();
    }
    this->new_row(); // TODO: Figure out if I need this
}

bool Grid::needs_flip(int const x, int const y) const
{
    int neighbours_alive = 0;
    for (int i = x - 1; i <= x + 1; i++) for (int j = y - 1; j <= y + 1; j++)
    {
        if (!is_valid(i, j) || (i == x && j == y)) continue;
        if (arr[i][j] == true) neighbours_alive++;
    }
    
    if (arr[x][y] == true) // If target cell is alive
    {
        return neighbours_alive < 2 || neighbours_alive > 3;
    }

    // If target cell is dead
    return neighbours_alive == 3;
}

void Grid::new_row() const
{
    this->flip_list->new_row();
    int** current = this->flip_list->get_current_list();
    std::cout << "Current list len is: " << this->flip_list->get_current_len() << '\n'; // DEBUG
    for (int i = 0; i < this->flip_list->get_current_len(); i++)
    {
        this->flip(current[i][0], current[i][1]);
        std::cout << "Flip called on: " << current[i][0] << ", " << current[i][1] << "!\n"; // DEBUG
    }
    this->flip_list->reset_current();
}
