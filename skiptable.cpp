#include <iostream>
#include <vector>
using namespace std;

// 跳表 //
template<typename T>
struct SkipNode {
    int key;  // 用来建索引
    int value;  
    vector<SkipNode*> next; // 指向下一个节点
    SkipNode(int k, T v, int level);  // 标志每个索引层数
};

template<typename T>
SkipNode<T>::SkipNode(int k, T v, int level) : key(k), value(v){
    for(int i = 0; i < level; i++){
        next.push_back(nullptr);
    }
}

template<class T>
class SkipList {
public:
    // 头节点
    SkipNode<T>* head;
    //列表最大层数
	int maxLevel;

	//整型的最小值和最大值
	const int minInt = numeric_limits<int>::min();
	const int maxInt = numeric_limits<int>::max();
public:
    SkipList(int maxLevel, T iniValue);
    ~SkipList();
    // 随机层数方法
    int randomLevel();
    // 操作方法
    SkipNode<T>* insert(int k, T v);
    SkipNode<T>* find(int k);
    SkipNode<T>* deleteNode(int k);
    void printNode();
private:
    // 尾节点
    SkipNode<T>* tail;
    // 当前列表或者node的最大层数
    int nodeLevel(vector<SkipNode<T>*> p);
};

// 初始化
template<typename T>
SkipList<T>::SkipList(int maxLevel, T iniValue) :maxLevel(maxLevel){
    //初始化头结点和尾节点为整型最小值和最大值
    head = new SkipNode<T>(minInt, iniValue, maxLevel);
    tail = new SkipNode<T>(maxInt, iniValue, maxLevel);

    // 所有层数的头节点都指向尾节点(头节点有maxLevel个层级)
    for(int i = 0; i < maxLevel; i++){
        head->next[i] = tail;
    }
}
template<typename T>
SkipList<T>::~SkipList(){
    delete head;
    delete tail;
}
// 随机层数
template<typename T>
int SkipList<T>::randomLevel(){
    int random_level = 1;
    int seed = time(NULL);
    static default_random_engine e(seed);
    // uniform_int_distributions:使用均匀分布，随机生成一个整数
    static uniform_int_distribution<int> u(0, 1);
    while(u(e) && random_level < maxLevel){
        random_level++;
    }
    return random_level;
}
// 当前节点的最大层数
template<typename T>
int SkipList<T>::nodeLevel(vector<SkipNode<T>*> next){
    int node_level = 0;
    // 尾节点，直接返回0层
    if(next[0]->key == maxInt){
        return node_level;
    }
    for(int i = 0; i < next.size(); i++){
        if(next[i] != nullptr && next[i]->key != maxInt){
            node_level++;
        }
        else{
            break;
        }
    }
    return node_level;
}
/*
插入：
1）首先用查找函数来判断该结点是否已经存在，如果存在，则更新该结点的值
2）获取新节点的随机层数
3）找到合适的插入位置
4）插入，并调整每层前后node的指针
*/
template<typename T> 
SkipNode<T>* SkipList<T>::insert(int k, T v){
    int x_level = randomLevel();
    SkipNode<T>* new_node = nullptr;
    SkipNode<T>* tmp = head;
    new_node = find(k);
    if(new_node){
        new_node->value = v;
        cout << "\nThis node " << k << " has already existed. And its value has been updated to " << v << endl;
        return head;
    }
    cout << "key: " << k << ", randomLevel: " << x_level << endl;
    new_node = new SkipNode<T>(k, v, x_level);
    for(int i = (x_level - 1); i > -1; i--){
        while(tmp->next[i] != nullptr && tmp->next[i]->key < k){
            tmp = tmp->next[i];
        }
        new_node->next[i] = tmp->next[i];
        tmp->next[i] = new_node;
    }
    return head;
}

/*查找：
由于列表有序，首先找到小于该结点的最近的结点，如果下一个结点等于目标结点，则返回该节点。
如果不是，则返回空*/
template<class T> SkipNode<T>* SkipList<T>::find(int k)
{
    SkipNode<T>* tmp = head;
    int current_level = nodeLevel(tmp->next);
    for(int i = (current_level - 1); i > -1; i--){
        while(tmp->next[i] != nullptr && tmp->next[i]->key < k){
            tmp = tmp->next[i];
        }
    }
    tmp = tmp->next[0];
    if(tmp->key == k){
        cout << "\nThis key " << k << " has been found\n";
		return tmp;
    }
    else{
        return nullptr;
    }
}

/*删除：
1) 用 find(x) 方法判断该结点是否存在. 如果不存在，则返回当前list, 并告知该结点不存在。
2) 找到小于该结点的最近的结点。
3) 更改该节点每层的前面的结点的指针。*/
template<class T> SkipNode<T>* SkipList<T>::deleteNode(int k){
    SkipNode<T>* node = find(k);
    if(!node){
        cout << "\n This deleting node" << k << "doesn't exist" << endl;
		return head;
    }
    else{
        SkipNode<T>* tmp = head;
        int x_level = node->next.size();
        cout << "\nThe deleting node " << k << "'s level is " << x_level << endl;
        for(int i = x_level - 1; i > -1; i--){
            while(tmp->next[i] != nullptr && tmp->next[i]->key < k){
                tmp = tmp -> next[i];
            }
            tmp -> next[i] = tmp -> next[i] -> next[i];
            cout << "This node " << k << " has been deleted from level " << i << endl;
        }
        return head;
    }
}

// 分层打印
template<class T> void SkipList<T>::printNode()
{

	for (int i = 0; i < maxLevel; i++)
	{
		SkipNode<T>* tmp = head;
		int lineLen = 1;

		if (tmp->next[i]->key != maxInt)
		{
			cout << "\n";
			cout << "This is level " << i << ":" << endl;
			cout << "{";

			while (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
			{
				cout << "(" << "Key: " << tmp->next[i]->key << ", ";
				cout << "Value: " << tmp->next[i]->value << ")";

				tmp = tmp->next[i];

				if (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
				{
					cout << ", ";
				}

				if (lineLen++ % 5 == 0) cout << "\n";
			}
			cout << "}" << "\n";
		}
	}
}

