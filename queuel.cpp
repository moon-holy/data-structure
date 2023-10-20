#include <iostream>
#include <vector>

// 队列的链式存储(非循环) //

template <typename T> 
struct LinkQueueNode
{
	T data;
	LinkQueueNode *next;
};

//  创建一个指向头和尾的节点
template <typename T> 
struct LinkQueue
{
	LinkQueueNode<T> *front;  //    指向队首
	LinkQueueNode<T> *rear;   //    指向队尾
};

template <class T> 
class LinkQueueClass
{
	LinkQueue<T> *Q;		
public:
	LinkQueueClass();
	~LinkQueueClass();
	bool LinkQueueisEmpty();
	void enLinkQueue(T elem);
	bool deLinkQueue(T &elem);
};


template<typename T>
LinkQueueClass<T>::LinkQueueClass(){
	Q = new LinkQueue<T>();  
	Q->front = nullptr;
	Q->rear = nullptr;
}

template<typename T>
LinkQueueClass<T>::~LinkQueueClass(){
	LinkQueueNode<T> *pre = Q->front, *p;
	if(pre!=NULL){
		if(pre == Q->rear) delete pre;  
		else{
			p=pre->next;
			while(p!=NULL){  
				delete pre;
				pre=p;
				p=p->next;  
			}
			delete pre;
		}
		delete Q;
	}
}

template<typename T>
bool LinkQueueClass<T>::LinkQueueisEmpty(){
	return Q -> rear == nullptr;
}

template<typename T>
void LinkQueueClass<T>::enLinkQueue(T elem){
	LinkQueueNode<T> *p = new LinkQueueNode<T>();
	p->data = elem;
	p->next = nullptr;
	if(Q->rear == nullptr){   
		Q->front = Q->rear = p;
	}
    else{    
		Q->rear->next = p;
		Q->rear = p;
	}
}

template<typename T>
bool LinkQueueClass<T>::deLinkQueue(T &elem){
	LinkQueueNode<T> *p;
	if(Q->rear == nullptr) return false;
	p = Q->front;
	if(Q->rear == Q->front){   
		Q->rear = Q->front = nullptr;
	}else{
		Q->front=Q->front->next;
	}
	elem = p->data;
	delete p;
	return true;
}


int main(){
    std::vector<int> a{1, 4, 5, 3, 1};
    LinkQueueClass<int> *link = new LinkQueueClass<int>();
    if(link->LinkQueueisEmpty()){
        std::cout<<"linkqueue is empty"<<std::endl;
    }
    for(auto &i : a){
        link->enLinkQueue(i);
    }
    if(!link->LinkQueueisEmpty()){
        std::cout<<"linkqueue is not empty"<<std::endl;
    }
    int elem;
    if(link->deLinkQueue(elem)){
        std::cout<<"dequeue elem is : "<<elem<<std::endl;
    }
}