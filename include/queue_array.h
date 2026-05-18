#ifndef DATA_STRUCTURES_QUEUE_ARRAY_H
#define DATA_STRUCTURES_QUEUE_ARRAY_H

#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

/**
 * @file queue_array.h
 * @brief 顺序队列（Array-based Queue）—— 非循环
 *
 * @details
 * 队列是一种先进先出（FIFO）的线性表，只允许在队尾插入、队头删除。
 * 非循环顺序队列存在"假溢出"问题（前面位置空闲但 rear 已到末尾）。
 * 实际使用建议使用循环队列 @ref CircularQueue。
 *
 * ## 时间复杂度
 * - 入队: O(1)
 * - 出队: O(1)
 *
 * ## 应用场景
 * - 简单的 FIFO 场景（数据量已知且较小）
 */

template <typename T>
class ArrayQueue {
public:
    using value_type = T;
    using size_type  = std::size_t;

    ArrayQueue() noexcept = default;

    explicit ArrayQueue(size_type capacity)
        : m_data(capacity)
    {
    }

    ArrayQueue(std::initializer_list<T> ilist)
        : m_data(ilist), m_rear(ilist.size())
    {
    }

    /// 入队
    bool enqueue(const T& value)
    {
        if (m_rear >= m_data.size()) {
            m_data.push_back(value);
            ++m_rear;
            return true;
        }
        m_data[m_rear] = value;
        ++m_rear;
        return true;
    }

    bool enqueue(T&& value)
    {
        if (m_rear >= m_data.size()) {
            m_data.push_back(std::move(value));
            ++m_rear;
            return true;
        }
        m_data[m_rear] = std::move(value);
        ++m_rear;
        return true;
    }

    /// 出队
    std::optional<T> dequeue() noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        T value = std::move(m_data[m_front]);
        ++m_front;
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
        return m_data[m_rear - 1];
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_front >= m_rear;
    }

    [[nodiscard]] size_type size() const noexcept
    {
        return m_rear - m_front;
    }

    void clear() noexcept
    {
        m_front = 0;
        m_rear = 0;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "Queue[front]: ";
        for (size_type i = m_front; i < m_rear; ++i) {
            os << m_data[i] << " ";
        }
        os << "[rear]\n";
    }

private:
    std::vector<T> m_data;
    size_type m_front{0};
    size_type m_rear{0};
};

#endif // DATA_STRUCTURES_QUEUE_ARRAY_H
