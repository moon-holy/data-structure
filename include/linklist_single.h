#ifndef DATA_STRUCTURES_LINKLIST_SINGLE_H
#define DATA_STRUCTURES_LINKLIST_SINGLE_H

#include <iostream>
#include <optional>
#include <span>

/**
 * @file linklist_single.h
 * @brief 单链表（Singly Linked List）—— 带头结点
 *
 * @details
 * 单链表是一种通过指针将各个节点串联起来的线性结构，每个节点包含数据域和指向下一个节点的指针。
 * 带头结点的实现简化了插入和删除操作的边界处理。
 *
 * ## 时间复杂度
 * - 头插:    O(1)
 * - 尾插:    O(n)
 * - 按位查找: O(n)
 * - 按值查找: O(n)
 * - 插入:     O(n)
 * - 删除:     O(n)
 *
 * ## 应用场景
 * - 需要频繁插入/删除操作
 * - 数据量动态变化较大
 * - 实现栈、队列等数据结构
 *
 * @tparam T 元素类型
 */

template <typename T>
struct SingleLinkNode {
    T                     data;
    SingleLinkNode*       next;

    explicit SingleLinkNode(const T& value) : data(value), next(nullptr) {}
    explicit SingleLinkNode(T&& value)      : data(std::move(value)), next(nullptr) {}
};

template <typename T>
class SingleLinkedList {
public:
    using node_type = SingleLinkNode<T>;

    SingleLinkedList() noexcept
        : m_head(new node_type(T{}))
    {
    }

    SingleLinkedList(std::initializer_list<T> ilist) : SingleLinkedList()
    {
        push_back(ilist);
    }

    explicit SingleLinkedList(std::span<const T> arr) : SingleLinkedList()
    {
        for (const auto& v : arr) {
            push_back(v);
        }
    }

    SingleLinkedList(const SingleLinkedList& other) : SingleLinkedList()
    {
        node_type* cur = other.m_head->next;
        node_type* tail = m_head;
        while (cur) {
            tail->next = new node_type(cur->data);
            tail = tail->next;
            cur = cur->next;
        }
    }

    SingleLinkedList(SingleLinkedList&& other) noexcept
        : m_head(other.m_head)
    {
        other.m_head = new node_type(T{});
    }

    SingleLinkedList& operator=(const SingleLinkedList& other)
    {
        if (this != &other) {
            SingleLinkedList tmp(other);
            swap(tmp);
        }
        return *this;
    }

    SingleLinkedList& operator=(SingleLinkedList&& other) noexcept
    {
        if (this != &other) {
            destroy();
            m_head = other.m_head;
            other.m_head = new node_type(T{});
        }
        return *this;
    }

    ~SingleLinkedList() noexcept
    {
        destroy();
    }

    void swap(SingleLinkedList& other) noexcept
    {
        std::swap(m_head, other.m_head);
    }

    // ============================================================
    // 容量
    // ============================================================

    [[nodiscard]] std::size_t size() const noexcept
    {
        std::size_t len = 0;
        node_type* cur = m_head->next;
        while (cur) {
            ++len;
            cur = cur->next;
        }
        return len;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_head->next == nullptr;
    }

    // ============================================================
    // 元素访问
    // ============================================================

    /// 按位查找（0-based），返回指向节点的指针；未找到返回 nullptr
    [[nodiscard]] node_type* at(std::size_t pos) noexcept
    {
        node_type* cur = m_head->next;
        std::size_t i = 0;
        while (cur && i < pos) {
            cur = cur->next;
            ++i;
        }
        return cur;
    }

    [[nodiscard]] const node_type* at(std::size_t pos) const noexcept
    {
        return const_cast<SingleLinkedList*>(this)->at(pos);
    }

    /// 按位查找，返回值的 optional
    [[nodiscard]] std::optional<T> get(std::size_t pos) const noexcept
    {
        const node_type* node = at(pos);
        if (node) {
            return node->data;
        }
        return std::nullopt;
    }

