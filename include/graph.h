#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <span>
#include <stack>
#include <vector>

/**
 * @file graph.h
 * @brief 图（Graph）—— 邻接矩阵与邻接表存储，以及经典图算法
 *
 * @details
 * 本文件实现了图的两种存储结构（邻接矩阵和邻接表），以及以下经典算法：
 * - 深度优先搜索 (DFS)
 * - 广度优先搜索 (BFS)
 * - Prim 最小生成树
 * - Kruskal 最小生成树
 * - Dijkstra 单源最短路径
 * - Floyd 多源最短路径
 * - 拓扑排序
 *
 * ## 应用场景
 * - 社交网络（好友推荐）
 * - 地图导航（最短路径）
 * - 网络拓扑（路由算法）
 * - 任务调度（拓扑排序）
 * - 电路设计（连通性分析）
 */

/// 无穷大常量
constexpr int INF = std::numeric_limits<int>::max() / 2;

// ============================================================
// 边信息（用于 Kruskal）
// ============================================================

struct Edge {
    int from;
    int to;
    int weight;

    bool operator<(const Edge& other) const noexcept
    {
        return weight < other.weight;
    }
};

// ============================================================
// 邻接表节点
// ============================================================

struct ArcNode {
    int     adjvex;     // 边指向的顶点编号
    int     weight;     // 边的权值
    ArcNode* next;      // 下一条边
};

struct VNode {
    int     data;       // 顶点信息
    ArcNode* first;     // 第一条边
};

struct ALGraph {
    std::vector<VNode>  adjlist;
    int                 n;  // 顶点数
    int                 e;  // 边数
};

// ============================================================
// 图类
// ============================================================

class Graph {
public:
    Graph() noexcept = default;

