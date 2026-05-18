#include "sparsetable.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

    // 区间最小值查询
    SparseTable<int> st_min(arr);
    std::cout << "min[1,4] = " << st_min.query(1, 4) << "\n";
    std::cout << "min[3,7] = " << st_min.query(3, 7) << "\n";

    // 区间最大值查询
    SparseTable<int> st_max(arr, [](int a, int b) { return std::max(a, b); });
    std::cout << "max[0,5] = " << st_max.query(0, 5) << "\n";
    std::cout << "max[2,8] = " << st_max.query(2, 8) << "\n";

    // 区间 GCD 查询
    SparseTable<int> st_gcd(arr, [](int a, int b) {
        while (b) { int t = b; b = a % b; a = t; }
        return a;
    });
    std::cout << "gcd[0,3] = " << st_gcd.query(0, 3) << "\n";

    return 0;
}
