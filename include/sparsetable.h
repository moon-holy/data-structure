#ifndef DATA_STRUCTURES_SPARSETABLE_H
#define DATA_STRUCTURES_SPARSETABLE_H

#include <algorithm>
#include <bit>
#include <cmath>
#include <functional>
#include <iostream>
#include <span>
#include <vector>

/**
 * @file sparsetable.h
 * @brief 稀疏表（Sparse Table）—— 静态数组区间查询
 *
 * @details
 * 稀疏表是一种用于静态数组上高效区间查询的数据结构。
 * 通过预处理使 O(1) 时间回答区间查询（如区间最小值、最大值、GCD 等）。
 * 支持满足幂等律的结合运算（即 x op x = x，如 min、max、gcd）。
 *
 * ## 时间复杂度
 * - 预处理: O(n log n)
 * - 区间查询: O(1)
 * - 空间: O(n log n)
 *
 * ## 应用场景
 * - RMQ（区间最值查询）
 * - 静态数组的区间查询（数据不变）
 * - LCA 问题的预处理
 *
 * @tparam T 元素类型
 * @tparam Combine 可调用的结合函数对象
 */

template <typename T, typename Combine = std::function<T(const T&, const T&)>>
class SparseTable {
public:
    /// 从数组构造
    SparseTable(std::span<const T> arr, Combine combine = [](const T& a, const T& b) { return std::min(a, b); })
        : m_combine(std::move(combine))
        , m_n(arr.size())
    {
        if (m_n == 0) {
            return;
        }
        m_log.resize(m_n + 1);
        m_log[1] = 0;
        for (std::size_t i = 2; i <= m_n; ++i) {
            m_log[i] = m_log[i / 2] + 1;
        }

        int k = m_log[m_n];
        m_st.resize(k + 1, std::vector<T>(m_n));

        for (std::size_t i = 0; i < m_n; ++i) {
            m_st[0][i] = arr[i];
        }

        for (int j = 1; j <= k; ++j) {
            std::size_t step = static_cast<std::size_t>(1) << (j - 1);
            for (std::size_t i = 0; i + (static_cast<std::size_t>(1) << j) <= m_n; ++i) {
                m_st[j][i] = m_combine(m_st[j - 1][i], m_st[j - 1][i + step]);
            }
        }
    }

    SparseTable(std::initializer_list<T> ilist, Combine combine = [](const T& a, const T& b) { return std::min(a, b); })
        : SparseTable(std::span<const T>(ilist), std::move(combine))
    {
    }

    /// 区间查询 [l, r]（含两端，0-based）
    [[nodiscard]] T query(std::size_t l, std::size_t r) const
    {
        int k = m_log[r - l + 1];
        return m_combine(m_st[k][l], m_st[k][r - (static_cast<std::size_t>(1) << k) + 1]);
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_n;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "SparseTable with " << m_n << " elements.\n";
    }

private:
    Combine                 m_combine;
    std::size_t             m_n{0};
    std::vector<int>        m_log;
    std::vector<std::vector<T>> m_st;
};

#endif // DATA_STRUCTURES_SPARSETABLE_H
