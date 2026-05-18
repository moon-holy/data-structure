#include "sort.h"
#include <iostream>

int main()
{
    std::vector<int> data = {9, 5, 2, 7, 1, 8, 3, 6, 4};

    auto test = [&](std::string_view name, auto func) {
        auto arr = data;
        func(arr);
        std::cout << name << ": ";
        sort::print(std::span<const int>(arr));
    };

    test("原始数据       ", [](auto&){});

    auto copy = data;
    sort::insertion_sort(std::span<int>(copy));
    std::cout << "insertion_sort: "; sort::print(std::span<const int>(copy));

    copy = data;
    sort::bubble_sort(std::span<int>(copy));
    std::cout << "bubble_sort   : "; sort::print(std::span<const int>(copy));

    copy = data;
    sort::selection_sort(std::span<int>(copy));
    std::cout << "selection_sort: "; sort::print(std::span<const int>(copy));

    copy = data;
    sort::quick_sort(std::span<int>(copy));
    std::cout << "quick_sort    : "; sort::print(std::span<const int>(copy));

    copy = data;
    sort::heap_sort(std::span<int>(copy));
    std::cout << "heap_sort     : "; sort::print(std::span<const int>(copy));

    copy = data;
    sort::merge_sort(std::span<int>(copy));
    std::cout << "merge_sort    : "; sort::print(std::span<const int>(copy));

    std::cout << "is_sorted? "
              << std::boolalpha << sort::is_sorted(std::span<const int>(copy)) << "\n";

    // 降序排序
    std::vector<int> desc = {1,2,3,4,5};
    sort::quick_sort(std::span<int>(desc), std::greater<int>{});
    std::cout << "降序排列: "; sort::print(std::span<const int>(desc));

    return 0;
}
