#include <iostream>
#include <vector>

// 栈的链式存储 //
/* 
# 入栈和出栈只能在链栈的头节点之后进行
# 带头节点的链表作为其数据结构
*/

template<typename T> 
struct LinkStack
{
	T data;				//  数据域
	LinkStack *next;	//  指针域
};

template<class T> 
class LinkStackClass
{
	LinkStack<T> *head;	        //  链栈头节点指针
public:
	LinkStackClass();
	~LinkStackClass();
	bool LinkStackisEmpty();	    //  栈空判断
	void Push(T elem);			    //  进栈方法
	bool Pop(T &elem);			    //  出栈算法
	bool GetLinkStackTop(T &elem);	//  取栈顶元素
};

template<typename T>
LinkStackClass<T>::LinkStackClass(){
	head = new LinkStack<T>();
	head->next = nullptr;
}

template<typename T>
LinkStackClass<T>::~LinkStackClass(){
	LinkStack<T> *pre = head, *p = pre->next;
	while(p != nullptr){
		delete pre;   
		pre = p;
		p = p->next;
	}
	delete pre;  
}

template<typename T>
bool LinkStackClass<T>::LinkStackisEmpty(){
	if(head->next == nullptr){
		return true;
	}
    else{
		return false;
	}
}

template<typename T>
void LinkStackClass<T>::Push(T elem){
	LinkStack<T> *node = new LinkStack<T>();
    node->data = elem;
    node -> next = head -> next;
    head -> next = node;
}

template<typename T>
bool LinkStackClass<T>::Pop(T &elem){
    if(head -> next == nullptr) return false;
	LinkStack<T> *node = head -> next;
    elem = node -> data;
    head -> next = node -> next;
    delete node;
}

template<typename T>
bool LinkStackClass<T>::GetLinkStackTop(T &elem){
	if(head->next == nullptr) return false;
	elem = head -> next -> data;
    return true;

}

int main(){
    std::vector<int> v({1, 3, 4, 5, 3});
    LinkStackClass<int> *link = new LinkStackClass<int>();
    if(link->LinkStackisEmpty()){
        std::cout<<"link is empty"<<std::endl;
    }
    for(auto &i : v){
        link->Push(i);
    }
    int elem;
    if(link->GetLinkStackTop(elem)){
        std::cout<<"top value is : "<<elem<<std::endl;
    }
    if(link->Pop(elem)){
        link->Pop(elem);
        std::cout<<"pop 2 data is : "<<elem<<std::endl;
    }
}