#include<iostream>
#include<iomanip>
using namespace std;

#define MAXL 64
#define MAXV 10         // 图的顶点个数
const int INF = 0x3f3f3f3f;
int visited[MAXV];      //全局变量访问数组

/*
1.图的矩阵存储
2.图的邻接表存储
*/

//  图的邻接矩阵存储方式 // 
struct VertexType       //  顶点信息
{
    int nu;             //  顶点的编号
    char data[MAXL];    //  顶点的其他信息
};

//   存储矩阵信息
template<typename T> 
struct MGraph
{
    T edge[MAXV][MAXV];     //  邻接矩阵的边组数
    int node,edg;           //  定义节点数，边组数
    VertexType vexs[MAXV];  //  存放边组信息
};


//  图的邻接表存储  //
template<typename T> 
struct ArcNode          //  边节点类型
{
    int adjvex;         //  该边的终点编号
    ArcNode *nextarc;   //  指向下一条边的指针
    T weight;           //  该边的相关信息，如边的权值
};

template<typename T> 
struct VNode                //  顶点类型
{
    char data[MAXL];        //  顶点信息
    ArcNode<T> *firstarc;   //  指向第一条边的相邻顶点
};

//  图的邻接表类型
template<typename T> 
struct ALGraph
{
    VNode<T> adjlist[MAXV];         //  存放图顶点的数组
    int n,  e;                      //  图中的顶点数n和边数e
};

//  图的类模板
template<typename T> 
class GraphClass
{
    MGraph<T> g;                //  图的邻接矩阵
    ALGraph<T> *G;              //  图的邻接表
public:
    GraphClass();
    ~GraphClass();
    void CreateMGraph(T a[][MAXV],int n,int e);     //  通过边组数a，顶点数n, 边数e创建图的邻接矩阵
    void DispMGraph();                              //  输出图的邻接矩阵
    void CreateALGraph(T a[][MAXV],int n,int e);    //  通过边组数a，顶点数n,边数e创建图的邻接表
    void DispALGraph();                             //  输出图的邻接表
    void DFS(GraphClass<T> &gobj, int v);
    void BFS(GraphClass<T> &gobj, int v);
private:
    void DestoryGraph();                            //  销毁图的邻接表
    void DFS1(ALGraph<T> *G, int v);
    void BFS1(ALGraph<T> *G, int v);
};


template<typename T> 
GraphClass<T>::GraphClass()
{
    G = nullptr;             
}
template<typename T> 
GraphClass<T>::~GraphClass()
{
    if(G != nullptr)
    {
        DestoryGraph();
    }
}
template<typename T> 
void GraphClass<T>::DestoryGraph()
{
    int i;
    ArcNode<T> *pre, *p;                //  创建查询指针
    for(int i = 0; i < G->n; i++)       //  遍历所以的表头节点
    {
        pre = G -> adjlist[i].firstarc;
        if(pre  !=  nullptr)
        {
            p = pre -> nextarc;
            while (p != nullptr)
            {
                delete pre;         //  后一个节点不为空时，删除前一个节点
                pre = p;
                p = p->nextarc;     //  移动指针
            }
            delete pre;             //  删除最后一个节点
        }
    }
    delete G;                       //  释放G所指头节点数组的内存空间
}


template<typename T>  
void GraphClass<T>::CreateMGraph(T a[][MAXV], int n, int e)
{
    int i, j;
    g.node = n, g.edg = e;      
    for(i = 0;i < g.node; i++)
    {
        for(j = 0;j < g.node; j++)
        {
            g.edge[i][j] = a[i][j];
        }
    }

}
template<typename T>  
void GraphClass<T>::DispMGraph()
{
    int i, j;
    for(i = 0; i < g.node; i++)
    {
        for(j = 0; j < g.node; j++)
        {
            if(g.edge[i][j] == INF)
            {
                std::cout<<setw(4)<<"∞";
            }
            else
            {
                std::cout<<setw(4)<<g.edge[i][j];
            }
        }
        std::cout<<endl;
    }
}


