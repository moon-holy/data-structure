#ifndef DATA_STRUCTURES_STACK_ARRAY_H
#define DATA_STRUCTURES_STACK_ARRAY_H

#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

/**
 * @file stack_array.h
 * @brief 顺序栈（Array-based Stack）—— 栈的顺序存储实现
 *
 * @details
 * 栈是一种操作受限的线性表，只允许在栈顶进行插入和删除操作，遵循后进先出（LIFO）原则。
 *
 * ## 时间复杂度
 * - 入栈: O(1)
 * - 出栈: O(1)
 * - 取栈顶: O(1)
 *
 * ## 应用场景
 * - 函数调用栈
 * - 表达式求值与括号匹配
 * - 深度优先搜索（DFS）
 * - 撤销操作（Undo）
 *
 * @tparam T 元素类型
 */

template <typename T>
class ArrayStack {
public:
    using value_type = T;
    using size_type  = std::size_t;

    ArrayStack() noexcept = default;

    explicit ArrayStack(size_type capacity)
        : m_data(capacity)
    {
    }

    ArrayStack(std::initializer_list<T> ilist)
        : m_data(ilist)
    {
    }

    ArrayStack(const ArrayStack&) = default;
    ArrayStack(ArrayStack&&) noexcept = default;
    ArrayStack& operator=(const ArrayStack&) = default;
    ArrayStack& operator=(ArrayStack&&) noexcept = default;

    /// 入栈
    void push(const T& value)
    {
        m_data.push_back(value);
    }

    void push(T&& value)
    {
        m_data.push_back(std::move(value));
    }

    /// 出栈
    void pop()
    {
        m_data.pop_back();
    }

    /// 出栈并返回元素
    std::optional<T> try_pop() noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        T value = std::move(m_data.back());
        m_data.pop_back();
        return value;
    }

    /// 获取栈顶元素
    [[nodiscard]] std::optional<T> top() const noexcept
    {
        if (empty()) {
            return std::nullopt;
        }
        return m_data.back();
    }

    /// 获取栈顶元素的引用
    [[nodiscard]] T& top_ref()
    {
        return m_data.back();
    }

    [[nodiscard]] const T& top_ref() const
    {
        return m_data.back();
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_data.empty();
    }

    [[nodiscard]] size_type size() const noexcept
    {
        return m_data.size();
    }

    void clear() noexcept
    {
        m_data.clear();
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "Stack[bottom]: ";
        for (const auto& v : m_data) {
            os << v << " ";
        }
        os << "[top]\n";
    }

private:
    std::vector<T> m_data;
};

#endif // DATA_STRUCTURES_STACK_ARRAY_H
