#include "StillLifeFinder.h"

StillLifeFinder::StillLifeFinder(ConwayGrid *grid)
{
    this->grid = grid;
    this->test_grid = new ConwayGrid(grid->get_length(), grid->get_height());

    this->block = make_block();
    this->beehive = make_beehive();
    // The size of "shapes" should be the max amount of shapes possible
    this->shapes = new std::vector<Coordinate>;
}

StillLifeFinder::~StillLifeFinder()
{
    delete test_grid;
}

int StillLifeFinder::check()
{
    test_grid->copy_values(grid);
    find_shapes();
    for (int x = 0; x < 30; x++)
    {
        test_grid->tick();
        if (check_shapes()) return x;
        shapes->clear();
        find_shapes();
    }
    return -1;
}

void StillLifeFinder::find_shapes()
{
    for (int x = 0; x < test_grid->get_length(); x++) for (int y = 0; y < test_grid->get_height(); y++) // TODO: Maybe - beehive length and height?
    {
        if (check(x, y, block) || check(x, y, beehive)) shapes->push_back(Coordinate {x, y});
    }
}

bool StillLifeFinder::check_shapes()
{
    for (int i = 0; i < shapes->size(); i++)
    {
        Coordinate const c = shapes->at(i);
        if (check(c.x, c.y, block) || check(c.x, c.y, beehive)) return true;
    }
    return false;
}


bool StillLifeFinder::check(int x, int y, Grid<bool>* shape)
{
    for (int i = -1; i <= shape->get_length(); i++) for (int j = -1; j <= shape->get_height(); j++)
    {
        if (!shape->is_valid(i, j) || !shape->get(i, j))
        {
            if (test_grid->is_valid(x + i,  y+ j) && test_grid->get(x + i, y + j)) return false;
        }
        else
        {
            if (!test_grid->is_valid(x + i, y + j) || !test_grid->get(x + i, y + j)) return false;
        }
    }
    return true;
}

Grid<bool>* StillLifeFinder::make_block()
{
    Grid<bool> *block = new Grid<bool>(2, 2);
    for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++)
    {
        block->set(x, y, true);
    }
    return block;
}

Grid<bool>* StillLifeFinder::make_beehive()
{
    Grid<bool> *beehive = new Grid<bool>(4, 3);
    beehive->set(0, 1, true);
    beehive->set(1, 0, true);
    beehive->set(1, 2, true);
    beehive->set(2, 0, true);
    beehive->set(2, 2, true);
    beehive->set(3, 1, true);
    return beehive;
}
