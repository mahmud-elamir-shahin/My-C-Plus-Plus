#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

// Queue using Linked List with templates

template <typename T>
class clsQueueUsingLinkedList
{
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int count;

public:
    QueueUsingLinkedList() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~QueueUsingLinkedList() {
        clear();
    }

    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        }
        else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty()) throw underflow_error("Queue underflow");
        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        count--;
        if (isEmpty()) rearNode = nullptr;
    }

    T front() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return frontNode->data;
    }

    T rear() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return rearNode->data;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void clear() {
        while (!isEmpty()) dequeue();
    }

    void display() const {
        cout << "Queue (front to rear): ";
        Node* curr = frontNode;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    bool contains(T value) const {
        Node* curr = frontNode;
        while (curr) {
            if (curr->data == value) return true;
            curr = curr->next;
        }
        return false;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* current = frontNode;
        rearNode = frontNode;
        while (current) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        frontNode = prev;
    }

    QueueUsingLinkedList<T> clone() const {
        QueueUsingLinkedList<T> newQueue;
        Node* curr = frontNode;
        while (curr) {
            newQueue.enqueue(curr->data);
            curr = curr->next;
        }
        return newQueue;
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) throw runtime_error("Failed to open file");
        Node* curr = frontNode;
        while (curr) {
            out << curr->data << endl;
            curr = curr->next;
        }
        out.close();
    }

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

    void debug() const {
        cout << "[DEBUG] Size: " << count << endl;
        cout << "Front: " << (frontNode ? frontNode->data : T()) << ", Rear: " << (rearNode ? rearNode->data : T()) << endl;
    }

    T getAt(int index) const {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        Node* curr = frontNode;
        for (int i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    void updateAt(int index, T value) {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        Node* curr = frontNode;
        for (int i = 0; i < index; ++i) curr = curr->next;
        curr->data = value;
    }

    void removeAt(int index) {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        if (index == 0) {
            dequeue();
            return;
        }
        Node* prev = frontNode;
        for (int i = 0; i < index - 1; ++i) prev = prev->next;
        Node* toDelete = prev->next;
        prev->next = toDelete->next;
        if (toDelete == rearNode) rearNode = prev;
        delete toDelete;
        count--;
    }

    void sort(bool ascending = true) {
        if (count < 2) return;
        vector<T> values;
        Node* curr = frontNode;
        while (curr) {
            values.push_back(curr->data);
            curr = curr->next;
        }
        std::sort(values.begin(), values.end());
        if (!ascending) std::reverse(values.begin(), values.end());
        curr = frontNode;
        for (const auto& val : values) {
            curr->data = val;
            curr = curr->next;
        }
    }

    void merge(const QueueUsingLinkedList<T>& other) {
        Node* curr = other.frontNode;
        while (curr) {
            enqueue(curr->data);
            curr = curr->next;
        }
    }
};

