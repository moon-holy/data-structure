#include "heap.h"
#include <iostream>

int main()
{
    // 大根堆
    BinaryHeap<int, true> max_heap = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "大根堆: "; max_heap.print();
    std::cout << "top = " << max_heap.top() << "\n";

    max_heap.pop();
    std::cout << "pop 后 top = " << max_heap.top() << "\n";

    max_heap.push(10);
    std::cout << "push 10 后 top = " << max_heap.top() << "\n";

    // 小根堆
    BinaryHeap<int, false> min_heap = {3, 1, 4, 1, 5, 9};
    std::cout << "小根堆: "; min_heap.print();
    std::cout << "min = " << min_heap.top() << "\n";

    // 堆排序：利用堆
    std::vector<int> v = {5, 3, 8, 1, 2, 7};
    BinaryHeap<int, true> h(v.begin(), v.end());
    std::cout << "堆排序结果: ";
    while (!h.empty()) {
        std::cout << h.top() << " ";
        h.pop();
    }
    std::cout << "\n";

    return 0;
}
