#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
using namespace std;

// Queue using Array with templates

template <typename T>
class clsQueueUsingArray
{
private:
    vector<T> data;
    int frontIndex;
    int rearIndex;
    int count;

public:
    QueueUsingArray() : frontIndex(0), rearIndex(-1), count(0) {}

    // Add element to rear of queue
    void enqueue(T value) {
        data.push_back(value);
        rearIndex++;
        count++;
    }

    // Remove element from front of queue
    void dequeue() {
        if (isEmpty()) throw underflow_error("Queue underflow");
        frontIndex++;
        count--;
    }

    // Get front element
    T front() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return data[frontIndex];
    }

    // Get rear element
    T rear() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return data[rearIndex];
    }

    // Check if queue is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Return number of elements in queue
    int size() const {
        return count;
    }

    // Clear all elements from queue
    void clear() {
        data.clear();
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Display queue contents
    void display() const {
        cout << "Queue (front to rear): ";
        for (int i = frontIndex; i <= rearIndex; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Check if queue contains a specific value
    bool contains(T value) const {
        for (int i = frontIndex; i <= rearIndex; ++i) {
            if (data[i] == value) return true;
        }
        return false;
    }

    // Convert queue to vector
    vector<T> toVector() const {
        vector<T> vec;
        for (int i = frontIndex; i <= rearIndex; ++i) {
            vec.push_back(data[i]);
        }
        return vec;
    }

    // Reverse the queue
    void reverse() {
        vector<T> vec = toVector();
        clear();
        for (int i = vec.size() - 1; i >= 0; --i) {
            enqueue(vec[i]);
        }
    }

    // Clone this queue into another
    QueueUsingArray<T> clone() const {
        QueueUsingArray<T> copy;
        for (int i = frontIndex; i <= rearIndex; ++i) {
            copy.enqueue(data[i]);
        }
        return copy;
    }

    // Get item at specific index
    T getAt(int index) const {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        return data[frontIndex + index];
    }

    // Remove item at specific index
    void removeAt(int index) {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        data.erase(data.begin() + frontIndex + index);
        rearIndex--;
        count--;
    }

    // Update item at specific index
    void updateAt(int index, T newValue) {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        data[frontIndex + index] = newValue;
    }

    // Sort the queue (ascending or descending)
    void sort(bool ascending = true) {
        vector<T> vec = toVector();
        clear();
        if (ascending)
            std::sort(vec.begin(), vec.end());
        else
            std::sort(vec.rbegin(), vec.rend());
        for (const T& val : vec) enqueue(val);
    }

    // Merge another queue into this one
    void merge(const QueueUsingArray<T>& other) {
        vector<T> otherVec = other.toVector();
        for (const T& val : otherVec) enqueue(val);
    }

    // Save queue contents to a file
    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) throw runtime_error("Failed to open file");
        for (int i = frontIndex; i <= rearIndex; ++i) {
            out << data[i] << endl;
        }
        out.close();
    }

    // Load queue contents from a file
    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) throw runtime_error("Failed to open file");
        clear();
        T value;
        while (in >> value) {
            enqueue(value);
        }
        in.close();
    }

    // Debug info
    void debug() const {
        cout << "[DEBUG] FrontIndex: " << frontIndex
            << ", RearIndex: " << rearIndex
            << ", Count: " << count << endl;
    }
};

