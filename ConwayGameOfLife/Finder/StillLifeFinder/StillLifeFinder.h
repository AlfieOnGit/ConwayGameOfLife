#pragma once
#include <vector>

#include "../Finder.h"
#include "../../Coordinate.h"
#include "../../Grid/ConwayGrid.h"

class StillLifeFinder: public Finder
{
public:
    StillLifeFinder(ConwayGrid *grid);
    ~StillLifeFinder();
    // Checks for still life. Returns the tick number the still life formed or -1 if no still life found
    int check();
private:
    //ConwayGrid *grid; // The main grid
    //ConwayGrid *test_grid; // Copy of the main grid that can be ticked
    Grid<bool> *block, *horizontal_beehive, *vertical_beehive; // Templates for the respective shapes
    std::vector<Coordinate> *shapes_found;
    // Finds blocks and beehives in the test grid and puts them in this->shapes
    void find_shapes();
    // Checks the shapes_found list to see if any are still there. Returns TRUE if a shape has persisted 1 tick
    bool check_for_persistence();
    // Checks coordinates for blocks and beehives
    inline bool check_all_shapes(int x, int y);
    // Checks for a shape in an input coordinate
    //bool check(int x, int y, Grid<bool> *shape);
    void make_block();
    void make_beehives();
};
