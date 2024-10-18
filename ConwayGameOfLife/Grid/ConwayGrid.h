#pragma once
#include "Grid.h"
#include "../FlipStack/FlipStack.h"
#include "../Coordinate.h"

class ConwayGrid : public Grid<bool>
{
public:
    ConwayGrid(int length, int height);
    void print();
    // Places COUNT number of cells randomly about the grid.
    void populate(int count) const;
    void flip(int x, int y);
    void tick();
    void tick_and_print();
protected:
    FlipStack<Coordinate> *flip_stack; // Holds coordinates that need flipping (killing or reviving)
    bool needs_flip(Coordinate coord) const;
    void new_row();
};
