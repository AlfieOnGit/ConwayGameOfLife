#pragma once
#include "Grid.h"
#include "FlipStack/FlipStack.h"

class ConwayGrid : Grid<bool>
{
protected:
    struct Coordinate
    {
        int x;
        int y;
    };
public:
    ConwayGrid(int length, int height);
    void print() const;
    void flip(int x, int y) const;
    void tick() const;
private:
    FlipStack<Coordinate> *flip_stack; // FlipStack holding int[2] arrays, index 0 being the X and 1 being the Y of cells that
                                       // need flipping
    bool needs_flip(Coordinate coord) const;
    void new_row() const;
};
