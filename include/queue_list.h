#ifndef DATA_STRUCTURES_QUEUE_LIST_H
#define DATA_STRUCTURES_QUEUE_LIST_H

#include <iostream>
#include <optional>

/**
 * @file queue_list.h
 * @brief 链式队列（Linked Queue）—— 队列的链式存储
 *
 * @details
 * 链式队列使用带头结点的单链表实现，维护 front（队头）和 rear（队尾）两个指针。
 * 入队在队尾操作，出队在队头操作。
 *
 * ## 时间复杂度
 * - 入队: O(1)
 * - 出队: O(1)
 *
 * ## 应用场景
 * - 数据量动态变化大的队列
 * - 避免固定大小限制
 *
 * @tparam T 元素类型
 */

template <typename T>
struct QueueNode {
    T           data;
    QueueNode*  next;

    explicit QueueNode(const T& value) : data(value), next(nullptr) {}
    explicit QueueNode(T&& value)      : data(std::move(value)), next(nullptr) {}
};

template <typename T>
class LinkedQueue {
public:
    using node_type = QueueNode<T>;

    LinkedQueue() noexcept
        : m_head(new node_type(T{})), m_rear(m_head)
    {
    }

    LinkedQueue(std::initializer_list<T> ilist) : LinkedQueue()
    {
        for (const auto& v : ilist) {
            enqueue(v);
        }
    }

    LinkedQueue(const LinkedQueue& other) : LinkedQueue()
    {
        node_type* cur = other.m_head->next;
        while (cur) {
            enqueue(cur->data);
            cur = cur->next;
        }
    }

    LinkedQueue(LinkedQueue&& other) noexcept
        : m_head(other.m_head), m_rear(other.m_rear)
    {
        other.m_head = new node_type(T{});
        other.m_rear = other.m_head;
    }

    LinkedQueue& operator=(const LinkedQueue& other)
    {
        if (this != &other) {
            LinkedQueue tmp(other);
            swap(tmp);
        }
        return *this;
    }

    LinkedQueue& operator=(LinkedQueue&& other) noexcept
    {
        if (this != &other) {
            destroy();
            m_head = other.m_head;
            m_rear = other.m_rear;
            other.m_head = new node_type(T{});
            other.m_rear = other.m_head;
        }
        return *this;
    }

    ~LinkedQueue() noexcept
    {
        destroy();
    }

    void swap(LinkedQueue& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_rear, other.m_rear);
    }

    /// 入队（尾插）
    void enqueue(const T& value)
    {
        auto* node = new node_type(value);
        m_rear->next = node;
        m_rear = node;
    }

    void enqueue(T&& value)
    {
        auto* node = new node_type(std::move(value));
        m_rear->next = node;
        m_rear = node;
    }

    /// 出队（删除头结点后第一个节点）
    std::optional<T> dequeue() noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        node_type* del = m_head->next;
        T value = std::move(del->data);
        m_head->next = del->next;
        if (m_rear == del) {
            m_rear = m_head;
        }
        delete del;
        return value;
    }

    /// 获取队头元素
    [[nodiscard]] std::optional<T> front() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_head->next->data;
    }

    /// 获取队尾元素
    [[nodiscard]] std::optional<T> back() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_rear->data;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_head == m_rear;
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
        m_head = new node_type(T{});
        m_rear = m_head;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "Queue[front]: ";
        node_type* cur = m_head->next;
        while (cur) {
            os << cur->data << " ";
            cur = cur->next;
        }
        os << "[rear]\n";
    }

private:
    node_type* m_head;
    node_type* m_rear;

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

#endif // DATA_STRUCTURES_QUEUE_LIST_H
