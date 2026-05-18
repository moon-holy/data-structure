#ifndef DATA_STRUCTURES_BST_H
#define DATA_STRUCTURES_BST_H

#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <vector>

/**
 * @file bst.h
 * @brief 二叉搜索树（Binary Search Tree, BST）
 *
 * @details
 * 二叉搜索树是满足以下性质的二叉树：
 * 1. 左子树上所有节点的值均小于根节点
 * 2. 右子树上所有节点的值均大于根节点
 * 3. 左右子树也分别是二叉搜索树
 *
 * ## 时间复杂度（平均 / 最坏）
 * - 查找: O(log n) / O(n)
 * - 插入: O(log n) / O(n)
 * - 删除: O(log n) / O(n)
 *
 * ## 应用场景
 * - 动态数据的有序维护
 * - 查找表（Symbol Table）
 * - 作为 AVL、红黑树等平衡树的基础
 *
 * @tparam T 元素类型
 */

template <typename T>
struct BSTNode {
    T           data;
    BSTNode*    left;
    BSTNode*    right;

    explicit BSTNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    explicit BSTNode(T&& value)      : data(std::move(value)), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
public:
    using node_type = BSTNode<T>;

    BST() noexcept = default;

    BST(std::initializer_list<T> ilist)
    {
        for (const auto& v : ilist) {
            insert(v);
        }
    }

    template <typename InputIt>
    BST(InputIt first, InputIt last)
    {
        while (first != last) {
            insert(*first++);
        }
    }

    BST(const BST& other)
    {
        copy_from(other.m_root);
    }

    BST(BST&& other) noexcept
        : m_root(other.m_root)
    {
        other.m_root = nullptr;
    }

    BST& operator=(const BST& other)
    {
        if (this != &other) {
            destroy(m_root);
            m_root = nullptr;
            copy_from(other.m_root);
        }
        return *this;
    }

    BST& operator=(BST&& other) noexcept
    {
        if (this != &other) {
            destroy(m_root);
            m_root = other.m_root;
            other.m_root = nullptr;
        }
        return *this;
    }

    ~BST() noexcept
    {
        destroy(m_root);
    }

    // ============================================================
    // 容量
    // ============================================================

    [[nodiscard]] bool empty() const noexcept
    {
        return m_root == nullptr;
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        std::size_t count = 0;
        inorder_traversal([&count](const T&) { ++count; });
        return count;
    }

    // ============================================================
    // 查找
    // ============================================================

    /// 查找元素，返回指向节点的指针
    [[nodiscard]] node_type* find(const T& value) noexcept
    {
        return find_node(m_root, value);
    }

    [[nodiscard]] const node_type* find(const T& value) const noexcept
    {
        return const_cast<BST*>(this)->find(value);
    }

    /// 是否包含某个值
    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        return find(value) != nullptr;
    }

    // ============================================================
    // 修改操作
    // ============================================================

    /// 插入元素
    void insert(const T& value)
    {
        m_root = insert_node(m_root, value);
    }

    void insert(T&& value)
    {
        m_root = insert_node(m_root, std::move(value));
    }

    /// 删除元素
    bool erase(const T& value)
    {
        if (!contains(value)) {
            return false;
        }
        m_root = erase_node(m_root, value);
        return true;
    }

    void clear() noexcept
    {
        destroy(m_root);
        m_root = nullptr;
    }

    // ============================================================
    // 遍历
    // ============================================================

    /// 前序遍历
    void preorder(std::function<void(const T&)> visit) const
    {
        preorder_recursive(m_root, visit);
    }

    /// 中序遍历（BST 的中序遍历结果为有序序列）
    void inorder(std::function<void(const T&)> visit) const
    {
        inorder_recursive(m_root, visit);
    }

    /// 后序遍历
    void postorder(std::function<void(const T&)> visit) const
    {
        postorder_recursive(m_root, visit);
    }

    /// 层序遍历
    void level_order(std::function<void(const T&)> visit) const
    {
        if (!m_root) {
            return;
        }
        std::queue<node_type*> q;
        q.push(m_root);
        while (!q.empty()) {
            auto* node = q.front();
            q.pop();
            visit(node->data);
            if (node->left)  { q.push(node->left); }
            if (node->right) { q.push(node->right); }
        }
    }

    // ============================================================
    // 属性
    // ============================================================

    /// 树的高度
    [[nodiscard]] int height() const noexcept
    {
        return height_recursive(m_root);
    }

    /// 最小值
    [[nodiscard]] std::optional<T> min() const noexcept
    {
        if (!m_root) {
            return std::nullopt;
        }
        node_type* cur = m_root;
        while (cur->left) {
            cur = cur->left;
        }
        return cur->data;
    }

    /// 最大值
    [[nodiscard]] std::optional<T> max() const noexcept
    {
        if (!m_root) {
            return std::nullopt;
        }
        node_type* cur = m_root;
        while (cur->right) {
            cur = cur->right;
        }
        return cur->data;
    }

    // ============================================================
    // 打印（括号表示法）
    // ============================================================

    void print(std::ostream& os = std::cout) const
    {
        print_node(m_root, os);
        os << '\n';
    }

