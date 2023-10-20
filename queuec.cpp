#include <iostream>
#include <vector>

#define MAXSIZE 100

// 队列的顺序存储(循环) //
template <class T> 
class CSqQueueClass
{
	T *data;                //  队列中的元素
	int front,rear;         //  队列中的队头指针和队尾指针
public:
	CSqQueueClass();
	~CSqQueueClass();
	bool QueueisEmpty();    //  判断队是否为空
	bool enQueue(T elem);   //  入队
	bool deQueue(T &elem);  //  出队
};

template<typename T>
CSqQueueClass<T>::CSqQueueClass(){
	data = new T[MAXSIZE];   
	front = rear = 0;        
}

template<typename T>
CSqQueueClass<T>::~CSqQueueClass(){
	delete [] data;
}

template<typename T>
bool CSqQueueClass<T>::QueueisEmpty(){
	return front == rear;
}

template<typename T>
bool CSqQueueClass<T>::enQueue(T elem){
	// 先判断队是否满，不满则data[front] = elem，然后front前进1
	if((rear+1) % MAXSIZE == front) return false;
	data[front] = elem;
	front = (front+1) % MAXSIZE;
    return true;
}
template<typename T>
bool CSqQueueClass<T>::deQueue(T &elem){
	// 先判断队是否空，不空则elem = data[rear], 然后rear前进1
	if(rear == front) return false;
	elem = data[rear];
	rear=(rear+1) % MAXSIZE;
    return true;
}


int main(){
    std::vector<int> arr{1, 2, 3, 4, 5, 6, 1};
    CSqQueueClass<int> *cq = new CSqQueueClass<int>();
    if(cq->QueueisEmpty()){
        std::cout<<"queue is empty"<<std::endl;
    }
    for(auto &i : arr){
        cq->enQueue(i);
    }
    if(!cq->QueueisEmpty()){
        std::cout<<"queue is not empty"<<std::endl;
    }
    int elem;
    if(cq->deQueue(elem)){
        std::cout<<"output elem is : "<<elem<<std::endl;
    }
    return 0;
}