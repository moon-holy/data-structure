#ifndef DATA_STRUCTURES_UNION_FIND_H
#define DATA_STRUCTURES_UNION_FIND_H

#include <iostream>
#include <vector>

/**
 * @file union_find.h
 * @brief 并查集（Union-Find / Disjoint Set Union, DSU）
 *
 * @details
 * 并查集是一种用于处理不相交集合的合并与查询问题的数据结构。
 * 支持两种操作：
 * 1. Find：查询元素所属集合的代表元
 * 2. Union：合并两个元素所在的集合
 *
 * 通过路径压缩（Path Compression）和按秩合并（Union by Rank）优化，
 * 均摊时间复杂度接近 O(α(n))（反阿克曼函数，几乎为常数）。
 *
 * ## 时间复杂度
 * - Find: O(α(n)) 均摊
 * - Union: O(α(n)) 均摊
 *
 * ## 应用场景
 * - 图的连通分量检测
 * - Kruskal 最小生成树
 * - 社交网络中的好友关系
 * - 动态连通性问题
 */

class UnionFind {
public:
    /// 初始化 n 个独立元素（编号 0 ~ n-1）
    explicit UnionFind(std::size_t n)
        : m_parent(n), m_rank(n, 0), m_count(n)
    {
        for (std::size_t i = 0; i < n; ++i) {
            m_parent[i] = i;
        }
    }

    /// 查找元素 x 的集合代表元（带路径压缩）
    std::size_t find(std::size_t x) noexcept
    {
        if (m_parent[x] != x) {
            m_parent[x] = find(m_parent[x]);
        }
        return m_parent[x];
    }

    [[nodiscard]] std::size_t find(std::size_t x) const noexcept
    {
        while (m_parent[x] != x) {
            x = m_parent[x];
        }
        return x;
    }

    /// 合并 x 和 y 所在的集合
    void unite(std::size_t x, std::size_t y) noexcept
    {
        std::size_t rx = find(x);
        std::size_t ry = find(y);
        if (rx == ry) {
            return;
        }

        // 按秩合并
        if (m_rank[rx] < m_rank[ry]) {
            m_parent[rx] = ry;
        } else if (m_rank[rx] > m_rank[ry]) {
            m_parent[ry] = rx;
        } else {
            m_parent[ry] = rx;
            m_rank[rx]++;
        }
        --m_count;
    }

    /// 判断 x 和 y 是否属于同一集合
    [[nodiscard]] bool same(std::size_t x, std::size_t y) noexcept
    {
        return find(x) == find(y);
    }

    [[nodiscard]] bool same(std::size_t x, std::size_t y) const noexcept
    {
        return find(x) == find(y);
    }

    /// 当前集合（连通分量）的数量
    [[nodiscard]] std::size_t count() const noexcept
    {
        return m_count;
    }

    /// 总元素数
    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_parent.size();
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "UnionFind: " << m_parent.size() << " elements, "
           << m_count << " sets\n";
    }

private:
    mutable std::vector<std::size_t> m_parent;
    std::vector<std::size_t>         m_rank;
    std::size_t                      m_count;
};

#endif // DATA_STRUCTURES_UNION_FIND_H
