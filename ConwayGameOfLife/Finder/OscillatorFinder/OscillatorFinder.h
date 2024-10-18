#pragma once
#include "../../Coordinate.h"
#include "../../Grid/ConwayGrid.h"
#include "../Finder.h"

class OscillatorFinder: public Finder
{
public:
    OscillatorFinder(ConwayGrid *grid);
    ~OscillatorFinder();
    // Checks for oscillators. Returns the tick number the still life formed or -1 if no still life found
    int check();
private:
    //Grid<bool> *horizontal_blinker, *vertical_blinker; // Template for the respective shapes
    Grid<bool> *shapes[10]; // TODO: Change to 10
    FlipStack<Coordinate> *shapes_found;
    // Finds blinkers and toads in the test grid and puts them in this->shapes
    void find_shapes();
    // Checks the shapes_found list to see if any are still there from 2 ticks ago. Returns TRUE if so
    bool check_for_persistence();
    // Checks coordinates for blinkers and toads
    inline bool check_all_shapes(int x, int y);
    void make_shapes();
    void copy_flipped_values(Grid<bool> *target, Grid<bool> *from);
};
