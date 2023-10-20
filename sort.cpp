#include <iostream>
#include <vector>
#include <time.h>
using namespace std;


template<class T> 
class MSortClass
{
    vector<T> v_;
    int legth_;
public:
    void SetKey(T a[],  int n);   
    void DisR();
    void InserSort();                         //  插入排序
    void BubbleSort();                        //  冒泡排序
    void QuickSort();                         //  快速排序     
    void SelectSort();                        //  选择排序
    void HeapSort();                          //  堆排序
private:
    void sift(int root, int n);
    void QuickSortParitition(int low, int high);     
}; 

template<typename T> 
void MSortClass<T>::SetKey(T a[], int n)
{
    for(int i=0; i < n; i++)
    {
        v_.push_back(a[i]);
    }
    legth_ = v_.size();
}

template<typename T> 
void MSortClass<T>::DisR()
{
    for(int i = 0; i < legth_; i++)
    {
        std::cout<<v_[i]<<" ";
        if((i+1) % 10 == 0)
        {
            std::cout<<std::endl;
        }
    }
}

template<typename T> 
void MSortClass<T>::InserSort()
{
    for(int i = 1; i < legth_; i++)
    {
        int key = v_[i];
        int j = i - 1;
        while(j >= 0 && v_[j] > key){
            v_[j+1] = v_[j];
            j--;
        }
        v_[j+1] = key;
    } 
}

template<typename T> 
void MSortClass<T>::BubbleSort()
{
    for(int i=0; i < legth_-1; i++)
    {
        for(int j = legth_-1; j > i ;j--)
        {
            if(v_[j] < v_[j-1])
            {
                swap(v_[j], v_[j-1]);
            }
        }
    }
}

template<typename T>
void MSortClass<T>::QuickSort(){
    QuickSortParitition(0, v_.size()-1);
}

template<typename T> 
void MSortClass<T>::QuickSortParitition(int low, int high)
{
    if(low >= high) return;
    int left = low;
    int right = high;
    int key = v_[left];
    while(left < right){
        while(left < right && v_[right] >= key) right--;
        v_[left] = v_[right];
        while(left < right && v_[left] <= key) left++;
        v_[right] = v_[left];
    }
    v_[left] = key;
    QuickSortParitition(low, left);
    QuickSortParitition(left+1, high);
}


template<typename T> 
void MSortClass<T>::SelectSort()
{
    for(int i = 0; i < v_.size(); i++){
        int temp = v_[i];
        int k = i;
        for(int j = i; j < v_.size(); j++){
            if(temp > v_[j]){
                temp = v_[j];
                k = j;
            }
        }
        v_[k] = v_[i];
        v_[i] = temp;
    }
}

template<typename T> 
void MSortClass<T>::sift(int root, int n)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    if(n > left && v_[left] < v_[largest]){
        largest = left;
    }
    if(n > right && v_[right] < v_[largest]){
        largest = right;
    }
    if(largest != root){
        swap(v_[root], v_[largest]);
        sift(largest, n);
    }
}

template<typename T> 
void MSortClass<T>::HeapSort()
{
    int n = v_.size();
    for(int i = n/2-1; i >= 0; i--){
        sift(i, n);
    }
    for(int i = n - 1; i > 0; i--){
        swap(v_[0], v_[i]);  // 小根堆排序后是从大到小（减小额外的开销）
        sift(0, i);
    }
}




void test()
{
    int arr[10] = {1, 3, 5, 0, 12, 1, 2, 15, 39, 7};
    MSortClass<int> *sort = new MSortClass<int>();
    sort->SetKey(arr, 10);
    sort->DisR();
    // sort->InserSort();
    // sort->BubbleSort();
    // sort->QuickSort();
    // sort->SelectSort();
    sort->HeapSort();
    sort->DisR();
}
int main()
{
    test();
    return 0;
}