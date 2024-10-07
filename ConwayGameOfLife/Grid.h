#pragma once

class Grid
{
public:
    Grid(int length, int height);
    ~Grid();
    void print() const;
    bool get(int x, int y) const;
    void set(int x, int y, bool val) const;
private:
    int length, height;
    bool **arr; // 2D boolean array: The actual grid behind the object (usage: use "arr[x][y]" to retrieve bool value)
};
