#ifndef DATA_STRUCTURES_STACK_LIST_H
#define DATA_STRUCTURES_STACK_LIST_H

#include <iostream>
#include <optional>

/**
 * @file stack_list.h
 * @brief 链式栈（Linked Stack）—— 栈的链式存储实现
 *
 * @details
 * 采用带头结点的单链表实现，入栈和出栈在头结点后操作（即栈顶为链表第一个有效节点）。
 * 链式栈的优点是不存在容量限制，元素动态分配。
 *
 * ## 时间复杂度
 * - 入栈: O(1)
 * - 出栈: O(1)
 * - 取栈顶: O(1)
 *
 * ## 应用场景
 * - 数据量无法预知且需要栈结构
 * - 避免顺序栈的扩容开销
 *
 * @tparam T 元素类型
 */

template <typename T>
struct StackNode {
    T           data;
    StackNode*  next;

    explicit StackNode(const T& value) : data(value), next(nullptr) {}
    explicit StackNode(T&& value)      : data(std::move(value)), next(nullptr) {}
};

template <typename T>
class LinkedStack {
public:
    using node_type = StackNode<T>;

    LinkedStack() noexcept
        : m_head(new node_type(T{}))
    {
    }

    LinkedStack(std::initializer_list<T> ilist) : LinkedStack()
    {
        for (const auto& v : ilist) {
            push(v);
        }
    }

    LinkedStack(const LinkedStack& other) : LinkedStack()
    {
        // 正序复制（保持栈顺序）
        node_type* cur = other.m_head->next;
        LinkedStack tmp;
        while (cur) {
            tmp.push(cur->data);
            cur = cur->next;
        }
        while (!tmp.empty()) {
            push(tmp.top().value());
            tmp.pop();
        }
    }

    LinkedStack(LinkedStack&& other) noexcept
        : m_head(other.m_head)
    {
        other.m_head = new node_type(T{});
    }

    LinkedStack& operator=(const LinkedStack& other)
    {
        if (this != &other) {
            LinkedStack tmp(other);
            swap(tmp);
        }
        return *this;
    }

    LinkedStack& operator=(LinkedStack&& other) noexcept
    {
        if (this != &other) {
            destroy();
            m_head = other.m_head;
            other.m_head = new node_type(T{});
        }
        return *this;
    }

    ~LinkedStack() noexcept
    {
        destroy();
    }

    void swap(LinkedStack& other) noexcept
    {
        std::swap(m_head, other.m_head);
    }

    /// 入栈（头插）
    void push(const T& value)
    {
        auto* node = new node_type(value);
        node->next = m_head->next;
        m_head->next = node;
    }

    void push(T&& value)
    {
        auto* node = new node_type(std::move(value));
        node->next = m_head->next;
        m_head->next = node;
    }

    /// 出栈
    void pop()
    {
        if (empty()) {
            return;
        }
        node_type* del = m_head->next;
        m_head->next = del->next;
        delete del;
    }

    /// 出栈并返回
    std::optional<T> try_pop() noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        node_type* del = m_head->next;
        T value = std::move(del->data);
        m_head->next = del->next;
        delete del;
        return value;
    }

    /// 获取栈顶元素
    [[nodiscard]] std::optional<T> top() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_head->next->data;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_head->next == nullptr;
    }

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

    void clear() noexcept
    {
        destroy();
        m_head->next = nullptr;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "Stack[top]: ";
        node_type* cur = m_head->next;
        while (cur) {
            os << cur->data << " ";
            cur = cur->next;
        }
        os << "[bottom]\n";
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
};

#endif // DATA_STRUCTURES_STACK_LIST_H
