#ifndef DATA_STRUCTURES_TRIE_H
#define DATA_STRUCTURES_TRIE_H

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

/**
 * @file trie.h
 * @brief 字典树 / 前缀树（Trie / Prefix Tree）
 *
 * @details
 * 字典树是一种用于快速检索字符串数据集中的键的多叉树结构。
 * 每个节点代表一个公共前缀，通过共享前缀节省空间。
 *
 * ## 时间复杂度
 * - 插入: O(m)，m 为键长
 * - 查找: O(m)
 * - 前缀查询: O(m)
 *
 * ## 应用场景
 * - 自动补全 / 输入预测
 * - 拼写检查
 * - IP 路由（最长前缀匹配）
 * - 词频统计
 */

class Trie {
public:
    struct Node {
        std::unique_ptr<Node> children[26]; // 仅小写字母 a-z
        bool is_end{false};
        int  count{0};                       // 经过该节点的单词数
    };

    Trie() = default;

    /// 插入一个单词
    void insert(std::string_view word)
    {
        Node* cur = &m_root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                cur->children[idx] = std::make_unique<Node>();
            }
            cur = cur->children[idx].get();
            cur->count++;
        }
        cur->is_end = true;
    }

    /// 查找完整单词是否存在
    [[nodiscard]] bool search(std::string_view word) const
    {
        const Node* cur = &m_root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return false;
            }
            cur = cur->children[idx].get();
        }
        return cur->is_end;
    }

    /// 判断是否有以 prefix 为前缀的单词
    [[nodiscard]] bool starts_with(std::string_view prefix) const
    {
        const Node* cur = &m_root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return false;
            }
            cur = cur->children[idx].get();
        }
        return true;
    }

    /// 删除一个单词，返回是否删除成功
    bool erase(std::string_view word)
    {
        if (!search(word)) {
            return false;
        }
        Node* cur = &m_root;
        for (char ch : word) {
            int idx = ch - 'a';
            cur->children[idx]->count--;
            cur = cur->children[idx].get();
        }
        cur->is_end = false;
        return true;
    }

    /// 获取以 prefix 为前缀的单词数
    [[nodiscard]] int count_prefix(std::string_view prefix) const
    {
        const Node* cur = &m_root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return 0;
            }
            cur = cur->children[idx].get();
        }
        return cur->count;
    }

    /// 获取所有插入的单词
    [[nodiscard]] std::vector<std::string> all_words() const
    {
        std::vector<std::string> result;
        std::string current;
        dfs_collect(&m_root, current, result);
        return result;
    }

    /// 根据前缀自动补全
    [[nodiscard]] std::vector<std::string> autocomplete(std::string_view prefix) const
    {
        std::vector<std::string> result;
        const Node* cur = &m_root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return result;
            }
            cur = cur->children[idx].get();
        }
        std::string current(prefix);
        dfs_collect(cur, current, result);
        return result;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_root.count == 0;
    }

    void print(std::ostream& os = std::cout) const
    {
        auto words = all_words();
        os << "Trie contains " << words.size() << " words:\n";
        for (const auto& w : words) {
            os << "  " << w << '\n';
        }
    }

private:
    Node m_root;

    static void dfs_collect(const Node* node, std::string& current, std::vector<std::string>& result)
    {
        if (node->is_end) {
            result.push_back(current);
        }
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                current.push_back(static_cast<char>('a' + i));
                dfs_collect(node->children[i].get(), current, result);
                current.pop_back();
            }
        }
    }
};

#endif // DATA_STRUCTURES_TRIE_H
