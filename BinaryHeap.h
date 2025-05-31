#include <iostream>
#include <vector>

using namespace std;

template <typename D>

class BinaryHeap 
{
public:

    BinaryHeap() = default;
    ~BinaryHeap() = default;

    void insert(D data);
    D extractMin();
    D getMin();
    int getSize();

private:
    vector<D> array;

    void siftDown(int index); 
    void siftUp(int index);
    int getParentIndex(int childIndex);
    int getLeftChildIndex(int parentIndex);
    int getRightChildIndex(int parentIndex);
};

template <typename D>
void BinaryHeap<D>::insert(D data)
{
    array.push_back(data);
    siftUp(getSize() - 1);
}

template <typename D>
D BinaryHeap<D>::extractMin() 
{
    if (array.empty()) 
    {
        throw out_of_range("Error: heap is empty!");
    }

    D min = array[0];
    array[0] = array[getSize() - 1];
    array.pop_back();
    siftDown(0);
    
    return min;
}

template <typename D>
D BinaryHeap<D>::getMin() 
{
    if (array.empty()) 
    {
        throw out_of_range("Error: heap is empty!");    
    }

    return array[0];
}

template <typename D>
int BinaryHeap<D>::getSize() 
{
    return array.size();
}

template <typename D>
void BinaryHeap<D>::siftDown(int index) 
{
    while (getLeftChildIndex(index) < getSize()) 
    {
        int minChildIndex = getLeftChildIndex(index);

        if (minChildIndex + 1 < getSize() && array[minChildIndex] > array[minChildIndex + 1]) 
        {
            minChildIndex++;
        }

        if (array[index] > array[minChildIndex]) 
        {
            swap(array[index], array[minChildIndex]);
            index = minChildIndex;
        }
        else
        {
            break;
        }
    }
}

template <typename D>
void BinaryHeap<D>::siftUp(int index) 
{
    
    while (array[index] < array[getParentIndex(index)])
    {
        swap(array[index], array[getParentIndex(index)]);
        index = getParentIndex(index);
    }
}

template <typename D>
int BinaryHeap<D>::getParentIndex(int childIndex) 
{
    return (childIndex - 1) / 2;
}

template <typename D>
int BinaryHeap<D>::getLeftChildIndex(int parentIndex) 
{
    return 2 * parentIndex + 1;

}

template <typename D>
int BinaryHeap<D>::getRightChildIndex(int parentIndex) 
{
    return 2 * parentIndex + 2;
}