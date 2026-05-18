#ifndef DATA_STRUCTURES_SEARCH_H
#define DATA_STRUCTURES_SEARCH_H

#include <functional>
#include <iostream>
#include <optional>
#include <span>
#include <vector>

/**
 * @file search.h
 * @brief 查找算法 —— 顺序查找与二分查找
 *
 * @details
 * 提供在有序（二分查找）和无序（顺序查找）数组上进行查找的算法。
 *
 * ## 时间复杂度
 * - 顺序查找: O(n)
 * - 二分查找: O(log n)
 *
 * ## 应用场景
 * - 顺序查找：小规模数据、无序数据
 * - 二分查找：有序数据的大规模查找
 */

/// 顺序查找（无序数组）
template <typename T>
[[nodiscard]] std::optional<std::size_t> seq_search(std::span<const T> arr, const T& key) noexcept
{
    for (std::size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == key) {
            return i;
        }
    }
    return std::nullopt;
}

/// 顺序查找（带哨兵版，避免每次循环比较边界）
template <typename T>
[[nodiscard]] std::optional<std::size_t> seq_search_sentinel(std::vector<T> arr, const T& key) noexcept
{
    if (arr.empty()) {
        return std::nullopt;
    }
    arr.push_back(key);  // 在末尾添加哨兵
    std::size_t i = 0;
    while (arr[i] != key) {
        ++i;
    }
    if (i < arr.size() - 1) {
        return i;
    }
    return std::nullopt;
}

/// 二分查找（非递归），数组必须有序
template <typename T>
[[nodiscard]] std::optional<std::size_t> bin_search(std::span<const T> arr, const T& key) noexcept
{
    std::size_t low = 0;
    std::size_t high = arr.size();
    while (low < high) {
        std::size_t mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return std::nullopt;
}

/// 二分查找（递归版），数组必须有序
template <typename T>
[[nodiscard]] std::optional<std::size_t> bin_search_recursive(std::span<const T> arr, const T& key,
                                                               std::size_t low, std::size_t high) noexcept
{
    if (low >= high) {
        return std::nullopt;
    }
    std::size_t mid = low + (high - low) / 2;
    if (arr[mid] == key) {
        return mid;
    }
    if (arr[mid] < key) {
        return bin_search_recursive(arr, key, mid + 1, high);
    }
    return bin_search_recursive(arr, key, low, mid);
}

/// 二分查找变体：查找第一个大于等于 key 的元素（lower_bound）
template <typename T>
[[nodiscard]] std::optional<std::size_t> lower_bound(std::span<const T> arr, const T& key) noexcept
{
    std::size_t low = 0;
    std::size_t high = arr.size();
    while (low < high) {
        std::size_t mid = low + (high - low) / 2;
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    if (low < arr.size()) {
        return low;
    }
    return std::nullopt;
}

/// 二分查找变体：查找第一个大于 key 的元素（upper_bound）
template <typename T>
[[nodiscard]] std::optional<std::size_t> upper_bound(std::span<const T> arr, const T& key) noexcept
{
    std::size_t low = 0;
    std::size_t high = arr.size();
    while (low < high) {
        std::size_t mid = low + (high - low) / 2;
        if (arr[mid] <= key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    if (low < arr.size()) {
        return low;
    }
    return std::nullopt;
}

#endif // DATA_STRUCTURES_SEARCH_H
