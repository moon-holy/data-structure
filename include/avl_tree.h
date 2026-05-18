#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>

/**
 * @file avl_tree.h
 * @brief AVL 平衡树（Adelson-Velsky and Landis Tree）
 *
 * @details
 * AVL 树是最早被发明的自平衡二叉搜索树，保证任意节点的左右子树高度差不超过 1。
 * 通过在插入和删除时进行旋转（左旋、右旋、左右旋、右左旋）来维持平衡。
 *
 * ## 时间复杂度
 * - 查找: O(log n)
 * - 插入: O(log n)
 * - 删除: O(log n)
 *
 * ## 应用场景
 * - 需要严格平衡的场景（比红黑树更严格的平衡条件）
 * - 查找频繁而插入删除较少的场景
 * - 需要快速获取树高的场景
 *
 * @tparam T 元素类型
 */

template <typename T>
struct AVLNode {
    T           data;
    AVLNode*    left;
    AVLNode*    right;
    int         height;  // 以该节点为根的子树高度

    explicit AVLNode(const T& value)
        : data(value), left(nullptr), right(nullptr), height(1)
    {
    }
};

template <typename T>
class AVLTree {
public:
    using node_type = AVLNode<T>;

    AVLTree() noexcept = default;

    AVLTree(std::initializer_list<T> ilist)
    {
        for (const auto& v : ilist) {
            insert(v);
        }
    }

    AVLTree(const AVLTree& other)
    {
        copy_from(other.m_root);
    }

    AVLTree(AVLTree&& other) noexcept
        : m_root(other.m_root)
    {
        other.m_root = nullptr;
    }

    AVLTree& operator=(const AVLTree& other)
    {
        if (this != &other) {
            destroy(m_root);
            m_root = nullptr;
            copy_from(other.m_root);
        }
        return *this;
    }

    AVLTree& operator=(AVLTree&& other) noexcept
    {
        if (this != &other) {
            destroy(m_root);
            m_root = other.m_root;
            other.m_root = nullptr;
        }
        return *this;
    }

    ~AVLTree() noexcept
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

    [[nodiscard]] int height() const noexcept
    {
        return height_of(m_root);
    }

    // ============================================================
    // 查找
    // ============================================================

    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        node_type* cur = m_root;
        while (cur) {
            if (value == cur->data) { return true; }
            if (value < cur->data)  { cur = cur->left; }
            else                    { cur = cur->right; }
        }
        return false;
    }

    [[nodiscard]] std::optional<T> min() const noexcept
    {
        if (!m_root) { return std::nullopt; }
        node_type* cur = m_root;
        while (cur->left) { cur = cur->left; }
        return cur->data;
    }

    [[nodiscard]] std::optional<T> max() const noexcept
    {
        if (!m_root) { return std::nullopt; }
        node_type* cur = m_root;
        while (cur->right) { cur = cur->right; }
        return cur->data;
    }

    // ============================================================
    // 修改操作
    // ============================================================

    void insert(const T& value)
    {
        m_root = insert_node(m_root, value);
    }

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

    void inorder(std::function<void(const T&)> visit) const
    {
        inorder_recursive(m_root, visit);
    }

    void preorder(std::function<void(const T&)> visit) const
    {
        preorder_recursive(m_root, visit);
    }

    void postorder(std::function<void(const T&)> visit) const
    {
        postorder_recursive(m_root, visit);
    }

    void level_order(std::function<void(const T&)> visit) const
    {
        if (!m_root) { return; }
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

    /// 括号表示法打印
    void print(std::ostream& os = std::cout) const
    {
        print_node(m_root, os);
        os << '\n';
    }

private:
    node_type* m_root{nullptr};

    // ---- 辅助 ----
    static int height_of(node_type* node) noexcept
    {
        return node ? node->height : 0;
    }

    static int balance_factor(node_type* node) noexcept
    {
        return node ? height_of(node->left) - height_of(node->right) : 0;
    }

    static void update_height(node_type* node) noexcept
    {
        node->height = 1 + std::max(height_of(node->left), height_of(node->right));
    }

    // ---- 旋转 ----
    static node_type* rotate_right(node_type* y) noexcept
    {
        node_type* x  = y->left;
        node_type* T2 = x->right;

        x->right = y;
        y->left  = T2;

        update_height(y);
        update_height(x);
        return x;
    }

    static node_type* rotate_left(node_type* x) noexcept
    {
        node_type* y  = x->right;
        node_type* T2 = y->left;

        y->left  = x;
        x->right = T2;

        update_height(x);
        update_height(y);
        return y;
    }

    // ---- 插入 ----
    static node_type* insert_node(node_type* node, const T& value)
    {
        if (!node) {
            return new node_type(value);
        }
        if (value < node->data) {
            node->left = insert_node(node->left, value);
        } else if (value > node->data) {
            node->right = insert_node(node->right, value);
        } else {
            return node;  // 重复值不插入
        }

        update_height(node);
        return balance(node);
    }

    // ---- 删除 ----
    static node_type* min_node(node_type* node) noexcept
    {
        while (node->left) { node = node->left; }
        return node;
    }

    static node_type* erase_node(node_type* node, const T& value)
    {
        if (!node) { return nullptr; }

        if (value < node->data) {
            node->left = erase_node(node->left, value);
        } else if (value > node->data) {
            node->right = erase_node(node->right, value);
        } else {
            if (!node->left || !node->right) {
                node_type* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            node_type* successor = min_node(node->right);
            node->data = successor->data;
            node->right = erase_node(node->right, successor->data);
        }

        update_height(node);
        return balance(node);
    }

    // ---- 平衡 ----
    static node_type* balance(node_type* node) noexcept
    {
        int bf = balance_factor(node);

        // 左左情况
        if (bf > 1 && balance_factor(node->left) >= 0) {
            return rotate_right(node);
        }
        // 左右情况
        if (bf > 1 && balance_factor(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        // 右右情况
        if (bf < -1 && balance_factor(node->right) <= 0) {
            return rotate_left(node);
        }
        // 右左情况
        if (bf < -1 && balance_factor(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }

    // ---- 遍历辅助 ----
    static void inorder_recursive(node_type* node, std::function<void(const T&)>& visit)
    {
        if (!node) { return; }
        inorder_recursive(node->left, visit);
        visit(node->data);
        inorder_recursive(node->right, visit);
    }

    static void preorder_recursive(node_type* node, std::function<void(const T&)>& visit)
    {
        if (!node) { return; }
        visit(node->data);
        preorder_recursive(node->left, visit);
        preorder_recursive(node->right, visit);
    }

    static void postorder_recursive(node_type* node, std::function<void(const T&)>& visit)
    {
        if (!node) { return; }
        postorder_recursive(node->left, visit);
        postorder_recursive(node->right, visit);
        visit(node->data);
    }

    static void print_node(node_type* node, std::ostream& os)
    {
        if (!node) { return; }
        os << node->data;
        if (node->left || node->right) {
            os << "(";
            print_node(node->left, os);
            if (node->right) {
                os << ",";
            }
            print_node(node->right, os);
            os << ")";
        }
    }

    static void destroy(node_type* node) noexcept
    {
        if (!node) { return; }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void copy_from(node_type* other)
    {
        if (!other) { return; }
        std::queue<node_type*> q;
        q.push(other);
        while (!q.empty()) {
            auto* node = q.front();
            q.pop();
            insert(node->data);
            if (node->left)  { q.push(node->left); }
            if (node->right) { q.push(node->right); }
        }
    }
};

#endif // DATA_STRUCTURES_AVL_TREE_H
