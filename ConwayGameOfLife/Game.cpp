#include <iostream>
#include <ostream>

#include "Finder/StillLifeFinder/StillLifeFinder.h"
#include "GameClock/GameClock.h"
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
    
    auto *grid = new ConwayGrid(length, height);
    grid->populate(starting_live);
    auto *clock = new GameClock<ConwayGrid>(&ConwayGrid::tick_and_print, grid);
    clock->set_loops(steps);
    grid->print();
    clock->start();
    clock->join();
}

void second()
{
    int length, height, starting_live;
    std::cout << "Enter the length of the grid: ";
    std::cin >> length;
    std::cout << "Enter the height of the grid: ";
    std::cin >> height;
    std::cout << "Enter the amount of cells that will start alive in the grid: ";
    std::cin >> starting_live;
    
    auto *grid = new ConwayGrid(length, height);
    StillLifeFinder *finder = new StillLifeFinder(grid);
    grid->populate(starting_live);
    int count = 1;
    int tick_num = finder->check();
    while (tick_num == -1)
    {
        grid->clear();
        grid->populate(starting_live);
        count++;
        tick_num = finder->check();
    }

    auto *clock = new GameClock<ConwayGrid>(&ConwayGrid::tick_and_print, grid);
    clock->set_loops(tick_num);
    grid->print();
    clock->start();
    clock->join();
    std::cout << "Grids attempted: " << count << '\n';
    std::cout << "Grid tick: " << tick_num << '\n';
}

int main()
{
    int question;
    std::cout << "Enter the question number: ";
    std::cin >> question;
    switch (question)
    {
    case 1:
        first();
        break;
    case 2:
        second();
        break;
    default:
        main();
    }
    std::cout << "Enter any input to close! ";
    system("pause");
    return 0;
}
