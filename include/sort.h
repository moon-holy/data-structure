#ifndef DATA_STRUCTURES_SORT_H
#define DATA_STRUCTURES_SORT_H

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <span>
#include <vector>

/**
 * @file sort.h
 * @brief 经典排序算法集合
 *
 * @details
 * 提供多种经典排序算法的实现，支持自定义比较器。
 *
 * ## 各算法时间复杂度
 * | 算法 | 平均 | 最坏 | 最好 | 空间 | 稳定 |
 * |------|------|------|------|------|------|
 * | 插入排序 | O(n²) | O(n²) | O(n) | O(1) | 是 |
 * | 冒泡排序 | O(n²) | O(n²) | O(n) | O(1) | 是 |
 * | 选择排序 | O(n²) | O(n²) | O(n²) | O(1) | 否 |
 * | 快速排序 | O(n log n) | O(n²) | O(n log n) | O(log n) | 否 |
 * | 堆排序 | O(n log n) | O(n log n) | O(n log n) | O(1) | 否 |
 * | 归并排序 | O(n log n) | O(n log n) | O(n log n) | O(n) | 是 |
 *
 * ## 应用场景
 * - 插入排序：小规模数据或基本有序的数据
 * - 快速排序：通用大规模排序（默认首选）
 * - 归并排序：外部排序、需要稳定排序
 * - 堆排序：嵌入式等空间受限场景
 */

/// 命名空间，包含所有排序算法
namespace sort {

/// 插入排序
template <typename T, typename Compare = std::less<T>>
void insertion_sort(std::span<T> arr, Compare comp = Compare{})
{
    for (std::size_t i = 1; i < arr.size(); ++i) {
        T key = std::move(arr[i]);
        std::ptrdiff_t j = static_cast<std::ptrdiff_t>(i) - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = std::move(arr[j]);
            --j;
        }
        arr[j + 1] = std::move(key);
    }
}

/// 冒泡排序
template <typename T, typename Compare = std::less<T>>
void bubble_sort(std::span<T> arr, Compare comp = Compare{})
{
    for (std::size_t i = 0; i + 1 < arr.size(); ++i) {
        bool swapped = false;
        for (std::size_t j = arr.size() - 1; j > i; --j) {
            if (comp(arr[j], arr[j - 1])) {
                std::swap(arr[j], arr[j - 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;  // 提前终止优化
        }
    }
}

/// 选择排序
template <typename T, typename Compare = std::less<T>>
void selection_sort(std::span<T> arr, Compare comp = Compare{})
{
    for (std::size_t i = 0; i + 1 < arr.size(); ++i) {
        std::size_t min_idx = i;
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (comp(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

/// 快速排序
template <typename T, typename Compare = std::less<T>>
void quick_sort(std::span<T> arr, Compare comp = Compare{})
{
    if (arr.size() <= 1) {
        return;
    }
    // 三数取中优化
    std::size_t mid = arr.size() / 2;
    if (comp(arr[mid], arr[0]))           { std::swap(arr[0], arr[mid]); }
    if (comp(arr.back(), arr[0]))         { std::swap(arr[0], arr.back()); }
    if (comp(arr.back(), arr[mid]))       { std::swap(arr[mid], arr.back()); }
    std::swap(arr[mid], arr.back());

    const T& pivot = arr.back();
    std::size_t left = 0;
    std::size_t right = arr.size() - 1;

    while (left < right) {
        while (left < right && comp(arr[left], pivot))  { ++left; }
        while (left < right && !comp(arr[right], pivot)) { --right; }
        if (left < right) {
            std::swap(arr[left], arr[right]);
        }
    }
    std::swap(arr[left], arr.back());

    if (left > 0) {
        quick_sort(arr.first(left), comp);
    }
    if (left + 1 < arr.size()) {
        quick_sort(arr.last(arr.size() - left - 1), comp);
    }
}

/// 堆排序
template <typename T, typename Compare = std::less<T>>
void heap_sort(std::span<T> arr, Compare comp = Compare{})
{
    auto sift_down = [&](std::size_t root, std::size_t n) {
        while (true) {
            std::size_t extreme = root;
            std::size_t l = 2 * root + 1;
            std::size_t r = 2 * root + 2;
            if (l < n && comp(arr[extreme], arr[l])) { extreme = l; }
            if (r < n && comp(arr[extreme], arr[r])) { extreme = r; }
            if (extreme == root) { break; }
            std::swap(arr[root], arr[extreme]);
            root = extreme;
        }
    };

    // 建堆 O(n)
    for (std::ptrdiff_t i = static_cast<std::ptrdiff_t>(arr.size() / 2) - 1; i >= 0; --i) {
        sift_down(static_cast<std::size_t>(i), arr.size());
    }
    // 排序 O(n log n)
    for (std::size_t i = arr.size(); i > 1; --i) {
        std::swap(arr[0], arr[i - 1]);
        sift_down(0, i - 1);
    }
}

/// 归并排序
template <typename T, typename Compare = std::less<T>>
void merge_sort(std::span<T> arr, Compare comp = Compare{})
{
    if (arr.size() <= 1) {
        return;
    }
    std::size_t mid = arr.size() / 2;
    auto left = arr.first(mid);
    auto right = arr.last(arr.size() - mid);

    merge_sort(left, comp);
    merge_sort(right, comp);

    // 归并
    std::vector<T> temp;
    temp.reserve(arr.size());
    std::size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (comp(left[i], right[j])) {
            temp.push_back(std::move(left[i++]));
        } else {
            temp.push_back(std::move(right[j++]));
        }
    }
    while (i < left.size()) {
        temp.push_back(std::move(left[i++]));
    }
    while (j < right.size()) {
        temp.push_back(std::move(right[j++]));
    }
    for (std::size_t k = 0; k < temp.size(); ++k) {
        arr[k] = std::move(temp[k]);
    }
}

/// 判断数组是否有序
template <typename T, typename Compare = std::less<T>>
[[nodiscard]] bool is_sorted(std::span<const T> arr, Compare comp = Compare{}) noexcept
{
    for (std::size_t i = 1; i < arr.size(); ++i) {
        if (comp(arr[i], arr[i - 1])) {
            return false;
        }
    }
    return true;
}

/// 打印数组
template <typename T>
void print(std::span<const T> arr, std::ostream& os = std::cout, std::string_view sep = " ")
{
    for (std::size_t i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i + 1 < arr.size()) {
            os << sep;
        }
    }
    os << '\n';
}

} // namespace sort

#endif // DATA_STRUCTURES_SORT_H
