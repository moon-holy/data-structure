#ifndef DATA_STRUCTURES_SQLIST_H
#define DATA_STRUCTURES_SQLIST_H

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <optional>
#include <span>
#include <stdexcept>
#include <vector>

/**
 * @file sqlist.h
 * @brief 顺序表（Sequence List）—— 线性表的顺序存储实现
 *
 * @details
 * 顺序表是一种将数据元素依次存放在一段连续存储单元中的线性表结构。
 * 它支持随机访问，但插入和删除操作需要移动大量元素。
 *
 * ## 时间复杂度
 * - 随机访问: O(1)
 * - 按值查找: O(n)
 * - 插入:     O(n)
 * - 删除:     O(n)
 *
 * ## 应用场景
 * - 需要频繁随机访问的场景（如数组下标访问）
 * - 数据量相对固定，插入删除操作较少
 * - 实现其他数据结构的底层存储（如堆、栈等）
 *
 * @tparam T 元素类型
 */

template <typename T>
class SqList {
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = T*;
    using const_iterator  = const T*;

    /// 默认构造函数，创建一个空顺序表
    SqList() noexcept = default;

    /// 从 std::span 构造
    explicit SqList(std::span<const T> arr)
        : m_data(arr.begin(), arr.end())
    {
    }

    /// 从初始化列表构造
    SqList(std::initializer_list<T> ilist)
        : m_data(ilist)
    {
    }

    /// 复制构造
    SqList(const SqList&) = default;

    /// 移动构造
    SqList(SqList&&) noexcept = default;

    /// 复制赋值
    SqList& operator=(const SqList&) = default;

    /// 移动赋值
    SqList& operator=(SqList&&) noexcept = default;

    ~SqList() noexcept = default;

    // ============================================================
    // 容量
    // ============================================================

    /// 返回元素个数
    [[nodiscard]] size_type size() const noexcept
    {
        return m_data.size();
    }

    /// 判断是否为空
    [[nodiscard]] bool empty() const noexcept
    {
        return m_data.empty();
    }

    /// 返回当前容量
    [[nodiscard]] size_type capacity() const noexcept
    {
        return m_data.capacity();
    }

    /// 预留容量
    void reserve(size_type new_cap)
    {
        m_data.reserve(new_cap);
    }

    // ============================================================
    // 元素访问
    // ============================================================

    /// 随机访问（带边界检查）
    [[nodiscard]] reference at(size_type pos)
    {
        return m_data.at(pos);
    }

    /// 随机访问（带边界检查，const）
    [[nodiscard]] const_reference at(size_type pos) const
    {
        return m_data.at(pos);
    }

    /// 随机访问（不带边界检查）
    [[nodiscard]] reference operator[](size_type pos) noexcept
    {
        return m_data[pos];
    }

    /// 随机访问（不带边界检查，const）
    [[nodiscard]] const_reference operator[](size_type pos) const noexcept
    {
        return m_data[pos];
    }

    /// 返回第一个元素
    [[nodiscard]] reference front()
    {
        return m_data.front();
    }

    /// 返回第一个元素（const）
    [[nodiscard]] const_reference front() const
    {
        return m_data.front();
    }

    /// 返回最后一个元素
    [[nodiscard]] reference back()
    {
        return m_data.back();
    }

    /// 返回最后一个元素（const）
    [[nodiscard]] const_reference back() const
    {
        return m_data.back();
    }

    // ============================================================
    // 查找
    // ============================================================

    /// 按值查找，返回第一个匹配的位置；未找到返回 std::nullopt
    [[nodiscard]] std::optional<size_type> locate(const T& value) const noexcept
    {
        for (size_type i = 0; i < m_data.size(); ++i) {
            if (m_data[i] == value) {
                return i;
            }
        }
        return std::nullopt;
    }

    /// 判断是否包含某个值
    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        return locate(value).has_value();
    }

    // ============================================================
    // 修改操作
    // ============================================================

    /// 在末尾追加元素
    void push_back(const T& value)
    {
        m_data.push_back(value);
    }

    /// 在末尾追加元素（移动语义）
    void push_back(T&& value)
    {
        m_data.push_back(std::move(value));
    }

    /// 删除末尾元素
    void pop_back()
    {
        m_data.pop_back();
    }

    /// 在指定位置插入元素（pos 是 0-based 索引）
    /// @return 如果 pos 合法返回 true，否则返回 false
    bool insert(size_type pos, const T& value)
    {
        if (pos > m_data.size()) {
            return false;
        }
        m_data.insert(m_data.begin() + static_cast<std::ptrdiff_t>(pos), value);
        return true;
    }

    /// 在指定位置插入元素（移动语义）
    bool insert(size_type pos, T&& value)
    {
        if (pos > m_data.size()) {
            return false;
        }
        m_data.insert(m_data.begin() + static_cast<std::ptrdiff_t>(pos), std::move(value));
        return true;
    }

    /// 删除指定位置的元素（0-based）
    /// @return 如果 pos 合法返回 true，否则返回 false
    bool erase(size_type pos)
    {
        if (pos >= m_data.size()) {
            return false;
        }
        m_data.erase(m_data.begin() + static_cast<std::ptrdiff_t>(pos));
        return true;
    }

    /// 清空顺序表
    void clear() noexcept
    {
        m_data.clear();
    }

    // ============================================================
    // 迭代器
    // ============================================================

    [[nodiscard]] iterator begin() noexcept { return m_data.data(); }
    [[nodiscard]] const_iterator begin() const noexcept { return m_data.data(); }
    [[nodiscard]] iterator end() noexcept { return m_data.data() + m_data.size(); }
    [[nodiscard]] const_iterator end() const noexcept { return m_data.data() + m_data.size(); }

    // ============================================================
    // 输出
    // ============================================================

    /// 打印顺序表内容到输出流
    void print(std::ostream& os = std::cout, std::string_view sep = " ") const
    {
        for (size_type i = 0; i < m_data.size(); ++i) {
            os << m_data[i];
            if (i + 1 < m_data.size()) {
                os << sep;
            }
        }
        os << '\n';
    }

private:
    std::vector<T> m_data;
};

#endif // DATA_STRUCTURES_SQLIST_H
