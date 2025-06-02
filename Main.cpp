#include <iostream>
#include "BinaryHeap.h"
#include "Queue.h"
#include <chrono>
#include <algorithm>
#include <ctime>

using namespace std;

long calculateAverageTime(int Q, long array[]) 
{
    int count = Q * 0.8;
    long sum = 0;

    sort(array, array + Q);

    for (int i = 0; i < count; i++) 
    {
        sum += array[i];
    }

    return sum / count;
}

template <typename T>
T generateRandomElement();

template<>
int generateRandomElement<int>()
{
    return rand() % 100;
}

template<>
string generateRandomElement<string>()
{
    return to_string(rand() % 100);
}

template <typename T>
void performOperations(Queue<T, T>& queue, int Q, long enqueueResults[], 
long dequeueResults[], long peekResults[])
{
    for (int i = 0; i < Q; i++)
    {
        T elem = generateRandomElement<T>();

        auto start = chrono::high_resolution_clock::now();
        queue.enqueue(elem, elem);
        auto end = chrono::high_resolution_clock::now();
        enqueueResults[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        queue.peek();
        end = chrono::high_resolution_clock::now();
        peekResults[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        queue.dequeue();
        end = chrono::high_resolution_clock::now();
        dequeueResults[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
}

template <typename T>
void testQueueType(int Q, int n, const string& typeName)
{
    long peekResults[Q];
    long enqueueResults[Q];
    long dequeueResults[Q];

    Queue<T, T> queue;

    for (int i = 0; i < n - 1; i++)
    {
        queue.enqueue(generateRandomElement<T>(), generateRandomElement<T>());
    }

    performOperations(queue, Q, enqueueResults, dequeueResults, peekResults);

    long averageEnqueue = calculateAverageTime(Q, enqueueResults);
    long averageDequeue = calculateAverageTime(Q, dequeueResults);
    long averagePeek = calculateAverageTime(Q, peekResults);

    cout << "\tFor " << typeName << ": enqueue - " << averageEnqueue 
    << ", dequeue - " << averageDequeue 
    << ", peek - " << averagePeek << endl; 

}

void averageTimeCounter(int Q, int n)
{
    cout << "Average time for N = " << n << endl;
    
    testQueueType<int>(Q, n, "int");
    testQueueType<string>(Q, n, "str");
}

int main() 
{
    int Q = 10;
    int nStart = 100;
    int nEnd = 200;
    int nDelta = 10;

    srand(time(0));

    for (int n = nStart; n <= nEnd; n += nDelta)
    {
        averageTimeCounter(Q, n);
    }
}