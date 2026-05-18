#include "queue_circular.h"
#include <iostream>

int main()
{
    CircularQueue<int> q(4);
    std::cout << "capacity = " << q.capacity() << "\n";

    for (int i = 1; i <= 4; ++i) q.enqueue(i * 10);
    q.print();

    std::cout << "front = " << q.front().value_or(-1) << "\n";
    std::cout << "back  = " << q.back().value_or(-1) << "\n";

    q.dequeue();
    q.dequeue();
    q.print();
    std::cout << "size = " << q.size() << "\n";

    // 自动扩容测试
    for (int i = 0; i < 10; ++i) q.enqueue(i);
    q.print();
    std::cout << "new capacity = " << q.capacity() << "\n";

    return 0;
}