    /// 从邻接矩阵创建图（适用于稠密图）
    /// @param matrix 邻接矩阵，n x n，0 表示无自环，INF 表示无边
    /// @param n 顶点数
    void from_matrix(std::span<const std::vector<int>> matrix, int n)
    {
        m_n = n;
        m_matrix.assign(n, std::vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    m_matrix[i][j] = 0;
                } else if (matrix[i][j] != INF) {
                    m_matrix[i][j] = matrix[i][j];
                }
            }
        }
    }

    /// 从边列表构建图
    void from_edges(int n, std::span<const ::Edge> edges, bool directed = false)
    {
        m_n = n;
        m_directed = directed;
        m_matrix.assign(n, std::vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            m_matrix[i][i] = 0;
        }
        m_adjlist.adjlist.resize(n);
        m_adjlist.n = n;

        for (const auto& e : edges) {
            m_matrix[e.from][e.to] = e.weight;
            m_adjlist.e++;

            auto* node = new ArcNode{e.to, e.weight, m_adjlist.adjlist[e.from].first};
            m_adjlist.adjlist[e.from].first = node;

            if (!directed) {
                m_matrix[e.to][e.from] = e.weight;
                auto* node2 = new ArcNode{e.from, e.weight, m_adjlist.adjlist[e.to].first};
                m_adjlist.adjlist[e.to].first = node2;
            }
        }
    }

    ~Graph() noexcept
    {
        destroy_adjlist();
    }

    // 禁止拷贝（包含复杂指针结构）
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    // 允许移动
    Graph(Graph&& other) noexcept
        : m_matrix(std::move(other.m_matrix))
        , m_adjlist(std::move(other.m_adjlist))
        , m_n(other.m_n), m_e(other.m_e), m_directed(other.m_directed)
    {
        other.m_n = 0;
        other.m_e = 0;
    }

    Graph& operator=(Graph&& other) noexcept
    {
        if (this != &other) {
            destroy_adjlist();
            m_matrix = std::move(other.m_matrix);
            m_adjlist = std::move(other.m_adjlist);
            m_n = other.m_n; other.m_n = 0;
            m_e = other.m_e; other.m_e = 0;
            m_directed = other.m_directed;
        }
        return *this;
    }

    // ============================================================
    // 基本属性
    // ============================================================

    [[nodiscard]] int vertex_count() const noexcept { return m_n; }
    [[nodiscard]] int edge_count()    const noexcept { return m_e; }
    [[nodiscard]] bool is_directed()  const noexcept { return m_directed; }

    // ============================================================
    // 邻接矩阵输出
    // ============================================================

    void print_matrix(std::ostream& os = std::cout) const
    {
        for (int i = 0; i < m_n; ++i) {
            for (int j = 0; j < m_n; ++j) {
                if (m_matrix[i][j] >= INF / 2) {
                    os << " ∞ ";
                } else {
                    os << " " << m_matrix[i][j] << " ";
                }
            }
            os << '\n';
        }
    }

    /// 打印邻接表
    void print_adjlist(std::ostream& os = std::cout) const
    {
        for (int i = 0; i < m_adjlist.n; ++i) {
            os << "[" << i << "]";
            ArcNode* p = m_adjlist.adjlist[i].first;
            while (p) {
                os << " -> " << p->adjvex << "(" << p->weight << ")";
                p = p->next;
            }
            os << '\n';
        }
    }

    // ============================================================
    // DFS（深度优先搜索）
    // ============================================================

    void dfs(int start, std::function<void(int)> visit) const
    {
        std::vector<bool> visited(m_n, false);
        dfs_recursive(start, visited, visit);
    }

    void dfs_all(std::function<void(int)> visit) const
    {
        std::vector<bool> visited(m_n, false);
        for (int i = 0; i < m_n; ++i) {
            if (!visited[i]) {
                dfs_recursive(i, visited, visit);
            }
        }
    }

    // ============================================================
    // BFS（广度优先搜索）
    // ============================================================

    void bfs(int start, std::function<void(int)> visit) const
    {
        std::vector<bool> visited(m_n, false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            visit(v);

            ArcNode* p = m_adjlist.adjlist[v].first;
            while (p) {
                if (!visited[p->adjvex]) {
                    visited[p->adjvex] = true;
                    q.push(p->adjvex);
                }
                p = p->next;
            }
        }
    }

    // ============================================================
    // Prim 最小生成树
    // ============================================================

    /// Prim 算法，返回最小生成树的边权和；非连通图返回 -1
    std::optional<int> prim() const
    {
        if (m_n == 0) { return 0; }
        std::vector<int> lowcost(m_n, INF);
        std::vector<int> closest(m_n, -1);
        std::vector<bool> in_mst(m_n, false);

        lowcost[0] = 0;
        int total = 0;

        for (int i = 0; i < m_n; ++i) {
            // 找当前最小边
            int u = -1;
            int min_val = INF;
            for (int j = 0; j < m_n; ++j) {
                if (!in_mst[j] && lowcost[j] < min_val) {
                    min_val = lowcost[j];
                    u = j;
                }
            }
            if (u == -1) {
                return std::nullopt;  // 非连通图
            }
            in_mst[u] = true;
            total += min_val;

            for (int v = 0; v < m_n; ++v) {
                if (!in_mst[v] && m_matrix[u][v] < lowcost[v]) {
                    lowcost[v] = m_matrix[u][v];
                    closest[v] = u;
                }
            }
        }
        return total;
    }

    // ============================================================
    // Kruskal 最小生成树
    // ============================================================

    /// Kruskal 算法，返回边权和
    std::optional<int> kruskal() const
    {
        std::vector<Edge> edges;
        for (int i = 0; i < m_n; ++i) {
            for (int j = i + 1; j < m_n; ++j) {
                if (m_matrix[i][j] < INF / 2) {
                    edges.push_back({i, j, m_matrix[i][j]});
                }
            }
        }
        std::sort(edges.begin(), edges.end());

        // 并查集
        std::vector<int> parent(m_n);
        for (int i = 0; i < m_n; ++i) { parent[i] = i; }
        std::function<int(int)> find = [&](int x) -> int {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        auto unite = [&](int a, int b) {
            parent[find(a)] = find(b);
        };

        int total = 0;
        int count = 0;
        for (const auto& e : edges) {
            if (find(e.from) != find(e.to)) {
                unite(e.from, e.to);
                total += e.weight;
                ++count;
            }
        }
        if (count != m_n - 1) {
            return std::nullopt;  // 非连通图
        }
        return total;
    }

    // ============================================================
    // Dijkstra 单源最短路径
    // ============================================================

    /// Dijkstra 算法，返回从 start 到各点的最短距离
    std::vector<int> dijkstra(int start) const
    {
        std::vector<int> dist(m_n, INF);
        std::vector<bool> visited(m_n, false);
        dist[start] = 0;

        for (int i = 0; i < m_n; ++i) {
            int u = -1;
            int min_dist = INF;
            for (int j = 0; j < m_n; ++j) {
                if (!visited[j] && dist[j] < min_dist) {
                    min_dist = dist[j];
                    u = j;
                }
            }
            if (u == -1) { break; }
            visited[u] = true;

            for (int v = 0; v < m_n; ++v) {
                if (!visited[v] && m_matrix[u][v] < INF / 2 &&
                    dist[u] + m_matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + m_matrix[u][v];
                }
            }
        }
        return dist;
    }

    /// Dijkstra + 路径还原
    std::pair<std::vector<int>, std::vector<int>> dijkstra_with_path(int start) const
    {
        std::vector<int> dist(m_n, INF);
        std::vector<int> prev(m_n, -1);
        std::vector<bool> visited(m_n, false);
        dist[start] = 0;

        for (int i = 0; i < m_n; ++i) {
            int u = -1;
            int min_dist = INF;
            for (int j = 0; j < m_n; ++j) {
                if (!visited[j] && dist[j] < min_dist) {
                    min_dist = dist[j];
                    u = j;
                }
            }
            if (u == -1) { break; }
            visited[u] = true;

            for (int v = 0; v < m_n; ++v) {
                if (!visited[v] && m_matrix[u][v] < INF / 2 &&
                    dist[u] + m_matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + m_matrix[u][v];
                    prev[v] = u;
                }
            }
        }
        return {dist, prev};
    }

    /// 根据 prev 数组还原路径
    static std::vector<int> reconstruct_path(int start, int end, const std::vector<int>& prev)
    {
        std::vector<int> path;
        for (int v = end; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());
        if (path.front() != start) {
            path.clear();  // 不可达
        }
        return path;
    }

    // ============================================================
    // Floyd 多源最短路径
    // ============================================================

    /// Floyd 算法，返回所有点对之间的最短距离矩阵
    std::vector<std::vector<int>> floyd() const
    {
        std::vector<std::vector<int>> dist = m_matrix;
        for (int k = 0; k < m_n; ++k) {
            for (int i = 0; i < m_n; ++i) {
                for (int j = 0; j < m_n; ++j) {
                    if (dist[i][k] < INF / 2 && dist[k][j] < INF / 2 &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        return dist;
    }

    // ============================================================
    // 拓扑排序（仅限有向图）
    // ============================================================

    /// 拓扑排序（Kahn 算法），成功返回排序结果，有环返回 nullopt
    std::optional<std::vector<int>> topological_sort() const
    {
        if (!m_directed) {
            return std::nullopt;  // 无向图不适用
        }
        std::vector<int> in_degree(m_n, 0);
        for (int u = 0; u < m_n; ++u) {
            ArcNode* p = m_adjlist.adjlist[u].first;
            while (p) {
                in_degree[p->adjvex]++;
                p = p->next;
            }
        }

        std::queue<int> q;
        for (int i = 0; i < m_n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> result;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);

            ArcNode* p = m_adjlist.adjlist[u].first;
            while (p) {
                if (--in_degree[p->adjvex] == 0) {
                    q.push(p->adjvex);
                }
                p = p->next;
            }
        }
        if (static_cast<int>(result.size()) != m_n) {
            return std::nullopt;  // 有环
        }
        return result;
    }

private:
    std::vector<std::vector<int>> m_matrix;
    ALGraph m_adjlist;
    int m_n{0};
    int m_e{0};
    bool m_directed{false};

    void dfs_recursive(int v, std::vector<bool>& visited, std::function<void(int)>& visit) const
    {
        visited[v] = true;
        visit(v);
        ArcNode* p = m_adjlist.adjlist[v].first;
        while (p) {
            if (!visited[p->adjvex]) {
                dfs_recursive(p->adjvex, visited, visit);
            }
            p = p->next;
        }
    }

    void destroy_adjlist() noexcept
    {
        for (int i = 0; i < m_adjlist.n; ++i) {
            ArcNode* p = m_adjlist.adjlist[i].first;
            while (p) {
                ArcNode* next = p->next;
                delete p;
                p = next;
            }
        }
        m_adjlist.adjlist.clear();
        m_adjlist.n = 0;
        m_adjlist.e = 0;
    }
};

#endif // DATA_STRUCTURES_GRAPH_H
