#include "segment_tree.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree<int> st(arr);

    std::cout << "原数组: ";
    for (auto v : arr) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "sum[1,4] = " << st.query(1, 4) << "\n";  // 3+5+7+9 = 24

    st.update_point(2, 10);
    std::cout << "更新位置2为10, sum[0,5] = " << st.query(0, 5) << "\n";

    st.update_range(1, 3, 100);
    std::cout << "区间[1,3]+=100, sum[0,5] = " << st.query(0, 5) << "\n";

    return 0;
}
