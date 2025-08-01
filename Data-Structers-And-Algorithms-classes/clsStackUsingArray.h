#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
using namespace std;

// Stack using Array implemented with templates

template <typename T>
class clsStackUsingArray
{
private:
    T* arr;
    int top;
    int capacity;

    // Resizes the array when full
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i <= top; ++i)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    StackUsingArray(int size = 100) {
        capacity = size;
        arr = new T[capacity];
        top = -1;
    }

    ~StackUsingArray() {
        delete[] arr;
    }

    // Pushes an element onto the stack
    void push(T value) {
        if (isFull()) resize(); // Auto resize if full
        arr[++top] = value;
    }

    // Removes the top element
    void pop() {
        if (isEmpty()) throw underflow_error("Stack underflow");
        --top;
    }

    // Returns the top element without removing it
    T peek() {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return arr[top];
    }

    // Returns the number of elements in the stack
    int size() {
        return top + 1;
    }

    // Clears the stack
    void clear() {
        top = -1;
    }

    // Checks if the stack is empty
    bool isEmpty() {
        return top == -1;
    }

    // Checks if the stack is full
    bool isFull() {
        return top == capacity - 1;
    }

    // Displays stack contents from top to bottom
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; --i)
            cout << arr[i] << " ";
        cout << endl;
    }

    // Displays stack contents from bottom to top
    void printReverse() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (bottom to top): ";
        for (int i = 0; i <= top; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }

    // Checks if a value exists in the stack
    bool contains(T value) {
        for (int i = 0; i <= top; ++i)
            if (arr[i] == value) return true;
        return false;
    }

    // Reverses the stack elements
    void reverse() {
        for (int i = 0, j = top; i < j; ++i, --j)
            swap(arr[i], arr[j]);
    }

    // Converts the stack to a vector
    vector<T> toVector() {
        vector<T> vec;
        for (int i = 0; i <= top; ++i)
            vec.push_back(arr[i]);
        return vec;
    }

    // Returns the bottom element (first pushed)
    T bottom() {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return arr[0];
    }

    // Access elements like an array (read-only recommended)
    T& operator[](int index) {
        if (index < 0 || index > top) throw out_of_range("Index out of range");
        return arr[index];
    }

    // Clone the current stack to a new stack
    StackUsingArray<T> clone() {
        StackUsingArray<T> copy(capacity);
        for (int i = 0; i <= top; ++i)
            copy.push(arr[i]);
        return copy;
    }

    // Compare with another stack
    bool equals(const StackUsingArray<T>& other) {
        if (this->size() != other.size()) return false;
        for (int i = 0; i <= top; ++i)
            if (arr[i] != other.arr[i]) return false;
        return true;
    }

    // Save stack to file
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) throw runtime_error("Failed to open file");
        for (int i = 0; i <= top; ++i)
            file << arr[i] << endl;
        file.close();
    }

    // Load stack from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) throw runtime_error("Failed to open file");
        clear();
        T value;
        while (file >> value)
            push(value);
        file.close();
    }
};

