#include "union_find.h"
#include <iostream>

int main()
{
    UnionFind uf(10);
    std::cout << "initial: " << uf.count() << " sets\n";

    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(4, 5);
    uf.unite(6, 7);
    uf.unite(8, 9);
    std::cout << "after 5 unions: " << uf.count() << " sets\n";

    uf.unite(1, 2);
    uf.unite(5, 6);
    std::cout << "after 2 more: " << uf.count() << " sets\n";

    uf.unite(3, 4);
    uf.unite(7, 8);
    uf.unite(0, 9);
    std::cout << "all connected? " << uf.count() << " set\n";

    std::cout << "same(0, 5)? " << std::boolalpha << uf.same(0, 5) << "\n";
    std::cout << "same(0, 9)? " << uf.same(0, 9) << "\n";

    uf.print();
    return 0;
}
