#include "linklist_single.h"
#include <iostream>

int main()
{
    SingleLinkedList<int> list = {3, 1, 4, 1, 5, 9};
    std::cout << "原始: "; list.print();

    list.push_front(0);
    list.push_back(99);
    std::cout << "头插0 + 尾插99: "; list.print();

    list.insert(3, 42);
    std::cout << "位置3插入42: "; list.print();

    list.erase(0);
    std::cout << "删除位置0: "; list.print();

    list.sort();
    std::cout << "排序后: "; list.print();

    auto val = list.get(2);
    if (val) std::cout << "位置2的值: " << *val << "\n";

    auto pos = list.locate(5);
    if (pos) std::cout << "5 的位置: " << *pos << "\n";

    return 0;
}
