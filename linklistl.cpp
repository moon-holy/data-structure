#include <iostream>

// 单链表（带头节点）//
template <typename T>
struct Node {
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};
template <typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList() : head(nullptr) {}
    void CreatListH(T a[], int size);
    void CreatListT(T a[], int size);
    void print();
    int getListLength();
    bool getElem(int i, T &e);
    int locateElem(T e);
    bool ListInsert(int i, T e);
    bool delElem(int i);
    void linkSort();
private:
    Node<T>* getMid(Node<T>* head);
    Node<T>* mergeSort(Node<T>* head);
    Node<T>* merge(Node<T>* list1, Node<T>* list2);
};

template<typename T>
void LinkedList<T>::CreatListH(T a[], int size){
    head = new Node<T>(0);
    for(int i = 0; i < size; i++){
        Node<T> *node = new Node<T>(a[i]);
        node -> next = head -> next;
        head ->next = node;
    }
}
template<typename T>
void LinkedList<T>::CreatListT(T a[], int size){
    head = new Node<T>(0);
    Node<T>* pre = head;
    for(int i = 0; i < size; i++){
        Node<T>* node = new Node<T>(a[i]);
        node->next = pre->next;
        pre -> next = node;
        pre = node;
    }
}

template<typename T>
void LinkedList<T>::print(){
    Node<T>* current = head -> next;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

template<typename T>
int LinkedList<T>::getListLength(){
    Node<T> *query = head -> next;
    int length = 0;
    while(query != nullptr){
        length++;
        query = query->next;
    }
    return length;
}

template<typename T>
bool LinkedList<T>::getElem(int i, T &e){
    Node<T> *query = head->next;
    int count = 0;
    while(count < i && query != nullptr){
        query = query->next;
        count++;
    }
    if(query != nullptr){
        e = query->data;
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
int LinkedList<T>::locateElem(T e){
    Node<T> *query = head;
    int i = 0;
    while(query != nullptr){
        query = query->next;
        i++;
        if(query -> data == e) return i;
    }
    return -1;
}

template<typename T>
bool LinkedList<T>::ListInsert(int i, T e){
    if(i < 0) return false;
    Node<T> *pre = head;
    Node<T> *cur = new Node<T>(e);
    while(pre != nullptr && i > 1){
        i--;
        pre = pre->next;
    }
    if(pre == nullptr){
        delete cur;
        return false;
    }
    else{
        cur -> next = pre -> next;
        pre -> next = cur;
        return true;
    }
    
}

template<typename T>
bool LinkedList<T>::delElem(int i){
    Node<T> *pre = head;
    Node<T> *cur = head->next;  
    while(i > 1 && pre != nullptr){
        i--;
        pre = pre->next;
        cur = cur->next;
    }
    if(pre == nullptr){
        return false;
    }
    else{
        pre -> next = cur -> next;
        delete cur;
        return true;
    }
}

template<typename T>
Node<T>* LinkedList<T>::getMid(Node<T>* head){
    if(head == nullptr) return head;
    Node<T>* fast = head;
    Node<T>* slow = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}
template<typename T>
Node<T>* LinkedList<T>::merge(Node<T>* list1, Node<T>* list2){
    if(list1 == nullptr) return list2;
    if(list2 == nullptr) return list1;
    Node<T>* mergeList = nullptr;
    if(list1->data <= list2->data){
        mergeList = list1;
        mergeList->next = merge(list1->next, list2);
    }
    else{
        mergeList = list2;
        mergeList->next = merge(list1, list2->next);
    }
    return mergeList;
}
template<typename T>
Node<T>* LinkedList<T>::mergeSort(Node<T>* head){
    if(head == nullptr || head->next == nullptr) return head;
    Node<T>* middle = getMid(head);
    Node<T>* nextToMid = middle->next;
    middle->next = nullptr;
    Node<T>* left = mergeSort(head);
    Node<T>* right = mergeSort(nextToMid);
    return merge(left, right);
}
template<typename T>
void LinkedList<T>::linkSort(){
    mergeSort(head);
}


int main() {
    LinkedList<int> myList;
    int arr[5] = {1, 2, 3, 5, 1};
    myList.CreatListT(arr, 5);
    std::cout<<"list length is : "<<myList.getListLength()<<std::endl;
    int a;
    std::cout<<"list 3 data is : "<<myList.getElem(8, a)<<std::endl;
    std::cout<<"list find elem 5 fist locate : "<<myList.locateElem(5)<<std::endl;
    myList.ListInsert(3, 999);
    myList.delElem(3);
    myList.linkSort();
    myList.print();

    return 0;
}
