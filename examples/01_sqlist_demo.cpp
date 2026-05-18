#include "sqlist.h"
#include <iostream>

int main()
{
    // 初始化列表构造
    SqList<int> list = {1, 2, 3, 4, 5};
    std::cout << "原始: "; list.print();

    // 插入
    list.insert(2, 99);
    std::cout << "在位置2插入99: "; list.print();

    // 删除
    list.erase(0);
    std::cout << "删除位置0: "; list.print();

    // 查找
    auto pos = list.locate(99);
    if (pos) std::cout << "99 的位置: " << *pos << "\n";

    // 随机访问
    std::cout << "list[1] = " << list[1] << "\n";
    std::cout << "size = " << list.size() << "\n";

    return 0;
}
