#include "trie.h"
#include <iostream>

int main()
{
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("help");
    trie.insert("he");
    trie.insert("hero");

    std::cout << std::boolalpha;
    std::cout << "search hello: " << trie.search("hello") << "\n";
    std::cout << "search hell: " << trie.search("hell") << "\n";
    std::cout << "starts_with he: " << trie.starts_with("he") << "\n";
    std::cout << "count_prefix he: " << trie.count_prefix("he") << "\n";

    auto words = trie.all_words();
    std::cout << "所有单词: ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n";

    auto completions = trie.autocomplete("hel");
    std::cout << "hel 自动补全: ";
    for (const auto& w : completions) std::cout << w << " ";
    std::cout << "\n";

    trie.erase("hero");
    std::cout << "删除 hero 后:\n";
    trie.print();

    return 0;
}
