#include "ConwayGrid.h"
#include "../FlipStack/FlipStack.h"

#include <iostream>

ConwayGrid::ConwayGrid(int const length, int const height): Grid(length, height, false)
{
    this->flip_stack = new FlipStack<Coordinate>(std::min(length, height));
}

void ConwayGrid::print()
{
    std::cout << "========GRID========\n";
    for (int x = 0; x < get_length() + 1; x++) std::cout << ". "; // Top layer of full stops
    std::cout << "\n";
    // This reverses down since the top line (the first one we handle) should be the max Y index
    for (int y = get_height() - 1; y >= 0; y--)
    {
        for (int x = 0; x < get_length(); x++)
        {
            std::cout << '.' << (get(x, y) ? 'O' : ' ');
        }
        std::cout << ".\n";
    }
    std::cout << "====================\n";
}

void ConwayGrid::populate(int const count) const
{
    srand(time(nullptr));
    for (int i = 0; i < count; i++)
    {
        int const x = rand() % get_length();
        int const y = rand() % get_height();
        if (!get(x, y)) set(x, y, true); // If not already alive, make alive
        else i--; // If already alive, turn a different cell alive instead
    }
}

void ConwayGrid::flip(int const x, int const y) const
{
    set(x, y, !get(x, y));
}

void ConwayGrid::tick() const
{
    for (int x = 0; x < get_length(); x++)
    {
        for (int y = 0; y < get_height(); y++)
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
        if (get(i, j)) neighbours_alive++;
    }

    if (get(coord.x, coord.y)) // If target cell is alive
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

void ConwayGrid::tick_and_print()
{
    tick();
    print();
}

