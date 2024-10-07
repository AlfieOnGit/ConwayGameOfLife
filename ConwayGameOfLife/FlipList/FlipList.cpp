#include "FlipList.h"

#include <iostream>
#include <ostream>
#include <__msvc_filebuf.hpp>

FlipList::FlipList(int const length)
{
    this->length = length;
    this->odd_list = new int*[length];
    this->even_list = new int*[length];
    for (int i = 0; i < length; i++)
    {
        this->odd_list[i] = new int[2];
        this->even_list[i] = new int[2];
    }
    this->currently_odd = false;
}

FlipList::~FlipList()
{
    for (int i = 0; i < this->length; i++)
    {
        delete this->odd_list[i];
        delete this->even_list[i];
    }
    delete this->odd_list;
    delete this->even_list;
}

void FlipList::add_flip(int const x, int const y)
{
    if (!(this->currently_odd ^ (x % 2 == 0)))
    {
        std::cout << "Error called because " << x << " is x and " << currently_odd << " is currently odd\n";
        throw std::invalid_argument("X and the flip list are not both odd or both even!");
    }

    int **current = this->get_current_list();
    int const current_i = this->get_current_len();
    current[current_i][0] = x;
    current[current_i][1] = y;
    this->get_current_len()++;
}

void FlipList::new_row()
{
    this->currently_odd = !this->currently_odd;
}

void FlipList::reset_current()
{
    for (int i = 0; i < this->get_current_len(); i++)
    {
        this->get_current_list()[i] = { nullptr };
    }
    this->get_current_len() = 0;
}

// I know, it looks scary. It's actually just a reference to a 2D array (either odd or even list)
int **&FlipList::get_current_list()
{
    return this->currently_odd ? this->odd_list : this->even_list;
}

int &FlipList::get_current_len()
{
    return this->currently_odd ? this->odd_len : this->even_len;
}