private:
    node_type* m_root{nullptr};

    void inorder_traversal(std::function<void(const T&)> visit) const
    {
        inorder(visit);
    }

    static node_type* find_node(node_type* root, const T& value) noexcept
    {
        node_type* cur = root;
        while (cur) {
            if (value == cur->data) {
                return cur;
            }
            if (value < cur->data) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return nullptr;
    }

    static node_type* insert_node(node_type* root, const T& value)
    {
        if (!root) {
            return new node_type(value);
        }
        if (value < root->data) {
            root->left = insert_node(root->left, value);
        } else if (value > root->data) {
            root->right = insert_node(root->right, value);
        }
        return root;
    }

    static node_type* insert_node(node_type* root, T&& value)
    {
        if (!root) {
            return new node_type(std::move(value));
        }
        if (value < root->data) {
            root->left = insert_node(root->left, std::move(value));
        } else if (value > root->data) {
            root->right = insert_node(root->right, std::move(value));
        }
        return root;
    }

    static node_type* erase_node(node_type* root, const T& value)
    {
        if (!root) {
            return nullptr;
        }
        if (value < root->data) {
            root->left = erase_node(root->left, value);
        } else if (value > root->data) {
            root->right = erase_node(root->right, value);
        } else {
            // 找到要删除的节点
            if (!root->left) {
                node_type* right = root->right;
                delete root;
                return right;
            }
            if (!root->right) {
                node_type* left = root->left;
                delete root;
                return left;
            }
            // 有两个子节点：找右子树的最小节点（后继）
            node_type* successor = min_node(root->right);
            root->data = successor->data;
            root->right = erase_node(root->right, successor->data);
        }
        return root;
    }

    static node_type* min_node(node_type* root) noexcept
    {
        while (root && root->left) {
            root = root->left;
        }
        return root;
    }

    static void destroy(node_type* root) noexcept
    {
        if (!root) {
            return;
        }
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

    void copy_from(node_type* other_root)
    {
        if (!other_root) {
            return;
        }
        std::queue<node_type*> q;
        q.push(other_root);
        while (!q.empty()) {
            auto* node = q.front();
            q.pop();
            insert(node->data);
            if (node->left)  { q.push(node->left); }
            if (node->right) { q.push(node->right); }
        }
    }

    static void preorder_recursive(node_type* root, std::function<void(const T&)>& visit)
    {
        if (!root) {
            return;
        }
        visit(root->data);
        preorder_recursive(root->left, visit);
        preorder_recursive(root->right, visit);
    }

    static void inorder_recursive(node_type* root, std::function<void(const T&)>& visit)
    {
        if (!root) {
            return;
        }
        inorder_recursive(root->left, visit);
        visit(root->data);
        inorder_recursive(root->right, visit);
    }

    static void postorder_recursive(node_type* root, std::function<void(const T&)>& visit)
    {
        if (!root) {
            return;
        }
        postorder_recursive(root->left, visit);
        postorder_recursive(root->right, visit);
        visit(root->data);
    }

    static int height_recursive(node_type* root) noexcept
    {
        if (!root) {
            return 0;
        }
        return 1 + std::max(height_recursive(root->left),
                            height_recursive(root->right));
    }

    static void print_node(node_type* root, std::ostream& os)
    {
        if (!root) {
            return;
        }
        os << root->data;
        if (root->left || root->right) {
            os << "(";
            print_node(root->left, os);
            if (root->right) {
                os << ",";
            }
            print_node(root->right, os);
            os << ")";
        }
    }
};

#endif // DATA_STRUCTURES_BST_H
