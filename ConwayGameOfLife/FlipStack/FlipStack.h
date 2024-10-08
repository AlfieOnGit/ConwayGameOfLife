#pragma once

// FlipStack holds two stacks and allows the user to flip() between the two. The idea is to save the user from having
// to keep checking which of the two stacks they should be handling at a given time.
template <typename T> class FlipStack
{
public:
    // Parameter "max_height" is the max height of both stacks INDIVIDUALLY, not combined.
    FlipStack(int max_height);
    ~FlipStack();
    // Flips the focus between the left and right stacks.
    void flip();
    // Takes argument and inserts it onto the top of the current stack. Returns TRUE if successful, FALSE if the stack
    // is full.
    bool append(T item);
    // Removes and returns the top item from the current stack. Returns item or NULLPTR if the stack is empty.
    T pop();
    void clear_current_stack();
private:
    bool currently_left = true;
    int max_height, left_height { 0 }, right_height { 0 };
    T *left_stack, *right_stack;
    T *&get_current_stack();
    int &get_current_height();
};
