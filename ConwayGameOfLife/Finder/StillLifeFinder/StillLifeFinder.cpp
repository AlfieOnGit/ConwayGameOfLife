#include "StillLifeFinder.h"

StillLifeFinder::StillLifeFinder(ConwayGrid *grid): Finder(grid)
{
    make_block();
    make_beehives();
    this->shapes_found = new std::vector<Coordinate>;
}

StillLifeFinder::~StillLifeFinder()
{
    delete block;
    delete horizontal_beehive;
    delete shapes_found;
}

int StillLifeFinder::check()
{
    test_grid->copy_values(grid);
    find_shapes();
    for (int x = 0; x < MAX_TICKS; x++)
    {
        test_grid->tick();
        if (check_for_persistence()) return x;
        shapes_found->clear();
        find_shapes();
    }
    return -1;
}

void StillLifeFinder::find_shapes()
{
    for (int x = 0; x < test_grid->get_length(); x++) for (int y = 0; y < test_grid->get_height(); y++)
    {
        if (check_all_shapes(x, y)) shapes_found->push_back(Coordinate {x, y});
    }
}

bool StillLifeFinder::check_for_persistence()
{
    for (int i = 0; i < shapes_found->size(); i++)
    {
        Coordinate const c = shapes_found->at(i);
        if (check_all_shapes(c.x, c.y)) return true;
    }
    return false;
}

bool StillLifeFinder::check_all_shapes(int const x, int const y)
{
    return Finder::check(x, y, block) || Finder::check(x, y, horizontal_beehive) || Finder::check(x, y, vertical_beehive);
}

void StillLifeFinder::make_block()
{
    block = new Grid<bool>(2, 2);
    for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++)
    {
        block->set(x, y, true);
    }
}

void StillLifeFinder::make_beehives()
{
    vertical_beehive = new Grid<bool>(4, 3);
    vertical_beehive->set(0, 1, true);
    vertical_beehive->set(1, 0, true);
    vertical_beehive->set(1, 2, true);
    vertical_beehive->set(2, 0, true);
    vertical_beehive->set(2, 2, true);
    vertical_beehive->set(3, 1, true);

    horizontal_beehive = new Grid<bool>(3, 4);
    for (int x = 0; x < vertical_beehive->get_length(); x++) for (int y = 0; y < vertical_beehive->get_height(); y++)
    {
        horizontal_beehive->set(y, x, vertical_beehive->get(x, y));
    }
}
