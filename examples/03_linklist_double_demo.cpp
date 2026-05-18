#include "linklist_double.h"
#include <iostream>

int main()
{
    DoubleLinkedList<int> list = {10, 20, 30, 40};
    std::cout << "原始: "; list.print();

    list.push_front(5);
    list.push_back(50);
    std::cout << "头插5 + 尾插50: "; list.print();

    list.insert(2, 25);
    std::cout << "位置2插入25: "; list.print();

    list.pop_front();
    list.pop_back();
    std::cout << "头删+尾删: "; list.print();

    list.erase(1);
    std::cout << "删除位置1: "; list.print();

    std::cout << "front = " << list.front().value_or(-1) << "\n";
    std::cout << "back  = " << list.back().value_or(-1) << "\n";
    std::cout << "size  = " << list.size() << "\n";

    return 0;
}
