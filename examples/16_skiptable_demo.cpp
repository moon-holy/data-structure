#include "skiptable.h"
#include <iostream>

int main()
{
    SkipList<int, std::string> sl(8);

    sl.insert(3, "three");
    sl.insert(1, "one");
    sl.insert(7, "seven");
    sl.insert(5, "five");
    sl.insert(9, "nine");
    sl.insert(2, "two");

    sl.print();

    auto v = sl.find(5);
    std::cout << "find(5) = " << (v ? *v : "not found") << "\n";

    v = sl.find(8);
    std::cout << "find(8) = " << (v ? *v : "not found") << "\n";

    std::cout << "contains(3)? " << std::boolalpha << sl.contains(3) << "\n";

    sl.erase(3);
    std::cout << "\n删除 3 后:\n";
    sl.print();

    return 0;
}
