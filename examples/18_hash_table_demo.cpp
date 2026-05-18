#include "hash_table.h"
#include <iostream>

int main()
{
    HashMap<std::string, int> scores;
    scores.insert("Alice", 95);
    scores.insert("Bob", 87);
    scores.insert("Charlie", 92);
    scores.insert("Diana", 78);

    scores.print();

    std::cout << "Bob's score: " << scores.get("Bob").value_or(-1) << "\n";
    std::cout << "contains Alice? " << std::boolalpha << scores.contains("Alice") << "\n";
    std::cout << "contains Eve? " << scores.contains("Eve") << "\n";

    scores.insert("Alice", 99);  // 更新
    std::cout << "Alice after update: " << scores.get("Alice").value_or(-1) << "\n";

    scores.erase("Charlie");
    std::cout << "after erase Charlie:\n"; scores.print();

    std::cout << "size = " << scores.size() << "\n";

    return 0;
}
