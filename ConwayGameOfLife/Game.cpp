#include <iostream>
#include <ostream>

#include "Finder/OscillatorFinder/OscillatorFinder.h"
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
    char save;
    std::cout << "Save grid? (y/n) ";
    std::cin >> save;
    if (save == 'Y' || save == 'y')
    {
        std::ofstream file("grid.txt");
        grid->save(file);
        file.close();
    }
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

void third()
{
    int length, height, starting_live;
    std::cout << "Enter the length of the grid: ";
    std::cin >> length;
    std::cout << "Enter the height of the grid: ";
    std::cin >> height;
    std::cout << "Enter the amount of cells that will start alive in the grid: ";
    std::cin >> starting_live;
    
    auto *grid = new ConwayGrid(length, height);
    auto *finder = new OscillatorFinder(grid);
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

void sixth()
{
    char inp = ' ';
    std::ifstream file("grid.txt");
    while (inp != '\0') // TODO: Make work
    {
        file >> inp;
        std::cout << inp << "_";
    }
    file.close();
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
    case 3:
        third();
        break;
    case 6:
        sixth();
        break;
    default:
        main();
    }
    std::cout << "Enter any input to close! ";
    system("pause");
    return 0;
}
