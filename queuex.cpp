#include<iostream>
using namespace std;
#define MAXSIZE 100




//  队列的顺序存储（非循环) / 队列的大小尾100 //
template <class T> class SqQueueClass
{
	T *data;   
	int front, rear;  
public: 
	SqQueueClass();                 // 创建一个顺序队列
	~SqQueueClass();                // 删除一个顺序队列
	bool QueueisEmpty();            // 判断队列是否为空
	bool enQueue(T elem);           // 入队
	T deQueue();                    // 出队
    T getFrontData();               // 获取队头元素
    T getTailData();                // 获取队尾元素
};

template<typename T>
SqQueueClass<T>::SqQueueClass(){
	data = new T[MAXSIZE];   
	front = rear = -1;      
}

template<typename T>
SqQueueClass<T>::~SqQueueClass(){
	delete [] data;

}

template<typename T>
bool SqQueueClass<T>::QueueisEmpty(){
	return rear == front;      
}

template<typename T>
bool SqQueueClass<T>::enQueue(T elem){
	if(rear == MAXSIZE-1) return false;  
	data[++rear]=elem;   
	return true;
}

template<typename T>
T SqQueueClass<T>::deQueue(){
	if(front == rear){
        return 0;
    }  
	return data[++front];   
}

template<typename T>
T SqQueueClass<T>::getFrontData(){
    if(front == -1) return 0;
    return data[front];
}

template<typename T>
T SqQueueClass<T>::getTailData(){
    return data[rear];
}



void test(){
    SqQueueClass<int> que;
    std::cout<<"队列是否为空 : "<<que.QueueisEmpty()<<std::endl;
    que.enQueue(10);
    que.enQueue(11);
    std::cout<<"获取对头元素 : "<<que.getFrontData()<<std::endl;
    std::cout<<"获取对尾元素 : "<<que.getTailData()<<std::endl;
    std::cout<<"队列是否为空 : "<<que.QueueisEmpty()<<std::endl;
    int elem = que.deQueue();
    std::cout<<"出队元素是 : "<<elem<<std::endl;


}

int main(int argc, char* argv[]){
    test();
    return 0;
}