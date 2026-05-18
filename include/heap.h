#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * @file heap.h
 * @brief 二叉堆（Binary Heap）
 *
 * @details
 * 二叉堆是一种完全二叉树，分为大根堆（max-heap）和小根堆（min-heap）。
 * - 大根堆：每个节点的值 >= 子节点的值，根节点为最大值
 * - 小根堆：每个节点的值 <= 子节点的值，根节点为最小值
 *
 * ## 时间复杂度
 * - 插入（push）: O(log n)
 * - 删除根（pop）: O(log n)
 * - 取根（top）:  O(1)
 * - 建堆（heapify）: O(n)
 *
 * ## 应用场景
 * - 优先队列（Priority Queue）
 * - 堆排序（Heap Sort）
 * - Top-K 问题
 * - 任务调度
 *
 * @tparam T 元素类型
 * @tparam MaxHeap 是否为最大堆，true = 大根堆，false = 小根堆
 */

template <typename T, bool MaxHeap = true>
class BinaryHeap {
public:
    using value_type = T;
    using size_type  = std::size_t;

    BinaryHeap() noexcept = default;

    template <typename InputIt>
    BinaryHeap(InputIt first, InputIt last)
        : m_data(first, last)
    {
        heapify();
    }

    BinaryHeap(std::initializer_list<T> ilist)
        : m_data(ilist)
    {
        heapify();
    }

    // ============================================================
    // 容量
    // ============================================================

    [[nodiscard]] size_type size() const noexcept
    {
        return m_data.size();
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_data.empty();
    }

    // ============================================================
    // 元素访问
    // ============================================================

    /// 获取堆顶元素（最大值或最小值）
    [[nodiscard]] const T& top() const
    {
        return m_data.front();
    }

    // ============================================================
    // 修改操作
    // ============================================================

    /// 插入元素
    void push(const T& value)
    {
        m_data.push_back(value);
        sift_up(size() - 1);
    }

    void push(T&& value)
    {
        m_data.push_back(std::move(value));
        sift_up(size() - 1);
    }

    /// 删除堆顶元素
    void pop()
    {
        if (empty()) {
            return;
        }
        std::swap(m_data.front(), m_data.back());
        m_data.pop_back();
        if (!empty()) {
            sift_down(0);
        }
    }

    /// 替换堆顶元素并重新调整
    void replace_top(const T& value)
    {
        if (empty()) {
            push(value);
            return;
        }
        m_data[0] = value;
        sift_down(0);
    }

    /// 清空
    void clear() noexcept
    {
        m_data.clear();
    }

    void print(std::ostream& os = std::cout) const
    {
        for (const auto& v : m_data) {
            os << v << " ";
        }
        os << '\n';
    }

    /// 获取内部数据（用于调试或排序）
    [[nodiscard]] const std::vector<T>& data() const noexcept
    {
        return m_data;
    }

private:
    std::vector<T> m_data;

    static size_type parent(size_type i) noexcept { return (i - 1) / 2; }
    static size_type left(size_type i)   noexcept { return 2 * i + 1; }
    static size_type right(size_type i)  noexcept { return 2 * i + 2; }

    static bool cmp(const T& a, const T& b) noexcept
    {
        if constexpr (MaxHeap) {
            return a < b;  // 大根堆：子节点 > 父节点时需交换
        } else {
            return a > b;  // 小根堆：子节点 < 父节点时需交换
        }
    }

    void sift_up(size_type i) noexcept
    {
        while (i > 0 && cmp(m_data[parent(i)], m_data[i])) {
            std::swap(m_data[parent(i)], m_data[i]);
            i = parent(i);
        }
    }

    void sift_down(size_type i) noexcept
    {
        size_type extreme = i;
        size_type l = left(i);
        size_type r = right(i);

        if (l < size() && cmp(m_data[extreme], m_data[l])) {
            extreme = l;
        }
        if (r < size() && cmp(m_data[extreme], m_data[r])) {
            extreme = r;
        }
        if (extreme != i) {
            std::swap(m_data[i], m_data[extreme]);
            sift_down(extreme);
        }
    }

    void heapify() noexcept
    {
        if (size() <= 1) {
            return;
        }
        for (std::ptrdiff_t i = static_cast<std::ptrdiff_t>(size() / 2) - 1; i >= 0; --i) {
            sift_down(static_cast<size_type>(i));
        }
    }
};

#endif // DATA_STRUCTURES_HEAP_H
