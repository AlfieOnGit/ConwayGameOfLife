#pragma once
#include "FlipStack/FlipStack.h"

class Grid
{
protected:
    struct Coordinate
    {
        int x;
        int y;
    };
public:
    Grid(int length, int height);
    ~Grid();
    void print() const;
    bool is_valid(int x, int y) const;
    bool get(int x, int y) const;
    void set(int x, int y, bool val) const;
    void flip(int x, int y) const;
    void tick() const;
private:
    int length, height;
    bool **arr; // 2D boolean array: The actual grid behind the object (usage: use "arr[x][y]" to retrieve bool value)
    FlipStack<Coordinate> *flip_stack; // FlipStack holding int[2] arrays, index 0 being the X and 1 being the Y of cells that
    // need flipping
    bool needs_flip(Coordinate coord) const;
    void new_row() const;
};
