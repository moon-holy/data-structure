#include "bst.h"
#include <iostream>

int main()
{
    BST<int> tree = {5, 3, 7, 2, 4, 6, 8};
    std::cout << "树: "; tree.print();

    std::cout << "前序: ";
    tree.preorder([](int v) { std::cout << v << " "; });
    std::cout << "\n中序: ";
    tree.inorder([](int v) { std::cout << v << " "; });
    std::cout << "\n后序: ";
    tree.postorder([](int v) { std::cout << v << " "; });
    std::cout << "\n层序: ";
    tree.level_order([](int v) { std::cout << v << " "; });
    std::cout << "\n";

    std::cout << "min = " << tree.min().value_or(-1) << "\n";
    std::cout << "max = " << tree.max().value_or(-1) << "\n";
    std::cout << "height = " << tree.height() << "\n";

    tree.insert(1);
    tree.erase(5);
    std::cout << "插入1、删除5后: "; tree.print();

    std::cout << "contains 3? " << std::boolalpha << tree.contains(3) << "\n";
    std::cout << "contains 5? " << tree.contains(5) << "\n";

    return 0;
}
