#include<iostream>
using namespace std;

// 顺序表 //
template <class T> class SqListClass
{
    T *data;                            //顺序表的元素
    int length;                         //顺序表的长度
public:
    SqListClass();                      //构造函数
    ~SqListClass();                     //析构函数
    void CreateSqList(T arr[],int n);   //利用数组创建顺序表
    void DisSqList();                   //输出顺序表
    int SqListLength();                 //求顺序表的长度
    int LocateSqList(T elem);           //按值查找元素序号(序号从1开始)
    bool InsertSqList(int i,T e);       //按位置插入元素
    bool DeleteSqList(int i);           //按位置删除元素
};


template<class T> void SqListClass<T>::CreateSqList(T arr[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        data[i]=arr[i];
    }
    length = i;
}

template<class T> SqListClass<T>::SqListClass()
{
    data = new T[length];
    length = 0;
}
template<class T> SqListClass<T>::~SqListClass()
{
    delete [] data;
}

template<class T> void SqListClass<T>::DisSqList()
{
    if(length>0)
    {
        for(int i=0;i<length;i++)
        {
            cout<<data[i]<<" ";
        }
        cout<<endl;
    }
}

template<class T> int SqListClass<T>::SqListLength()
{
    return length;
}

template<class T> int SqListClass<T>::LocateSqList(T elem)
{
    for(int i=0;i<length;i++)
    {
        if(data[i]==elem)
        {
            return i+1;
        }
    }
    return -1;
}

template<class T> bool SqListClass<T>::InsertSqList(int i,T elem)
{
    if(i<1||i>length+1) return false;
    for(int j=length;j>=i;j--)
    {
        data[j]=data[j-1];
    }
    data[i-1] = elem;
    length++;
    return true;
}

template<class T> bool SqListClass<T>::DeleteSqList(int i)
{
    if(i<0||i>length+1) return false;
    for(int j=i-1;j<length-1;j++)
    {
        data[j]=data[j+1];
    }
    return true;
}


void test1()
{
    SqListClass<int> SqList;
    int arr[10]={15,61,71,116,171,72,426,726,252,72};
    SqList.CreateSqList(arr,10);
    SqList.DisSqList();
    cout<<SqList.SqListLength()<<endl;
    cout<<SqList.LocateSqList(71)<<endl;
    SqList.InsertSqList(7,1767);
    SqList.DisSqList();   
}

int main()
{
    test1();
    return 0;
}