#ifndef DATA_STRUCTURES_FENWICK_TREE_H
#define DATA_STRUCTURES_FENWICK_TREE_H

#include <iostream>
#include <span>
#include <vector>

/**
 * @file fenwick_tree.h
 * @brief 树状数组 / 二叉索引树（Fenwick Tree / Binary Indexed Tree, BIT）
 *
 * @details
 * 树状数组是一种用于维护数组前缀和的数据结构，支持高效的
 * 单点更新和前缀和查询。通过利用 lowbit（i & -i）实现 O(log n) 操作。
 *
 * ## 时间复杂度
 * - 单点更新: O(log n)
 * - 前缀和查询: O(log n)
 * - 区间和查询: O(log n)
 *
 * ## 应用场景
 * - 动态数组的前缀和/区间和维护
 * - 逆序对计数
 * - 二维树状数组（图像处理）
 * - 差分约束
 *
 * @tparam T 元素类型
 */

template <typename T>
class FenwickTree {
public:
    explicit FenwickTree(std::size_t n)
        : m_n(n), m_tree(n + 1, T{})
    {
    }

    FenwickTree(std::span<const T> arr)
        : m_n(arr.size()), m_tree(arr.size() + 1, T{})
    {
        for (std::size_t i = 0; i < arr.size(); ++i) {
            add(i, arr[i]);
        }
    }

    FenwickTree(std::initializer_list<T> ilist)
        : FenwickTree(std::span<const T>(ilist))
    {
    }

    /// 单点更新：在下标 pos 处增加 delta（0-based）
    void add(std::size_t pos, const T& delta)
    {
        for (std::size_t i = pos + 1; i <= m_n; i += lowbit(i)) {
            m_tree[i] += delta;
        }
    }

    /// 前缀和查询 [0, pos]（含 pos，0-based）
    [[nodiscard]] T prefix_sum(std::size_t pos) const
    {
        T result{};
        for (std::size_t i = pos + 1; i > 0; i -= lowbit(i)) {
            result += m_tree[i];
        }
        return result;
    }

    /// 区间和查询 [l, r]（含两端，0-based）
    [[nodiscard]] T range_sum(std::size_t l, std::size_t r) const
    {
        if (l == 0) {
            return prefix_sum(r);
        }
        return prefix_sum(r) - prefix_sum(l - 1);
    }

    /// 将 pos 处的值设为 val
    void set(std::size_t pos, const T& val)
    {
        T current = range_sum(pos, pos);
        add(pos, val - current);
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_n;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_n == 0;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "FenwickTree with " << m_n << " elements.\n";
        os << "Prefix sums: ";
        for (std::size_t i = 0; i < m_n; ++i) {
            os << prefix_sum(i) << " ";
        }
        os << '\n';
    }

private:
    std::size_t  m_n;
    std::vector<T> m_tree;

    static std::size_t lowbit(std::size_t x) noexcept
    {
        return x & (~x + 1);
    }
};

#endif // DATA_STRUCTURES_FENWICK_TREE_H
