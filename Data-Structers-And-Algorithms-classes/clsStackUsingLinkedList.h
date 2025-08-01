#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Stack using Linked List implemented with templates

template <typename T>
class clsStackUsingLinkedList
{
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int count;

public:
    StackUsingLinkedList() : topNode(nullptr), count(0) {}

    ~StackUsingLinkedList() {
        clear();
    }

    // Push an element onto the stack
    void push(T value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++count;
    }

    // Remove the top element
    void pop() {
        if (isEmpty()) throw underflow_error("Stack underflow");
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        --count;
    }

    // Return the top element without removing it
    T peek() const {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return topNode->data;
    }

    // Return the size of the stack
    int size() const {
        return count;
    }

    // Clear all elements from the stack
    void clear() {
        while (!isEmpty()) pop();
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return topNode == nullptr;
    }

    // Display stack from top to bottom
    void display() const {
        Node* curr = topNode;
        cout << "Stack (top to bottom): ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // Check if the stack contains a value
    bool contains(T value) const {
        Node* curr = topNode;
        while (curr) {
            if (curr->data == value) return true;
            curr = curr->next;
        }
        return false;
    }

    // Return the bottom (first pushed) element
    T bottom() const {
        if (isEmpty()) throw underflow_error("Stack is empty");
        Node* curr = topNode;
        while (curr->next) curr = curr->next;
        return curr->data;
    }

    // Convert stack to vector (top to bottom)
    vector<T> toVector() const {
        vector<T> vec;
        Node* curr = topNode;
        while (curr) {
            vec.push_back(curr->data);
            curr = curr->next;
        }
        return vec;
    }

    // Reverse stack contents
    void reverse() {
        Node* prev = nullptr;
        Node* curr = topNode;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        topNode = prev;
    }

    // Merge another stack into this one (preserving order)
    void merge(const StackUsingLinkedList<T>& other) {
        vector<T> elements = other.toVector();
        for (int i = elements.size() - 1; i >= 0; --i) {
            push(elements[i]);
        }
    }

    // Sort the stack in ascending or descending order
    void sort(bool ascending = true) {
        vector<T> elements = toVector();
        clear();
        if (ascending)
            std::sort(elements.begin(), elements.end());
        else
            std::sort(elements.rbegin(), elements.rend());
        for (int i = elements.size() - 1; i >= 0; --i) {
            push(elements[i]);
        }
    }
};

