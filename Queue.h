#pragma once

#include <iostream>
#include "BinaryHeap.h"

using namespace std;

/*
    Неубывающая очередь с приоритетами (приоритет и данные – обобщенные типы)
    Операции: Enqueue, Dequeue, Peek
    Реализация: бинарная пирамида
*/

template<typename D, typename P>
class Queue
{
public:    

    // добавляет элемент в конец очереди
    void enqueue(D data, P priority);

    // возвращает и удаляет элемент из начала очереди
    D dequeue();

    // возвращает элемент из начала очереди без удаления
    D peek();

    // выводит все элементы очереди
    void print();

    // cтандартная операция – проверка на пустоту очереди
    bool isEmpty();

private:        
    struct Node
    {
        P priority;
        D data;

        Node(P _priority, D _data)
        {
            this -> priority = _priority;
            this -> data = _data;
        } 

        // переопределение операторов для сравнения

        bool operator > (const Node & otherNode) const
        {
            return this->priority > otherNode.priority;
        }

        bool operator >= (const Node & otherNode) const
        {
            return this->priority >= otherNode.priority;
        }

        bool operator < (const Node & otherNode) const
        {
            return this->priority < otherNode.priority;
        }

        bool operator <= (const Node & otherNode) const
        {
            return this->priority <= otherNode.priority;
        }
    };
        
    BinaryHeap<Node> heap;

};

template<typename D, typename P>
void Queue<D, P>::enqueue(D data, P priority) 
{
    Queue<D, P>::Node node(priority, data);
    heap.insert(node);
}

template<typename D, typename P>
D Queue<D, P>::dequeue()
{
    if (heap.isEmpty()) 
    {
        throw std::out_of_range("Queue is empty!");
    }

    return heap.extractMin().data;
}

template<typename D, typename P>
D Queue<D, P>::peek()
{
    if (heap.isEmpty()) 
    {
        throw std::out_of_range("Queue is empty!");
    }

    return heap.getMin().data;
}

template<typename D, typename P>
void Queue<D, P>::print()
{
    BinaryHeap<Node> tempHeap = heap;

    while (! tempHeap.isEmpty())
    {
        Node node = tempHeap.extractMin();
        std::cout << "priority: " << node.priority << ", data: " << node.data << std::endl;
    }
}

template<typename D, typename P>
bool Queue<D, P>::isEmpty()
{
    return heap.getSize() == 0;
}