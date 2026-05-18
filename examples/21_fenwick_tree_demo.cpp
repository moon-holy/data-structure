#include "fenwick_tree.h"
#include <iostream>

int main()
{
    FenwickTree<int> bit = {1, 3, 5, 7, 9, 11};

    std::cout << "prefix[3] = " << bit.prefix_sum(3) << "\n";  // 1+3+5+7 = 16
    std::cout << "range[1,4] = " << bit.range_sum(1, 4) << "\n";  // 3+5+7+9 = 24

    bit.add(2, 10);  // 位置2加10
    std::cout << "after add(2,10):\n";
    std::cout << "prefix[3] = " << bit.prefix_sum(3) << "\n";
    std::cout << "range[1,4] = " << bit.range_sum(1, 4) << "\n";

    bit.set(0, 0);
    std::cout << "after set(0,0): range[0,2] = " << bit.range_sum(0, 2) << "\n";

    // 逆序对计算
    std::vector<int> nums = {5, 3, 8, 1, 2};
    FenwickTree<int> bit2(10);
    int inversions = 0;
    for (int num : nums) {
        inversions += bit2.range_sum(num + 1, 9);
        bit2.add(num, 1);
    }
    std::cout << "逆序对数: " << inversions << "\n";

    return 0;
}
