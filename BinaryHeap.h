#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <typename D>

class BinaryHeap 
{
public:

    BinaryHeap() = default;
    ~BinaryHeap() = default;

    // вставка элемента в конец
    void insert(D data);

    // возвращает и удаляет минимальный элемент
    D extractMin();

    // возвращает минимальный элемент без удаления
    D getMin();

    // возвращает размер кучи
    int getSize();

    // проверяет кучу на пустоту
    bool isEmpty();

private:
    vector<D> array;

    // опускает элемент, пока тот не встанет на свое место
    void siftDown(int index); 

    // поднимает элемент, пока тот не встанет на свое место
    void siftUp(int index);

    // возвращает индекс родителя 
    int getParentIndex(int childIndex);
    
    // возвращает индекс левого ребёнка
    int getLeftChildIndex(int parentIndex);

    // возвращает индекс правого ребёнка
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
bool BinaryHeap<D>::isEmpty()
{
    return array.size() == 0;
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