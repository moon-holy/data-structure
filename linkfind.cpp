#include <iostream>


//  线性表的查找   //
const int MaxSize  = 100;                   //  设置顺序表的大小
template<typename T> 
struct RecType                              //  顺序表记录的类型
{                                           
    T key;                                  //  存放关键字
    char data;                              //  存放其他信息
};

template<class T> 
class SqlsitFindClass
{   
    RecType<T> R[MaxSize];
    int length;         
public:
    void setK(T a[],int n);     //  设置表的关键字
    int SeqFind(T k);           //  顺序查找算法, 返回逻辑序号
    int BinFind(T k);           //  折半查找算法，返回逻辑序号(非递归)
    int BinFind1(T k);          //  折半查找算法，返回逻辑序号(递归)
    int BinFind11(int low,int high,T k);
    void disR();                //  输出表中的元素
};


template<class T> 
void SqlsitFindClass<T>::setK(T a[],int n)
{
    this->length = n;
    if(n > MaxSize)
    {
        std::cout<<"please input again"<<std::endl;
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            R[i].key = a[i];
        }
    }
}


template<class T> 
void SqlsitFindClass<T>::disR()
{
    for(int i = 0; i<this->length;i++)
    {
        std::cout<<this->R[i].key<<" ";
        if((i+1) % 10 == 0)
        {
            std::cout<<std::endl;
        }
    }
}

template<class T> 
int SqlsitFindClass<T>::SeqFind(T k)
{
    for(int i = 0; i < this->length; i++)
    {
        if(this->R[i].key==k)
        {
            return i;
        }
    }
    return -1;
}

template<class T> 
int SqlsitFindClass<T>::BinFind(T k)
{
    int low = 0, high = this -> length-1;
    int mid = (low + high)/2;
    while(low <= mid)
    {
        if(R[mid].key == k)
        {
            return mid+1;
        }
        else if(R[mid].key < k)
        {
            low = mid+1;
        }
        else if(R[mid].key > k)
        {
            high = mid-1;
        }
        mid = (low+high)/2;
    }
    return -1;
}

template<class T> 
int SqlsitFindClass<T>::BinFind1(T k)
{
    return BinFind11(0, this->length-1, k);
}

template<class T> 
int SqlsitFindClass<T>::BinFind11(int low, int high, T k)
{
    int mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(R[mid].key == k)
        {
            return mid;
        }
        else if(R[mid].key < k)
        {
            return BinFind11(mid+1, high, k);
        }
        else if(R[mid].key > k)
        {
            return BinFind11(low, high-1, k);
        }
    }
    return -1;
}


int main(){
    int arr[10] = {1, 2, 3, 5, 6, 33, 46, 61, 333, 351};
    SqlsitFindClass<int> *find = new SqlsitFindClass<int>();
    find->setK(arr, 10);
    find->disR();
    int elem1 = find->SeqFind(33);
    int elem2 = find->BinFind1(0);
    int elem3 = find->BinFind(333);
    std::cout<<"seq find : "<<elem1<<std::endl;
    std::cout<<"bin1 find : "<<elem2<<std::endl;
    std::cout<<"bind find : "<<elem3<<std::endl;
    return 0;
}
