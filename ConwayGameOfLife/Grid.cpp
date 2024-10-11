#include "Grid.h"

#include <iostream>

Grid::Grid(int const length, int const height)
{
    this->length = length;
    this->height = height;
    this->flip_stack = new FlipStack<Coordinate>(std::min(length, height));

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
    for (int x = 0; x < length + 1; x++) std::cout << ". "; // Top layer of full stops
    std::cout << "\n";
    for (int y = height - 1; y >= 0; y--) // This reverses down since the top line (the first one we handle) should be
                                          // the max Y index
    {
        for (int x = 0; x < length; x++)
        {
            std::cout << '.' << (arr[x][y] ? 'O' : ' ');
        }
        std::cout << ".\n";
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
            Coordinate hold{x, y};
            if (needs_flip(hold)) *this->flip_stack << hold;
        }
        this->new_row();
    }
    this->new_row(); // TODO: Figure out if I need this
}

bool Grid::needs_flip(Coordinate const coord) const
{
    int neighbours_alive = 0;
    for (int i = coord.x - 1; i <= coord.x + 1; i++) for (int j = coord.y - 1; j <= coord.y + 1; j++)
    {
        if (!is_valid(i, j) || (i == coord.x && j == coord.y)) continue;
        if (arr[i][j] == true) neighbours_alive++;
    }
    
    if (arr[coord.x][coord.y] == true) // If target cell is alive
    {
        return neighbours_alive < 2 || neighbours_alive > 3;
    }

    // If target cell is dead
    return neighbours_alive == 3;
}

void Grid::new_row() const
{
    this->flip_stack->flip();
    Coordinate hold;
    while (this->flip_stack->get_height() > 0)
    {
        *flip_stack >> hold;
        this->flip(hold.x, hold.y);
    }
}
