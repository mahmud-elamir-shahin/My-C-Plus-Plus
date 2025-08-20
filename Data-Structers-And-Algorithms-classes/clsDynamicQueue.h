#pragma once

#include <iostream>
using namespace std;
template <typename T>
class clsDynamicQueue
{
    private:
        T* arr;
        int capacity;
        int front;
        int rear;
        int count;

        void resize() {
            int newCapacity = capacity * 2;
            T* newArr = new T[newCapacity];

            for (int i = 0; i < count; i++) {
                newArr[i] = arr[(front + i) % capacity];
            }

            delete[] arr;
            arr = newArr;
            front = 0;
            rear = count;
            capacity = newCapacity;
        }

    public:
        DynamicQueue(int initSize = 4) {
            arr = new T[initSize];
            capacity = initSize;
            front = 0;
            rear = 0;
            count = 0;
        }

        ~DynamicQueue() {
            delete[] arr;
        }

        void enqueue(T val) {
            if (count == capacity)
                resize();

            arr[rear] = val;
            rear = (rear + 1) % capacity;
            count++;
        }

        void dequeue() {
            if (isEmpty()) {
                cout << "Queue is empty.\n";
                return;
            }
            front = (front + 1) % capacity;
            count--;
        }

        T peek() {
            if (isEmpty()) {
                throw runtime_error("Queue is empty.");
            }
            return arr[front];
        }

        bool isEmpty() {
            return count == 0;
        }

        int size() {
            return count;
        }

        void print() {
            cout << "Queue (front to rear): ";
            for (int i = 0; i < count; i++) {
                cout << arr[(front + i) % capacity] << " ";
            }
            cout << "\n";
        }
    };



