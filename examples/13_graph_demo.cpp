#include "graph.h"
#include <iostream>

int main()
{
    // 无向图
    Graph g;
    std::vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };
    g.from_edges(5, edges, false);

    std::cout << "邻接表:\n"; g.print_adjlist();
    std::cout << "邻接矩阵:\n"; g.print_matrix();

    std::cout << "\nDFS from 0: "; g.dfs(0, [](int v) { std::cout << v << " "; });
    std::cout << "\nBFS from 0: "; g.bfs(0, [](int v) { std::cout << v << " "; });
    std::cout << "\n";

    // 最小生成树
    auto mst = g.prim();
    if (mst) std::cout << "Prim MST 权值: " << *mst << "\n";

    auto mst2 = g.kruskal();
    if (mst2) std::cout << "Kruskal MST 权值: " << *mst2 << "\n";

    // 最短路径
    auto [dist, prev] = g.dijkstra_with_path(0);
    std::cout << "Dijkstra from 0:\n";
    for (int i = 0; i < 5; ++i) {
        auto path = Graph::reconstruct_path(0, i, prev);
        std::cout << "  to " << i << ": dist=" << dist[i] << " path=";
        for (auto v : path) std::cout << v << " ";
        std::cout << "\n";
    }

    // Floyd
    auto all_dist = g.floyd();
    std::cout << "Floyd 最短路径矩阵:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (all_dist[i][j] >= INF / 2) std::cout << " ∞ ";
            else std::cout << " " << all_dist[i][j] << " ";
        }
        std::cout << "\n";
    }

    // 有向图拓扑排序
    Graph dag;
    std::vector<Edge> de = {{0,1,1},{0,2,1},{1,3,1},{2,3,1},{3,4,1}};
    dag.from_edges(5, de, true);
    auto topo = dag.topological_sort();
    if (topo) {
        std::cout << "拓扑排序: ";
        for (auto v : *topo) std::cout << v << " ";
        std::cout << "\n";
    }

    return 0;
}