    /// 按值查找，返回第一个匹配的位置
    [[nodiscard]] std::optional<std::size_t> locate(const T& value) const noexcept
    {
        node_type* cur = m_head->next;
        std::size_t i = 0;
        while (cur) {
            if (cur->data == value) {
                return i;
            }
            cur = cur->next;
            ++i;
        }
        return std::nullopt;
    }

    /// 返回第一个元素
    [[nodiscard]] std::optional<T> front() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_head->next->data;
    }

    // ============================================================
    // 修改操作
    // ============================================================

    /// 头插
    void push_front(const T& value)
    {
        auto* node = new node_type(value);
        node->next = m_head->next;
        m_head->next = node;
    }

    void push_front(T&& value)
    {
        auto* node = new node_type(std::move(value));
        node->next = m_head->next;
        m_head->next = node;
    }

    /// 尾插
    void push_back(const T& value)
    {
        node_type* tail = m_head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = new node_type(value);
    }

    void push_back(T&& value)
    {
        node_type* tail = m_head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = new node_type(std::move(value));
    }

    void push_back(std::initializer_list<T> ilist)
    {
        for (const auto& v : ilist) {
            push_back(v);
        }
    }

    /// 在指定位置插入（0-based）
    /// @return 是否成功
    bool insert(std::size_t pos, const T& value)
    {
        node_type* prev = m_head;
        std::size_t i = 0;
        while (prev && i < pos) {
            prev = prev->next;
            ++i;
        }
        if (!prev) {
            return false;
        }
        auto* node = new node_type(value);
        node->next = prev->next;
        prev->next = node;
        return true;
    }

    bool insert(std::size_t pos, T&& value)
    {
        node_type* prev = m_head;
        std::size_t i = 0;
        while (prev && i < pos) {
            prev = prev->next;
            ++i;
        }
        if (!prev) {
            return false;
        }
        auto* node = new node_type(std::move(value));
        node->next = prev->next;
        prev->next = node;
        return true;
    }

    /// 删除指定位置的元素（0-based）
    bool erase(std::size_t pos)
    {
        node_type* prev = m_head;
        std::size_t i = 0;
        while (prev->next && i < pos) {
            prev = prev->next;
            ++i;
        }
        if (!prev->next) {
            return false;
        }
        node_type* del = prev->next;
        prev->next = del->next;
        delete del;
        return true;
    }

    /// 删除第一个元素
    bool pop_front() noexcept
    {
        if (empty()) {
            return false;
        }
        node_type* del = m_head->next;
        m_head->next = del->next;
        delete del;
        return true;
    }

    /// 清空链表
    void clear() noexcept
    {
        destroy();
        m_head->next = nullptr;
    }

    // ============================================================
    // 排序（归并排序）
    // ============================================================

    void sort()
    {
        m_head->next = merge_sort(m_head->next);
    }

    // ============================================================
    // 打印
    // ============================================================

    void print(std::ostream& os = std::cout, std::string_view sep = " -> ") const
    {
        node_type* cur = m_head->next;
        while (cur) {
            os << cur->data;
            cur = cur->next;
            if (cur) {
                os << sep;
            }
        }
        os << " -> nullptr\n";
    }

private:
    node_type* m_head;

    void destroy() noexcept
    {
        node_type* cur = m_head;
        while (cur) {
            node_type* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    // ---- 归并排序辅助 ----
    static node_type* get_mid(node_type* head)
    {
        if (!head) {
            return nullptr;
        }
        node_type* slow = head;
        node_type* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    static node_type* merge(node_type* left, node_type* right)
    {
        node_type dummy(T{});
        node_type* tail = &dummy;
        while (left && right) {
            if (left->data <= right->data) {
                tail->next = left;
                left = left->next;
            } else {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }
        tail->next = left ? left : right;
        return dummy.next;
    }

    static node_type* merge_sort(node_type* head)
    {
        if (!head || !head->next) {
            return head;
        }
        node_type* mid = get_mid(head);
        node_type* right_head = mid->next;
        mid->next = nullptr;
        node_type* left  = merge_sort(head);
        node_type* right = merge_sort(right_head);
        return merge(left, right);
    }
};

#endif // DATA_STRUCTURES_LINKLIST_SINGLE_H
