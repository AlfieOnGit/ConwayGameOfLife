#include "OscillatorFinder.h"

OscillatorFinder::OscillatorFinder(ConwayGrid* grid): Finder(grid)
{
    make_shapes();
    shapes_found = new FlipStack<Coordinate>(std::max(grid->get_length(), grid->get_height()));
}

OscillatorFinder::~OscillatorFinder()
{
    for (Grid<bool> *p : shapes)
    {
        delete p;
    }
}

int OscillatorFinder::check()
{
    test_grid->copy_values(grid);
    find_shapes();
    for (int x = 0; x < MAX_TICKS; x++)
    {
        test_grid->tick();
        shapes_found->flip();
        if (check_for_persistence()) return x;
        find_shapes();
    }
    return -1;
}

void OscillatorFinder::find_shapes()
{
    for (int x = 0; x < test_grid->get_length(); x++) for (int y = 0; y < test_grid->get_height(); y++)
    {
        if (check_all_shapes(x, y)) *shapes_found << Coordinate {x, y};
    }
}

bool OscillatorFinder::check_for_persistence()
{
    for (int i = 0; i < shapes_found->get_height(); i++)
    {
        Coordinate c;
        *shapes_found >> c;
        if (check_all_shapes(c.x, c.y)) return true;
    }
    return false;
}

bool OscillatorFinder::check_all_shapes(int const x, int const y)
{
    for (Grid<bool> *p : shapes)
    {
        if (Finder::check(x, y, p)) return true;
    }
    return false;
}

void OscillatorFinder::make_shapes()
{
    shapes[0] = new Grid<bool>(3, 1, true);
    shapes[1] = new Grid<bool>(1, 3, true);
    auto *hold = new Grid<bool>(4, 4, false);
    hold->set(0, 2, true);
    hold->set(1, 0, true);
    hold->set(1, 3, true);
    hold->set(2, 0, true);
    hold->set(2, 3, true);
    hold->set(3, 1, true);
    shapes[2] = hold;

    hold = new Grid<bool>(4, 4, false);
    copy_flipped_values(hold, shapes[2]);
    shapes[3] = hold;

    hold = new Grid<bool>(4, 4, false);
    hold->copy_values(shapes[2]);
    hold->set(0, 1, true);
    hold->set(0, 2, false);
    hold->set(3, 1, false);
    hold->set(3, 2, true);
    shapes[4] = hold;

    hold = new Grid<bool>(4, 4, false);
    copy_flipped_values(hold, shapes[4]);
    shapes[5] = hold;

    hold = new Grid<bool>(2, 4, true);
    hold->set(0, 0, false);
    hold->set(1, 3, false);
    shapes[6] = hold;

    hold = new Grid<bool>(4, 2);
    copy_flipped_values(hold, shapes[6]);
    shapes[7] = hold;

    hold = new Grid<bool>(2, 4, true);
    hold->set(0, 3, false);
    hold->set(1, 0, false);
    shapes[8] = hold;

    hold = new Grid<bool>(4, 2);
    copy_flipped_values(hold, shapes[8]);
    shapes[9] = hold;
}

void OscillatorFinder::copy_flipped_values(Grid<bool>* target, Grid<bool>* from)
{
    for (int x = 0; x < from->get_length(); x++) for (int y = 0; y < from->get_height(); y++)
    {
        target->set(y, x, from->get(x, y));
    }
}
