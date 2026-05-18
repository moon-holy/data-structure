#include "search.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> ordered = {1, 3, 5, 7, 9, 11, 13, 15};

    auto pos = bin_search(std::span<const int>(ordered), 7);
    std::cout << "bin_search 7: " << (pos ? std::to_string(*pos) : "not found") << "\n";

    pos = bin_search(std::span<const int>(ordered), 6);
    std::cout << "bin_search 6: " << (pos ? std::to_string(*pos) : "not found") << "\n";

    pos = bin_search_recursive(std::span<const int>(ordered), 13, 0, ordered.size());
    std::cout << "bin_search_recursive 13: " << (pos ? std::to_string(*pos) : "not found") << "\n";

    auto lb = lower_bound(std::span<const int>(ordered), 6);
    std::cout << "lower_bound 6: " << (lb ? std::to_string(*lb) : "not found")
              << " (value=" << (lb ? std::to_string(ordered[*lb]) : "?") << ")\n";

    auto ub = upper_bound(std::span<const int>(ordered), 7);
    std::cout << "upper_bound 7: " << (ub ? std::to_string(*ub) : "not found")
              << " (value=" << (ub ? std::to_string(ordered[*ub]) : "?") << ")\n";

    // 顺序查找
    std::vector<int> unsorted = {9, 3, 7, 1, 8, 4};
    pos = seq_search(std::span<const int>(unsorted), 7);
    std::cout << "seq_search 7: " << (pos ? std::to_string(*pos) : "not found") << "\n";

    return 0;
}
