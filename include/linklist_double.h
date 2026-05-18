#ifndef DATA_STRUCTURES_LINKLIST_DOUBLE_H
#define DATA_STRUCTURES_LINKLIST_DOUBLE_H

#include <iostream>
#include <optional>
#include <span>

/**
 * @file linklist_double.h
 * @brief 双链表（Doubly Linked List）—— 带头结点
 *
 * @details
 * 双链表中每个节点包含指向前驱和后继的两个指针，支持双向遍历。
 * 相比单链表，双链表的插入和删除操作更灵活（无需查找前驱），但每个节点多一个指针的存储开销。
 *
 * ## 时间复杂度
 * - 头插:    O(1)
 * - 尾插:    O(1)（有尾指针）
 * - 按位查找: O(n)
 * - 插入:     O(1)（已知位置）
 * - 删除:     O(1)（已知位置）
 *
 * ## 应用场景
 * - 需要双向遍历的场合
 * - 实现 LRU Cache、双向队列（deque）等
 *
 * @tparam T 元素类型
 */

template <typename T>
struct DoubleLinkNode {
    T                 data;
    DoubleLinkNode*   prev;
    DoubleLinkNode*   next;

    explicit DoubleLinkNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    explicit DoubleLinkNode(T&& value)      : data(std::move(value)), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoubleLinkedList {
public:
    using node_type = DoubleLinkNode<T>;

    DoubleLinkedList() noexcept
        : m_head(new node_type(T{})), m_tail(m_head)
    {
    }

    DoubleLinkedList(std::initializer_list<T> ilist) : DoubleLinkedList()
    {
        push_back(ilist);
    }

    explicit DoubleLinkedList(std::span<const T> arr) : DoubleLinkedList()
    {
        for (const auto& v : arr) {
            push_back(v);
        }
    }

    DoubleLinkedList(const DoubleLinkedList& other) : DoubleLinkedList()
    {
        node_type* cur = other.m_head->next;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    DoubleLinkedList(DoubleLinkedList&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail)
    {
        other.m_head = new node_type(T{});
        other.m_tail = other.m_head;
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other)
    {
        if (this != &other) {
            DoubleLinkedList tmp(other);
            swap(tmp);
        }
        return *this;
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept
    {
        if (this != &other) {
            destroy();
            m_head = other.m_head;
            m_tail = other.m_tail;
            other.m_head = new node_type(T{});
            other.m_tail = other.m_head;
        }
        return *this;
    }

    ~DoubleLinkedList() noexcept
    {
        destroy();
    }

    void swap(DoubleLinkedList& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
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
        return m_head == m_tail;
    }

    // ============================================================
    // 元素访问
    // ============================================================

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
        return const_cast<DoubleLinkedList*>(this)->at(pos);
    }

    [[nodiscard]] std::optional<T> get(std::size_t pos) const noexcept
    {
        const node_type* node = at(pos);
        if (node) {
            return node->data;
        }
        return std::nullopt;
    }

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

    [[nodiscard]] std::optional<T> front() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_head->next->data;
    }

    [[nodiscard]] std::optional<T> back() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_tail->data;
    }

    // ============================================================
    // 修改操作
    // ============================================================

    /// 头插
    void push_front(const T& value)
    {
        auto* node = new node_type(value);
        node->next = m_head->next;
        node->prev = m_head;
        if (m_head->next) {
            m_head->next->prev = node;
        } else {
            m_tail = node;
        }
        m_head->next = node;
    }

    void push_front(T&& value)
    {
        auto* node = new node_type(std::move(value));
        node->next = m_head->next;
        node->prev = m_head;
        if (m_head->next) {
            m_head->next->prev = node;
        } else {
            m_tail = node;
        }
        m_head->next = node;
    }

    /// 尾插
    void push_back(const T& value)
    {
        auto* node = new node_type(value);
        node->prev = m_tail;
        m_tail->next = node;
        m_tail = node;
    }

    void push_back(T&& value)
    {
        auto* node = new node_type(std::move(value));
        node->prev = m_tail;
        m_tail->next = node;
        m_tail = node;
    }

    void push_back(std::initializer_list<T> ilist)
    {
        for (const auto& v : ilist) {
            push_back(v);
        }
    }

    /// 在指定位置插入（0-based）
    bool insert(std::size_t pos, const T& value)
    {
        if (pos == 0) {
            push_front(value);
            return true;
        }
        if (pos >= size()) {
            return false;
        }
        node_type* cur = m_head->next;
        std::size_t i = 0;
        while (cur && i < pos) {
            cur = cur->next;
            ++i;
        }
        if (!cur) {
            return false;
        }
        auto* node = new node_type(value);
        node->prev = cur->prev;
        node->next = cur;
        cur->prev->next = node;
        cur->prev = node;
        return true;
    }

    /// 删除指定位置的元素（0-based）
    bool erase(std::size_t pos)
    {
        node_type* cur = at(pos);
        if (!cur) {
            return false;
        }
        if (cur == m_tail) {
            m_tail = cur->prev;
        }
        cur->prev->next = cur->next;
        if (cur->next) {
            cur->next->prev = cur->prev;
        }
        delete cur;
        return true;
    }

    bool pop_front() noexcept
    {
        if (empty()) {
            return false;
        }
        node_type* del = m_head->next;
        m_head->next = del->next;
        if (del->next) {
            del->next->prev = m_head;
        } else {
            m_tail = m_head;
        }
        delete del;
        return true;
    }

    bool pop_back() noexcept
    {
        if (empty()) {
            return false;
        }
        node_type* del = m_tail;
        m_tail = m_tail->prev;
        m_tail->next = nullptr;
        delete del;
        return true;
    }

    void clear() noexcept
    {
        destroy();
        m_head = new node_type(T{});
        m_tail = m_head;
    }

    // ============================================================
    // 打印
    // ============================================================

    void print(std::ostream& os = std::cout, std::string_view sep = " <-> ") const
    {
        os << "nullptr";
        node_type* cur = m_head->next;
        while (cur) {
            os << sep << cur->data;
            cur = cur->next;
        }
        os << " -> nullptr\n";
    }

private:
    node_type* m_head;
    node_type* m_tail;

    void destroy() noexcept
    {
        node_type* cur = m_head;
        while (cur) {
            node_type* next = cur->next;
            delete cur;
            cur = next;
        }
    }
};

#endif // DATA_STRUCTURES_LINKLIST_DOUBLE_H
