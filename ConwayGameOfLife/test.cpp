#include <iostream>

#include "Grid.h"

int main()
{
    auto const *grid = new Grid(5, 5);
    grid->set(1, 1, true);
    grid->print();
    grid->tick();
    grid->print();
}
