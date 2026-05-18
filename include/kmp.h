#ifndef DATA_STRUCTURES_KMP_H
#define DATA_STRUCTURES_KMP_H

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

/**
 * @file kmp.h
 * @brief KMP 字符串匹配算法（Knuth-Morris-Pratt）
 *
 * @details
 * KMP 算法通过预处理模式串的 next 数组（部分匹配表），
 * 在匹配失败时利用已匹配信息跳过不必要的比较，
 * 避免暴力算法的回溯，达到线性时间复杂度。
 *
 * ## 时间复杂度
 * - 预处理 next 数组: O(m)，m 为模式串长度
 * - 匹配: O(n)，n 为文本串长度
 * - 总: O(m + n)
 *
 * ## 应用场景
 * - 字符串模式匹配
 * - 文本编辑器中的查找功能
 * - 生物信息学中的基因序列匹配
 * - 网络入侵检测中的特征匹配
 */

namespace kmp {

/// 构建 next 数组（部分匹配表）
/// next[i] 表示 pattern[0..i] 的最长相等前后缀长度
[[nodiscard]] inline std::vector<int> build_next(std::string_view pattern)
{
    int m = static_cast<int>(pattern.size());
    std::vector<int> next(m, 0);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

/// KMP 搜索，返回所有匹配位置的起始索引
[[nodiscard]] inline std::vector<std::size_t> search(std::string_view text,
                                                      std::string_view pattern)
{
    std::vector<std::size_t> result;
    if (pattern.empty()) {
        return result;
    }
    std::vector<int> next = build_next(pattern);
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());

    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            result.push_back(static_cast<std::size_t>(i - m + 1));
            j = next[j - 1];  // 继续搜索后续匹配
        }
    }
    return result;
}

/// 判断 pattern 是否在 text 中出现
[[nodiscard]] inline bool contains(std::string_view text, std::string_view pattern)
{
    return !search(text, pattern).empty();
}

/// 计算 pattern 在 text 中出现的次数
[[nodiscard]] inline int count(std::string_view text, std::string_view pattern)
{
    return static_cast<int>(search(text, pattern).size());
}

} // namespace kmp

#endif // DATA_STRUCTURES_KMP_H
