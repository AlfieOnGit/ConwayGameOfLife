#include "ConwayGrid.h"

#include <iostream>

ConwayGrid::ConwayGrid(int const length, int const height): Grid(length, height)
{
    this->flip_stack = new FlipStack<Coordinate>(std::min(length, height));
}


void ConwayGrid::print() const
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

void ConwayGrid::flip(int const x, int const y) const
{
    set(x, y, !get(x, y));
}

void ConwayGrid::tick() const
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

bool ConwayGrid::needs_flip(Coordinate const coord) const
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

void ConwayGrid::new_row() const
{
    this->flip_stack->flip();
    Coordinate hold;
    while (this->flip_stack->get_height() > 0)
    {
        *flip_stack >> hold;
        this->flip(hold.x, hold.y);
    }
}
