#include "queue_list.h"
#include <iostream>

int main()
{
    LinkedQueue<int> q = {1, 2, 3};
    q.print();

    q.enqueue(100);
    q.enqueue(200);
    std::cout << "front = " << q.front().value_or(-1) << "\n";
    std::cout << "back  = " << q.back().value_or(-1) << "\n";

    q.dequeue();
    q.print();

    q.clear();
    std::cout << "clear 后 empty = " << std::boolalpha << q.empty() << "\n";

    return 0;
}
