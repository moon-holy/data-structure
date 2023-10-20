#include <iostream>
#include <vector>
#define MAXSIZE 100

// 栈的顺序存储 //
template<class T> class SqStackClass
{
	T *data;	
	int top;	
public:
	SqStackClass();
	~SqStackClass();
	bool SqStackisEmpty();	
	bool Push(T elem);		
	bool Pop(T &elem);			
	bool GetSqStackTop(T &elem);	
};

template<class T> 
SqStackClass<T>::SqStackClass(){
	data = new T[MAXSIZE];   
	top = -1;  
}

template<class T>
SqStackClass<T>::~SqStackClass(){
	delete [] data;
}

template<class T> 
bool SqStackClass<T>::SqStackisEmpty(){
	if(top == -1){
		return true;
	}else{
		return false;
	}
}

template<class T> 
bool SqStackClass<T>::Push(T elem){
	if(top == MAXSIZE-1) return false;
	data[++top]=elem;
	return true;
}

template<class T> 
bool SqStackClass<T>::Pop(T &elem){
	if(top == -1) return false;
	elem = data[top--];
	return true;
}
template<class T> 
bool SqStackClass<T>::GetSqStackTop(T &elem){
	if(top == -1) return false;
	elem = data[top];
	return true;
}

int main(){
    std::vector<int> v(10, 1);
    SqStackClass<int> *sq = new SqStackClass<int>();
    if(sq->SqStackisEmpty()){
        std::cout<<"stack is empty"<<std::endl;
    }
    for(auto &i : v){
        sq->Push(i);
    }
    int elem;
    if(sq->GetSqStackTop(elem)){
        std::cout<<"stack top is : "<<elem<<std::endl;
    }
    if(sq->Pop(elem)){
        std::cout<<"output data is : "<<elem<<std::endl;
    }
    if(sq->GetSqStackTop(elem)){
        std::cout<<"stack top is : "<<elem<<std::endl;
    }
}