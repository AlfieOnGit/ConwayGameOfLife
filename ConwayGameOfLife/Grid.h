#pragma once
#include "FlipList/FlipList.h"

class Grid
{
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
    FlipList *flip_list;
    bool needs_flip(int x, int y) const;
    void new_row() const;
};
