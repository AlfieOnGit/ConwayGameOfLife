#pragma once

// FlipStack holds two stacks and allows the user to flip() between the two. The idea is to save the user from having
// to keep checking which of the two stacks they should be handling at a given time.
template <typename T> class FlipStack
{
public:
    // Parameter "max_height" is the max height of both stacks INDIVIDUALLY, not combined.
    FlipStack(int max_height);
    ~FlipStack();
    // Appends an item to the current stack. Is safe but does NOT indicate failure (use append() if unsure).
    FlipStack &operator<<(T const &item);
    // Pops an item from the current stack and sets it to the variable. Variable will become T or NULL if no items left
    // in the current stack.
    FlipStack &operator>>(T &var);
    // Flips the focus between the left and right stacks.
    void flip();
    // Takes argument and inserts it onto the top of the current stack. Returns TRUE if successful, FALSE if the stack
    // is full.
    bool append(T item);
    // Removes and returns the top item from the current stack. Returns item or NULLPTR if the stack is empty.
    T pop();
    // Clears the current stack of all items.
    void clear();
    // Gets the height of the current stack.
    int get_height() const;
private:
    int max_height, *current_height, left_height { 0 }, right_height { 0 };
    T **current_stack, *left_stack, *right_stack;
};

template <typename T>
FlipStack<T>::FlipStack(int const max_height)
{
    this->max_height = max_height;
    left_stack = new T[max_height];
    right_stack = new T[max_height];
    current_stack = &left_stack;
    current_height = &left_height;
}

template <typename T>
FlipStack<T>::~FlipStack()
{
    delete[] left_stack;
    delete[] right_stack;
}

template <typename T>
FlipStack<T> &FlipStack<T>::operator<<(T const &item)
{
    this->append(item);
    return *this;
}

template <typename T>
FlipStack<T>& FlipStack<T>::operator>>(T& var)
{
    var = this->pop();
    return *this;
}

template <typename T>
void FlipStack<T>::flip()
{
    bool currently_left = current_stack == &left_stack;
    current_height = currently_left ? &right_height : &left_height;
    current_stack = currently_left ? &right_stack : &left_stack;
}

template <typename T>
bool FlipStack<T>::append(T item)
{
    if (*current_height >= max_height) return false;
    (*current_stack)[(*current_height)++] = item;
    return true;
}

template <typename T>
T FlipStack<T>::pop()
{
    if (*current_height == 0) return NULL;
    T hold = (*current_stack)[*current_height - 1];
    (*current_stack)[(*current_height)--] = NULL;
    return hold;
}

template <typename T>
void FlipStack<T>::clear()
{
    for (int i = 0; i < *current_height; i++)
    {
        (*current_stack)[i] = NULL;
    }
    *current_height = 0;
}

template <typename T>
int FlipStack<T>::get_height() const
{
    return *current_height;
}
