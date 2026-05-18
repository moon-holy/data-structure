#ifndef DATA_STRUCTURES_SKIPTABLE_H
#define DATA_STRUCTURES_SKIPTABLE_H

#include <iostream>
#include <optional>
#include <random>
#include <vector>

/**
 * @file skiptable.h
 * @brief 跳表（Skip List）
 *
 * @details
 * 跳表是一种基于有序链表、通过多级索引加速查找的概率性数据结构。
 * 期望时间复杂度 O(log n)，实现比平衡树更简单。
 *
 * ## 时间复杂度
 * - 查找: O(log n) 期望
 * - 插入: O(log n) 期望
 * - 删除: O(log n) 期望
 *
 * ## 应用场景
 * - Redis 有序集合 (ZSET)
 * - 高性能 Key-Value 存储（LevelDB, RocksDB）
 * - 需要范围查询的有序数据
 *
 * @tparam K 键类型
 * @tparam V 值类型
 */

template <typename K, typename V>
struct SkipNode {
    K                   key;
    V                   value;
    std::vector<SkipNode*> next;

    SkipNode(const K& k, const V& v, int level)
        : key(k), value(v), next(level, nullptr)
    {
    }
};

template <typename K, typename V>
class SkipList {
public:
    using Node = SkipNode<K, V>;

    explicit SkipList(int max_level = 16)
        : m_max_level(max_level)
        , m_rng(std::random_device{}())
    {
        K min_key{}, max_key{};
        if constexpr (std::is_same_v<K, int>) {
            min_key = std::numeric_limits<int>::min();
            max_key = std::numeric_limits<int>::max();
        } else if constexpr (std::is_same_v<K, long>) {
            min_key = std::numeric_limits<long>::min();
            max_key = std::numeric_limits<long>::max();
        } else if constexpr (std::is_same_v<K, short>) {
            min_key = std::numeric_limits<short>::min();
            max_key = std::numeric_limits<short>::max();
        } else {
            static_assert(std::is_same_v<K, int>, "SkipList currently requires integer key type");
        }

        m_head = new Node(min_key, V{}, max_level);
        m_tail = new Node(max_key, V{}, max_level);
        for (int i = 0; i < max_level; ++i) {
            m_head->next[i] = m_tail;
        }
    }

    ~SkipList() noexcept
    {
        Node* cur = m_head;
        while (cur && cur != m_tail) {
            Node* next = cur->next[0];
            delete cur;
            cur = next;
        }
        delete m_tail;
    }

    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;

    /// 插入键值对（key 已存在则更新）
    void insert(const K& key, const V& value)
    {
        std::vector<Node*> update(m_max_level, nullptr);
        Node* cur = m_head;

        for (int i = m_max_level - 1; i >= 0; --i) {
            while (cur->next[i] != m_tail && cur->next[i]->key < key) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        cur = cur->next[0];

        if (cur != m_tail && cur->key == key) {
            cur->value = value;
            return;
        }

        int level = random_level();
        if (level > m_current_level) {
            for (int i = m_current_level; i < level; ++i) {
                update[i] = m_head;
            }
            m_current_level = level;
        }

        auto* node = new Node(key, value, level);
        for (int i = 0; i < level; ++i) {
            node->next[i] = update[i]->next[i];
            update[i]->next[i] = node;
        }
    }

    /// 查找
    [[nodiscard]] std::optional<V> find(const K& key) const
    {
        Node* cur = m_head;
        for (int i = m_current_level - 1; i >= 0; --i) {
            while (cur->next[i] != m_tail && cur->next[i]->key < key) {
                cur = cur->next[i];
            }
        }
        cur = cur->next[0];
        if (cur != m_tail && cur->key == key) {
            return cur->value;
        }
        return std::nullopt;
    }

    [[nodiscard]] bool contains(const K& key) const
    {
        return find(key).has_value();
    }

    /// 删除
    bool erase(const K& key)
    {
        std::vector<Node*> update(m_max_level, nullptr);
        Node* cur = m_head;

        for (int i = m_current_level - 1; i >= 0; --i) {
            while (cur->next[i] != m_tail && cur->next[i]->key < key) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        cur = cur->next[0];

        if (cur == m_tail || cur->key != key) {
            return false;
        }

        for (int i = 0; i < m_current_level; ++i) {
            if (update[i]->next[i] != cur) {
                break;
            }
            update[i]->next[i] = cur->next[i];
        }
        delete cur;

        while (m_current_level > 1 && m_head->next[m_current_level - 1] == m_tail) {
            --m_current_level;
        }
        return true;
    }

    void print(std::ostream& os = std::cout) const
    {
        for (int i = m_current_level - 1; i >= 0; --i) {
            os << "Level " << i << ": ";
            Node* cur = m_head->next[i];
            while (cur != m_tail) {
                os << "(" << cur->key << ":" << cur->value << ") ";
                cur = cur->next[i];
            }
            os << '\n';
        }
    }

private:
    Node*   m_head{nullptr};
    Node*   m_tail{nullptr};
    int     m_max_level;
    int     m_current_level{1};
    std::mt19937 m_rng;

    int random_level()
    {
        int level = 1;
        while (level < m_max_level && std::bernoulli_distribution(0.5)(m_rng)) {
            ++level;
        }
        return level;
    }
};

#endif // DATA_STRUCTURES_SKIPTABLE_H
