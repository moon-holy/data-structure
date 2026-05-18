#include "queue_array.h"
#include <iostream>

int main()
{
    ArrayQueue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.print();

    std::cout << "front = " << q.front().value_or(-1) << "\n";
    std::cout << "back  = " << q.back().value_or(-1) << "\n";

    auto val = q.dequeue();
    if (val) std::cout << "dequeue = " << *val << "\n";
    q.print();

    std::cout << "size = " << q.size() << "\n";
    return 0;
}
