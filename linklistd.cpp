#include <iostream>

// 双链表 //
template <typename T>
struct DLinkList{
    T data;
    DLinkList<T> *pre;
    DLinkList<T> *next;
};
template <class T>
class DLinkListClass{
    DLinkList<T> *head;  
public:
    DLinkListClass<T>();
    ~DLinkListClass<T>();
    void CreateListF(T a[],int n);   
    void CreateListR(T a[],int n);   
    void DispList();   
    int ListLength();  
    bool GetElem(int i,T &e);  
    int LocateElem(T e); 
    bool ListInsert(int i,T e); 
    bool ListDelete(int i);  
};
template<typename T>
void DLinkListClass<T>::CreateListF(T a[],int n){
    DLinkList<T> *p;
    int i;   //p用于指向插入元素
    head->next=NULL;
    for(i=0;i<n;i++){
        p=new DLinkList<T>();
        p->data=a[i];
        p->next=head->next;
        if(head->next!=NULL)
            head->next->pre=p;
        head->next = p;
        p->pre=head;   
    }
}
template<typename T>
void DLinkListClass<T>::CreateListR(T a[],int n){
    DLinkList<T> *p,*q=head;
    int i;  //p用于指向要插入元素,q指向尾元素
    for(i=0;i<n;i++){
        p=new DLinkList<T>();
        q->next=p;
        p->pre=q;
        q=p;
    }
    q->next=NULL;  //最后将尾节点置空
}
template<typename T>
void DLinkListClass<T>::DispList(){
    
}
template<typename T>
int DLinkListClass<T>::ListLength(){
    
}
template<typename T>
bool DLinkListClass<T>::GetElem(int i,T &e){
    
}
template<typename T>
int DLinkListClass<T>::LocateElem(T e){
    
}
template<typename T>
bool DLinkListClass<T>::ListInsert(int i,T e){
    // 双链表的插入和头插法一样
}
template<typename T>
bool DLinkListClass<T>::ListDelete(int i){
    
}
