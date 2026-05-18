#ifndef DATA_STRUCTURES_QUEUE_CIRCULAR_H
#define DATA_STRUCTURES_QUEUE_CIRCULAR_H

#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>

/**
 * @file queue_circular.h
 * @brief 循环队列（Circular Queue）—— 队列的顺序循环存储
 *
 * @details
 * 循环队列通过将存储空间在逻辑上视为首尾相连的环，解决了"假溢出"问题。
 * 使用 (rear+1) % capacity == front 判断队满，会浪费一个元素空间。
 *
 * ## 时间复杂度
 * - 入队: O(1)（均摊）
 * - 出队: O(1)
 * - 取队首/尾: O(1)
 *
 * ## 应用场景
 * - 固定大小的缓冲区（如环形缓冲区、IO 缓冲）
 * - 生产者-消费者模型
 * - 网络数据包缓冲
 *
 * @tparam T 元素类型
 */

template <typename T>
class CircularQueue {
public:
    using value_type = T;
    using size_type  = std::size_t;

    explicit CircularQueue(size_type capacity = 16)
        : m_capacity(capacity + 1)  // 多一个空间用于区分空/满
        , m_data(std::make_unique<T[]>(m_capacity))
        , m_front(0), m_rear(0)
    {
    }

    CircularQueue(std::initializer_list<T> ilist)
        : CircularQueue(ilist.size())
    {
        for (const auto& v : ilist) {
            enqueue(v);
        }
    }

    CircularQueue(const CircularQueue& other)
        : m_capacity(other.m_capacity)
        , m_data(std::make_unique<T[]>(m_capacity))
        , m_front(other.m_front)
        , m_rear(other.m_rear)
    {
        size_type i = other.m_front;
        while (i != other.m_rear) {
            m_data[i] = other.m_data[i];
            i = (i + 1) % m_capacity;
        }
    }

    CircularQueue(CircularQueue&& other) noexcept = default;

    CircularQueue& operator=(const CircularQueue& other)
    {
        if (this != &other) {
            CircularQueue tmp(other);
            swap(tmp);
        }
        return *this;
    }

    CircularQueue& operator=(CircularQueue&& other) noexcept = default;

    void swap(CircularQueue& other) noexcept
    {
        using std::swap;
        swap(m_capacity, other.m_capacity);
        swap(m_data, other.m_data);
        swap(m_front, other.m_front);
        swap(m_rear, other.m_rear);
    }

    /// 入队
    bool enqueue(const T& value)
    {
        if (full()) {
            resize();
        }
        m_data[m_rear] = value;
        m_rear = (m_rear + 1) % m_capacity;
        return true;
    }

    bool enqueue(T&& value)
    {
        if (full()) {
            resize();
        }
        m_data[m_rear] = std::move(value);
        m_rear = (m_rear + 1) % m_capacity;
        return true;
    }

    /// 出队
    std::optional<T> dequeue() noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        T value = std::move(m_data[m_front]);
        m_front = (m_front + 1) % m_capacity;
        return value;
    }

    /// 获取队头元素
    [[nodiscard]] std::optional<T> front() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_data[m_front];
    }

    /// 获取队尾元素
    [[nodiscard]] std::optional<T> back() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_data[(m_rear - 1 + m_capacity) % m_capacity];
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_front == m_rear;
    }

    [[nodiscard]] bool full() const noexcept
    {
        return (m_rear + 1) % m_capacity == m_front;
    }

    [[nodiscard]] size_type size() const noexcept
    {
        return (m_rear - m_front + m_capacity) % m_capacity;
    }

    [[nodiscard]] size_type capacity() const noexcept
    {
        return m_capacity - 1;
    }

    void clear() noexcept
    {
        m_front = m_rear = 0;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "CircularQueue[front]: ";
        size_type i = m_front;
        while (i != m_rear) {
            os << m_data[i] << " ";
            i = (i + 1) % m_capacity;
        }
        os << "[rear]\n";
    }

private:
    size_type               m_capacity;
    std::unique_ptr<T[]>    m_data;
    size_type               m_front{0};
    size_type               m_rear{0};

    void resize()
    {
        size_type new_cap = m_capacity * 2;
        auto new_data = std::make_unique<T[]>(new_cap);
        size_type i = m_front;
        size_type j = 0;
        while (i != m_rear) {
            new_data[j++] = std::move(m_data[i]);
            i = (i + 1) % m_capacity;
        }
        m_front = 0;
        m_rear = j;
        m_capacity = new_cap;
        m_data = std::move(new_data);
    }
};

#endif // DATA_STRUCTURES_QUEUE_CIRCULAR_H
