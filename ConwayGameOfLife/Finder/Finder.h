#pragma once
#include "../Grid/ConwayGrid.h"
#include "../Grid/Grid.h"

class Finder
{
public:
    Finder(ConwayGrid *grid);
    ~Finder();
protected:
    int MAX_TICKS = 30;
    ConwayGrid *grid;
    ConwayGrid *test_grid;
    // Checks for a shape in an input coordinate
    bool check(int x, int y, Grid<bool> *shape);
};
