#ifndef DATA_STRUCTURES_SEGMENT_TREE_H
#define DATA_STRUCTURES_SEGMENT_TREE_H

#include <functional>
#include <iostream>
#include <span>
#include <vector>

/**
 * @file segment_tree.h
 * @brief 线段树（Segment Tree）—— 区间查询与区间更新
 *
 * @details
 * 线段树是一种基于分治思想的二叉树结构，用于高效处理数组上的区间查询和区间更新。
 * 支持任意结合律操作（如求和、最大值、最小值、GCD 等）。
 * 实现带惰性传播（Lazy Propagation）的区间更新。
 *
 * ## 时间复杂度
 * - 建树: O(n)
 * - 区间查询: O(log n)
 * - 单点更新: O(log n)
 * - 区间更新: O(log n)
 *
 * ## 应用场景
 * - 区间求和 / 最值 / GCD
 * - 区间加减赋值（带 lazy 标记）
 * - 扫描线算法（矩形面积并）
 * - 动态规划优化
 *
 * @tparam T 元素类型
 * @tparam Combine 结合律操作
 */

template <typename T, typename Combine = std::plus<T>>
class SegmentTree {
public:
    /// 从数组构造（0-based）
    SegmentTree(std::span<const T> arr, Combine combine = Combine{}, T identity = T{})
        : m_n(arr.size())
        , m_tree(4 * m_n)
        , m_lazy(4 * m_n, 0)
        , m_combine(std::move(combine))
        , m_identity(identity)
    {
        build(arr, 1, 0, m_n - 1);
    }

    /// 区间查询 [ql, qr]（含两端）
    T query(std::size_t ql, std::size_t qr)
    {
        return query(1, 0, m_n - 1, ql, qr);
    }

    /// 单点更新：将 pos 位置的值更新为 val
    void update_point(std::size_t pos, const T& val)
    {
        update_point(1, 0, m_n - 1, pos, val);
    }

    /// 区间更新：将 [ql, qr] 中每个元素增加 delta
    void update_range(std::size_t ql, std::size_t qr, const T& delta)
    {
        update_range(1, 0, m_n - 1, ql, qr, delta);
    }

    [[nodiscard]] std::size_t size() const noexcept { return m_n; }

    void print(std::ostream& os = std::cout) const
    {
        os << "SegmentTree with " << m_n << " elements.\n";
    }

private:
    std::size_t          m_n;
    std::vector<T>       m_tree;
    std::vector<T>       m_lazy;
    Combine              m_combine;
    T                    m_identity;

    void build(std::span<const T> arr, std::size_t node, std::size_t l, std::size_t r)
    {
        if (l == r) {
            m_tree[node] = arr[l];
            return;
        }
        std::size_t mid = l + (r - l) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        m_tree[node] = m_combine(m_tree[node * 2], m_tree[node * 2 + 1]);
    }

    void push(std::size_t node, std::size_t l, std::size_t r)
    {
        if (m_lazy[node] != 0) {
            m_tree[node] += m_lazy[node] * (static_cast<T>(r - l + 1));
            if (l != r) {
                m_lazy[node * 2]     += m_lazy[node];
                m_lazy[node * 2 + 1] += m_lazy[node];
            }
            m_lazy[node] = 0;
        }
    }

    T query(std::size_t node, std::size_t l, std::size_t r, std::size_t ql, std::size_t qr)
    {
        push(node, l, r);
        if (ql > r || qr < l) { return m_identity; }
        if (ql <= l && r <= qr) { return m_tree[node]; }
        std::size_t mid = l + (r - l) / 2;
        return m_combine(query(node * 2, l, mid, ql, qr),
                         query(node * 2 + 1, mid + 1, r, ql, qr));
    }

    void update_point(std::size_t node, std::size_t l, std::size_t r,
                      std::size_t pos, const T& val)
    {
        if (l == r) {
            m_tree[node] = val;
            return;
        }
        std::size_t mid = l + (r - l) / 2;
        if (pos <= mid) {
            update_point(node * 2, l, mid, pos, val);
        } else {
            update_point(node * 2 + 1, mid + 1, r, pos, val);
        }
        m_tree[node] = m_combine(m_tree[node * 2], m_tree[node * 2 + 1]);
    }

    void update_range(std::size_t node, std::size_t l, std::size_t r,
                      std::size_t ql, std::size_t qr, const T& delta)
    {
        push(node, l, r);
        if (ql > r || qr < l) { return; }
        if (ql <= l && r <= qr) {
            m_lazy[node] += delta;
            push(node, l, r);
            return;
        }
        std::size_t mid = l + (r - l) / 2;
        update_range(node * 2, l, mid, ql, qr, delta);
        update_range(node * 2 + 1, mid + 1, r, ql, qr, delta);
        m_tree[node] = m_combine(m_tree[node * 2], m_tree[node * 2 + 1]);
    }
};

#endif // DATA_STRUCTURES_SEGMENT_TREE_H
