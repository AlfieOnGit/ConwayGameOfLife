#include <iostream>

#include "FlipStack.h"

int main()
{
    FlipStack<int> *flip_stack = new FlipStack<int>(10);
    flip_stack->append(1);
    flip_stack->append(2);
    flip_stack->append(3);
    std::cout << flip_stack->pop() << ", ";
    flip_stack->flip();
    std::cout << flip_stack->pop() << ", ";
    flip_stack->flip();
    std::cout << flip_stack->pop() << '\n';
    
    return 0;
}
