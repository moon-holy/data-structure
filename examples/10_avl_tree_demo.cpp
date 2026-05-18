#include "avl_tree.h"
#include <iostream>

int main()
{
    AVLTree<int> tree = {10, 20, 30, 40, 50, 25};
    std::cout << "AVL树: "; tree.print();
    std::cout << "高度: " << tree.height() << "\n";

    std::cout << "中序: ";
    tree.inorder([](int v) { std::cout << v << " "; });
    std::cout << "\n";

    tree.insert(5);
    tree.insert(15);
    std::cout << "插入5, 15后: "; tree.print();

    tree.erase(30);
    std::cout << "删除30后: "; tree.print();

    std::cout << "contains 25? " << std::boolalpha << tree.contains(25) << "\n";
    std::cout << "contains 100? " << tree.contains(100) << "\n";
    std::cout << "min = " << tree.min().value_or(-1) << "\n";
    std::cout << "max = " << tree.max().value_or(-1) << "\n";

    return 0;
}
