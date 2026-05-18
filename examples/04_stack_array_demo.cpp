#include "stack_array.h"
#include <iostream>

int main()
{
    ArrayStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.print();

    std::cout << "top = " << stack.top().value_or(-1) << "\n";

    stack.pop();
    std::cout << "pop 后: "; stack.print();

    auto val = stack.try_pop();
    if (val) std::cout << "try_pop = " << *val << "\n";
    std::cout << "size = " << stack.size() << "\n";
    std::cout << "empty = " << std::boolalpha << stack.empty() << "\n";

    return 0;
}