template<typename T>  
void GraphClass<T>::CreateALGraph(T a[][MAXV], int n, int e)
{
    int i, j;
    ArcNode<T> *p;
    G = new ALGraph<T>();    
    G->n = n, G->e = e;
    for(i = 0; i < G->n; i++)
    {
        G->adjlist[i].firstarc = nullptr;     

    }
    for(i = 0; i < G->n; i++)        
    {
        for(j = G->n-1; j >= 0; j--)  
        {
            if(a[i][j] !=0 && a[i][j] != INF)
            {
                p = new ArcNode<T>();   
                p->adjvex = j;
                p->weight = a[i][j];
                p->nextarc = G->adjlist[i].firstarc;  
                G->adjlist[i].firstarc = p;
            }
        }
    }
}
template<typename T>  
void GraphClass<T>:: DispALGraph()
{
    int i;
    ArcNode<T> *p;
    for(i = 0; i < G->n; i++)
    {
        std::cout<<"["<<i<<"]";
        p = G->adjlist[i].firstarc;
        if(p != nullptr)
        {
            cout<<"-->";
        }
        while( p != nullptr)
        {
            cout<<" "<<p->adjvex<<"("<<p->weight<<")";
            p = p->nextarc;
        }
        std::cout<<endl;
    }
}


template<typename T>
void GraphClass<T>::DFS(GraphClass<T> &gobj, int v){
    int i;
    for(i = 0; i < gobj.G->n; i++){ 
        visited[i] = 0;
    }
    DFS1(gobj.G, v);
}
template<typename T>
void GraphClass<T>::DFS1(ALGraph<T> *G, int v){
    int w;
    ArcNode<T> *p;
    visited[v] = 1;  
    std::cout<<v<<" ";  
    p = G -> adjlist[v].firstarc;  
    while(p != nullptr){
        w = p->adjvex;  
        if(visited[w] == 0) DFS1(G, w); 
        p = p -> nextarc;
    }
}

template<typename T>
void GraphClass<T>::BFS(GraphClass<T> &gobj, int v){
    int i;
    for(i = 0; i < gobj.G->n; i++) visited[i] = 0;
    BFS1(gobj.G, v);
}
template<typename T>
void GraphClass<T>::BFS1(ALGraph<T> *G, int v){
    ArcNode<T> *p;
    int w;
    int qu[MAXV]; 
    int front = 0, rear = 0;
    std::cout<<v<<" ";
    visited[v] = 1;  
    rear = (rear+1) % MAXV;
    qu[rear] = v;  
    while(front != rear){  
        front = (front+1) % MAXV;
        w = qu[front];  
        p = G->adjlist[w].firstarc;  
        while(p != nullptr){
            if(visited[p->adjvex] == 0){ 
                std::cout<<p->adjvex<<" ";
                visited[p->adjvex] = 1;
                rear = (rear+1) % MAXV; 
                qu[rear] = p->adjvex;
            }
            p = p->nextarc;  
        }
    }

}
//5.最小生成树
//prim
//kruskal

//6.最短路径
//dijkstra
//floyd

//7.拓扑排序


void test1()
{
    //创建一个邻接矩阵(无向图)
    int a[MAXV][MAXV] = {0};
    int k = 1;
    for(int i = 0;i < MAXV; i++)
    {      
        for(int j = 0;j < k; j++)
        {
            if(i == j)
            {
                a[i][j] = 0;
            }
            else
            {
                a[i][j] = rand()%2;
                a[j][i] = a[i][j];
            }
        }
        k++;
    }

    //输出矩阵并且计算矩阵总共的边数
    int edges = 0;
    for(int i = 0;i<MAXV; i++)
    {
        for(int j = 0;j < MAXV; j++)
        {
            std::cout<<a[i][j]<<setw(4);
            if(a[i][j] != 0) edges++;
        }
        std::cout<<endl;
    }
    std::cout<<"该图的总边数是 : "<<edges/2<<std::endl;

    GraphClass<int> graph;
    graph.CreateMGraph(a, MAXV, edges/2);
    graph.DispMGraph();
    graph.CreateALGraph(a, MAXV, edges/2);
    graph.DispALGraph();
    graph.DFS(graph, 0);
    std::cout<<std::endl;
    graph.BFS(graph, 0);
}


int main()
{
    test1();
    return 0;
}