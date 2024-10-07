#pragma once

class FlipList
{
public:
    FlipList(int length);
    ~FlipList();
    void add_flip(int x, int y);
    void new_row();
    void reset_current();
    int **&get_current_list();
    int &get_current_len();
private:
    int length;
    bool currently_odd;
    int **odd_list, **even_list;
    int odd_len { 0 }, even_len { 0 };
};
