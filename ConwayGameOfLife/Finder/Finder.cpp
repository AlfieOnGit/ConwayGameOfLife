#include "Finder.h"

Finder::Finder(ConwayGrid* grid)
{
    this->grid = grid;
    this->test_grid = new ConwayGrid(grid->get_length(), grid->get_height());
}

Finder::~Finder()
{
    delete test_grid;
}

bool Finder::check(int x, int y, Grid<bool>* shape)
{
    for (int i = -1; i <= shape->get_length(); i++) for (int j = -1; j <= shape->get_height(); j++)
    {
        if (!shape->is_valid(i, j) || !shape->get(i, j))
        {
            if (test_grid->is_valid(x + i,  y + j) && test_grid->get(x + i, y + j)) return false;
        }
        else
        {
            if (!test_grid->is_valid(x + i, y + j) || !test_grid->get(x + i, y + j)) return false;
        }
    }
    return true;
}
