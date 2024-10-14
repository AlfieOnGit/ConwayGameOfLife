#include <iostream>
#include <ostream>

#include "Grid/ConwayGrid.h"

void first()
{
    int length, height, starting_live, steps;
    std::cout << "Enter the length of the grid: ";
    std::cin >> length;
    std::cout << "Enter the height of the grid: ";
    std::cin >> height;
    std::cout << "Enter the amount of cells that will start alive in the grid: ";
    std::cin >> starting_live;
    std::cout << "Enter the number of steps the grid will take: ";
    std::cin >> steps;
    std::cout << "Length: " << length << ", height: " << height << ", starting_live: " << starting_live << ", steps: " << steps << '\n';
    
    auto const *grid = new ConwayGrid(length, height);
    grid->print();
}

void two()
{
    auto const *grid = new ConwayGrid(10, 10);
    grid->populate(5);
    grid->print();
    grid->clear();
    grid->print();
}

int main()
{
    //first();
    two();
    return 0;
}
