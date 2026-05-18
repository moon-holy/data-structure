# 数据结构与算法（C++23 实现）

[![C++23](https://img.shields.io/badge/C%2B%2B-23-00599C?logo=cplusplus)](https://en.cppreference.com/w/cpp/23)
[![VS2022](https://img.shields.io/badge/MSVC-VS2022%2017.14-5C2D91?logo=microsoft)](https://visualstudio.microsoft.com/)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)

**经典数据结构的现代 C++23 实现**，包含 22 个常用数据结构与算法，覆盖线性表、栈队列、树、图、排序、查找等核心知识领域。

## 目录结构

```
data-structure/
├── include/          # 头文件（模板实现）
│   ├── sqlist.h             顺序表
│   ├── linklist_single.h    单链表
│   ├── linklist_double.h    双链表
│   ├── stack_array.h        顺序栈
│   ├── stack_list.h         链式栈
│   ├── queue_array.h        顺序队列
│   ├── queue_circular.h     循环队列
│   ├── queue_list.h         链式队列
│   ├── bst.h                二叉搜索树
│   ├── avl_tree.h           AVL 平衡树
│   ├── trie.h               字典树
│   ├── heap.h               二叉堆
│   ├── graph.h              图
│   ├── sort.h               排序算法
│   ├── search.h             查找算法
│   ├── skiptable.h          跳表
│   ├── sparsetable.h        稀疏表
│   ├── hash_table.h         哈希表
│   ├── union_find.h         并查集
│   ├── segment_tree.h       线段树
│   ├── fenwick_tree.h       树状数组
│   └── kmp.h                KMP 字符串匹配
├── examples/         # 22 个 demo 示例
│   └── 01_sqlist_demo.cpp ~ 22_kmp_demo.cpp
├── docs/
│   └── data_structures.md   数据结构详细文档
├── CMakeLists.txt           构建系统
└── README.md                本文件
```

## 特性

- **C++23 标准**：使用 `std::optional`、`std::span`、`std::string_view`、`if constexpr`、`deducing this` 等现代特性
- **完整的错误处理**：函数返回 `std::optional<T>` 而非魔法值
- **RAII 资源管理**：所有动态内存自动管理，无内存泄漏
- **泛型设计**：模板化实现，支持任意数据类型
- **详细注释**：中文文档注释，包含复杂度分析和应用场景
- **全面的文档**：[docs/data_structures.md](docs/data_structures.md) 包含每个数据结构的理论介绍和实际应用

## 构建方法

### 前置要求

- Visual Studio 2022 17.14+
- CMake 3.20+

### 使用 CMake 构建

```bash
# 在 "x64 Native Tools Command Prompt for VS 2022" 中执行
cd data-structure
mkdir build && cd build
cmake .. -G "Ninja"   # 或 "Visual Studio 17 2022"
cmake --build .       # 编译所有 22 个 demo
```

### 手动编译单个示例

```bash
cl /std:c++latest /EHsc /I include examples\01_sqlist_demo.cpp
```

## 数据总览

| # | 数据结构 | 头文件 | 核心操作时间复杂度 |
|---|---------|--------|------------------|
| 1 | 顺序表 | `sqlist.h` | 访问 O(1)，插入/删除 O(n) |
| 2 | 单链表 | `linklist_single.h` | 头插 O(1)，查找 O(n) |
| 3 | 双链表 | `linklist_double.h` | 头尾 O(1)，查找 O(n) |
| 4 | 顺序栈 | `stack_array.h` | 全 O(1) |
| 5 | 链式栈 | `stack_list.h` | 全 O(1) |
| 6 | 顺序队列 | `queue_array.h` | 全 O(1) |
| 7 | 循环队列 | `queue_circular.h` | 全 O(1) |
| 8 | 链式队列 | `queue_list.h` | 全 O(1) |
| 9 | BST | `bst.h` | 均摊 O(log n) |
| 10 | AVL 树 | `avl_tree.h` | 严格 O(log n) |
| 11 | 字典树 | `trie.h` | O(m)，m 为键长 |
| 12 | 二叉堆 | `heap.h` | push/pop O(log n) |
| 13 | 图 | `graph.h` | 见具体算法 |
| 14 | 排序 | `sort.h` | 见具体算法 |
| 15 | 查找 | `search.h` | 二分 O(log n) |
| 16 | 跳表 | `skiptable.h` | 期望 O(log n) |
| 17 | 稀疏表 | `sparsetable.h` | 查询 O(1) |
| 18 | 哈希表 | `hash_table.h` | 平均 O(1) |
| 19 | 并查集 | `union_find.h` | O(α(n)) |
| 20 | 线段树 | `segment_tree.h` | O(log n) |
| 21 | 树状数组 | `fenwick_tree.h` | O(log n) |
| 22 | KMP | `kmp.h` | O(m+n) |

## 项目迁移说明

本项目从旧版 C++98/11 风格完全重构，主要变更：

- 文件从单一 `.cpp` 迁移为 `.h` 头文件 + `examples/*_demo.cpp`
- 空/0/-1 等哨兵值替换为 `std::optional<T>`
- `int n + T arr[]` 参数替换为 `std::span<const T>`
- 修复了原代码中的多处 bug（循环队列方向错误、二分查找逻辑错误、双链表空实现等）
- 新增 8 个数据结构
- 补全了图算法（Prim、Kruskal、Dijkstra、Floyd、拓扑排序）
- 添加 CMake 构建系统

## 许可

MIT License
