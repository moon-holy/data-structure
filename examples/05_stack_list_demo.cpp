#include "stack_list.h"
#include <iostream>

int main()
{
    LinkedStack<int> stack = {1, 2, 3};
    stack.print();

    stack.push(4);
    stack.push(5);
    std::cout << "top = " << stack.top().value_or(-1) << "\n";

    auto val = stack.try_pop();
    if (val) std::cout << "pop = " << *val << "\n";
    stack.print();

    std::cout << "size = " << stack.size() << "\n";
    return 0;
}
