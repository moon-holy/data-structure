#include "kmp.h"
#include <iostream>

int main()
{
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    auto matches = kmp::search(text, pattern);
    std::cout << "Text:    " << text << "\n";
    std::cout << "Pattern: " << pattern << "\n";
    std::cout << "匹配位置: ";
    for (auto pos : matches) std::cout << pos << " ";
    std::cout << "\n";
    std::cout << "匹配次数: " << kmp::count(text, pattern) << "\n";
    std::cout << "contains? " << std::boolalpha << kmp::contains(text, pattern) << "\n";

    // next 数组
    auto next = kmp::build_next(pattern);
    std::cout << "next 数组: ";
    for (auto v : next) std::cout << v << " ";
    std::cout << "\n";

    // 无匹配
    std::cout << "\n搜索不存在的模式:\n";
    auto r = kmp::search(text, "XYZ");
    std::cout << "匹配数: " << r.size() << "\n";

    // 空模式
    std::cout << "\n空模式搜索: " << kmp::search(text, "").size() << "\n";

    return 0;
}
