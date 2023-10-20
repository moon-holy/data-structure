#include <iostream>
#include <functional>
#include <queue>
#include <vector>

// 二叉树的链式存储（BST） //
template<typename T> 
struct BTreeNote
{
    T data;
    BTreeNote *lchild;
    BTreeNote *rchild;
    BTreeNote(T value) : data(value), lchild(nullptr), rchild(nullptr){}
};

template<class T> class BTreeNoteClass
{           
public:
    BTreeNote<T> *root;             
    BTreeNoteClass() : root(nullptr){};
    ~BTreeNoteClass(){ DestorBTree(root); };
    void createTree(std::vector<T>& v);
    void DispBTree();                       
    BTreeNote<T> *FindBTree(T elem);       
    int BTreeHight();          
    void preOder(BTreeNote<T> *root);
    void inOder(BTreeNote<T> *root);
    void postOder(BTreeNote<T> *root);
    void levelOder(BTreeNote<T> *root);
private:
    BTreeNote<T>* CreatBTree(BTreeNote<T>* root, int value); 
    void DispBTreeNode(BTreeNote<T> *t);
    void DestorBTree(BTreeNote<T> *root);           
    BTreeNote<T> *FindNote(BTreeNote<T> *root, T x);   
    int BTreeHightl(BTreeNote<T> *t);

};

template<typename T> 
void BTreeNoteClass<T>::DestorBTree(BTreeNote<T> *root)
{
    if(root != nullptr)
    {
        DestorBTree(root->lchild);
        DestorBTree(root->rchild);
        delete root;
    }
}

template<typename T>
void BTreeNoteClass<T>::createTree(std::vector<T>& v){
    for(int i = 0; i < v.size(); i++){
        root = CreatBTree(root, v[i]);
    }
}
template<typename T> 
BTreeNote<T>* BTreeNoteClass<T>::CreatBTree(BTreeNote<T>* root, int value)
{
    if(root == nullptr){
        return new BTreeNote<T>(value);
    }
    if(value < root -> data){
        root -> lchild = CreatBTree(root->lchild, value);
    }
    else{
        root -> rchild = CreatBTree(root->rchild, value);
    }
    return root;
}

template<typename T> 
BTreeNote<T> *BTreeNoteClass<T>::FindBTree(T elem)
{
    return FindNote(root, elem);
}
template<typename T> 
BTreeNote<T> *BTreeNoteClass<T>::FindNote(BTreeNote<T> *root, T x)
{
    if(root == nullptr || root->data == x) return root;
    if(x < root -> data){
        return FindNote(root -> lchild, x);
    }
    else{     
        return FindNote(root -> rchild, x);
    }
}

template<typename T> 
void BTreeNoteClass<T>::preOder(BTreeNote<T> *root)
{
    if(root != nullptr)
    {
        std::cout<<root->data<<"-->";
        preOder(root->lchild);
        preOder(root->rchild);
    }
}

template<typename T> 
void BTreeNoteClass<T>::inOder(BTreeNote<T> *root)
{
    if(root != nullptr)
    {
        preOder(root->lchild);
        std::cout<<root->data<<"-->";
        preOder(root->rchild);
    }
}

template<typename T> 
void BTreeNoteClass<T>::postOder(BTreeNote<T> *root)
{
    if(root != nullptr)
    {
        preOder(root->lchild);
        preOder(root->rchild);
        std::cout<<root->data<<"-->";
    }
}

template<typename T> 
void BTreeNoteClass<T>::levelOder(BTreeNote<T> *root)
{
    std::queue<BTreeNote<T>*> qu;
    std::vector<std::vector<T>> result;
    if(root != nullptr) qu.push(root);
    while(!qu.empty()){
        int size = qu.size();
        std::vector<T> voc;
        for(int i = 0; i < size; i++){
            BTreeNote<T> *cur = qu.front();
            qu.pop();
            voc.push_back(cur->data);
            if(cur->lchild != nullptr) qu.push(cur->lchild);
            if(cur->rchild != nullptr) qu.push(cur->rchild);
        }
        result.push_back(voc);
    }
    for(int i = 0; i < result.size(); i++){
        for(int j = 0; j < result[i].size(); j++){
            std::cout<<result[i][j]<<"-->";
        }
        std::cout<<std::endl;
    }
}

template<typename T> 
void BTreeNoteClass<T>::DispBTree(){
    DispBTreeNode(root);
}
template<typename T>
void BTreeNoteClass<T>::DispBTreeNode(BTreeNote<T> *t){
    if(t != nullptr){
        std::cout<<t->data;                 
        if(t->lchild != nullptr|| t->rchild != nullptr){
            std::cout<<"(";
            DispBTreeNode(t->lchild);  
            if(t->rchild != nullptr){
                std::cout<<",";
            }
            DispBTreeNode(t->rchild);  
            std::cout<<")";
        }
    }
}

template<typename T>
int BTreeNoteClass<T>::BTreeHight(){
    return BTreeHightl(root);
}
template<typename T>
int BTreeNoteClass<T>::BTreeHightl(BTreeNote<T> *t){
    int lchrild, rchrild;
    if(t == nullptr) return 0;  
    else{
        lchrild = BTreeHightl(t->lchild);  
        rchrild = BTreeHightl(t ->rchild);  
        return lchrild > rchrild ? (lchrild+1):(rchrild+1);
    }
}


int main(){
    std::vector<int> v({1, 4, -1, 3});
    BTreeNoteClass<int> *tree = new BTreeNoteClass<int>();
    tree->createTree(v);
    tree->DispBTree();
    std::cout<<std::endl;
    BTreeNote<int>* t = tree->FindBTree(3);
    std::cout<<"搜索到的数据是 : "<<t->data<<std::endl;
    tree->preOder(tree->root);
    std::cout<<std::endl;
    tree->inOder(tree->root);
    std::cout<<std::endl;
    tree->postOder(tree->root);
    std::cout<<std::endl;
    tree->levelOder(tree->root);
    std::cout<<"树的高度是 : "<<tree->BTreeHight()<<std::endl;
    return 0;
}