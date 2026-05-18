#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#include <functional>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

/**
 * @file hash_table.h
 * @brief 哈希表（Hash Table / HashMap）—— 链地址法
 *
 * @details
 * 哈希表通过哈希函数将键映射到数组索引，实现平均 O(1) 的查找、插入和删除。
 * 采用链地址法处理哈希冲突（每个桶使用链表存储多个元素）。
 * 当负载因子超过阈值时自动扩容（rehash）。
 *
 * ## 时间复杂度
 * - 查找: O(1) 平均 / O(n) 最坏
 * - 插入: O(1) 平均（均摊）
 * - 删除: O(1) 平均
 *
 * ## 应用场景
 * - 需要 O(1) 查找的关联容器
 * - 缓存系统（Cache）
 * - 去重与计数
 *
 * @tparam K 键类型
 * @tparam V 值类型
 * @tparam Hash 哈希函数对象
 */

template <typename K, typename V, typename Hash = std::hash<K>>
class HashMap {
public:
    using value_type = std::pair<K, V>;

    explicit HashMap(std::size_t initial_capacity = 16, double load_factor = 0.75)
        : m_buckets(initial_capacity)
        , m_max_load_factor(load_factor)
    {
    }

    HashMap(std::initializer_list<value_type> ilist)
        : HashMap(ilist.size() * 2)
    {
        for (const auto& [k, v] : ilist) {
            insert(k, v);
        }
    }

    HashMap(const HashMap& other)
        : m_buckets(other.m_buckets.size())
        , m_size(other.m_size)
        , m_max_load_factor(other.m_max_load_factor)
    {
        for (std::size_t i = 0; i < other.m_buckets.size(); ++i) {
            m_buckets[i] = other.m_buckets[i];
        }
    }

    HashMap(HashMap&& other) noexcept = default;
    HashMap& operator=(const HashMap& other)
    {
        if (this != &other) {
            HashMap tmp(other);
            swap(tmp);
        }
        return *this;
    }
    HashMap& operator=(HashMap&& other) noexcept = default;

    ~HashMap() noexcept = default;

    void swap(HashMap& other) noexcept
    {
        using std::swap;
        swap(m_buckets, other.m_buckets);
        swap(m_size, other.m_size);
        swap(m_max_load_factor, other.m_max_load_factor);
    }

    // ============================================================
    // 容量
    // ============================================================

    [[nodiscard]] std::size_t size() const noexcept { return m_size; }
    [[nodiscard]] bool empty() const noexcept { return m_size == 0; }

    // ============================================================
    // 元素访问
    // ============================================================

    /// 查找键对应的值
    [[nodiscard]] std::optional<V> get(const K& key) const
    {
        std::size_t idx = m_hash(key) % m_buckets.size();
        for (const auto& [k, v] : m_buckets[idx]) {
            if (k == key) {
                return v;
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] V operator[](const K& key) const
    {
        return get(key).value_or(V{});
    }

    [[nodiscard]] bool contains(const K& key) const
    {
        std::size_t idx = m_hash(key) % m_buckets.size();
        for (const auto& [k, v] : m_buckets[idx]) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    // ============================================================
    // 修改操作
    // ============================================================

    /// 插入键值对
    void insert(const K& key, const V& value)
    {
        if (static_cast<double>(m_size + 1) / m_buckets.size() > m_max_load_factor) {
            rehash(m_buckets.size() * 2);
        }
        std::size_t idx = m_hash(key) % m_buckets.size();
        for (auto& [k, v] : m_buckets[idx]) {
            if (k == key) {
                v = value;
                return;
            }
        }
        m_buckets[idx].emplace_back(key, value);
        ++m_size;
    }

    /// 删除键，返回是否成功
    bool erase(const K& key)
    {
        std::size_t idx = m_hash(key) % m_buckets.size();
        auto& bucket = m_buckets[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --m_size;
                return true;
            }
        }
        return false;
    }

    void clear() noexcept
    {
        for (auto& bucket : m_buckets) {
            bucket.clear();
        }
        m_size = 0;
    }

    // ============================================================
    // 迭代遍历
    // ============================================================

    void for_each(std::function<void(const K&, const V&)> func) const
    {
        for (const auto& bucket : m_buckets) {
            for (const auto& [k, v] : bucket) {
                func(k, v);
            }
        }
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "HashMap size=" << m_size << " buckets=" << m_buckets.size() << '\n';
        for_each([&os](const K& k, const V& v) {
            os << "  " << k << " -> " << v << '\n';
        });
    }

private:
    std::vector<std::vector<value_type>> m_buckets;
    std::size_t m_size{0};
    double      m_max_load_factor{0.75};
    Hash        m_hash{};

    void rehash(std::size_t new_capacity)
    {
        std::vector<std::vector<value_type>> new_buckets(new_capacity);
        for (const auto& bucket : m_buckets) {
            for (auto& [k, v] : bucket) {
                std::size_t idx = m_hash(k) % new_capacity;
                new_buckets[idx].emplace_back(std::move(k), std::move(v));
            }
        }
        m_buckets = std::move(new_buckets);
    }
};

#endif // DATA_STRUCTURES_HASH_TABLE_H
