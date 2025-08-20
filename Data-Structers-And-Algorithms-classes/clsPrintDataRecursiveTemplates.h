#pragma once

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class clsPrintDataRecursiveTemplates
{
    // =======================
// 1. Print Array (Recursive)
// =======================
    template <typename T>
    void printData(const T arr[], int size, int index = 0) {
        if (index == size) return;
        cout << arr[index] << " ";
        printData(arr, size, index + 1);
    }

    // =======================
    // 2. Print Stack (Recursive)
    // =======================
    template <typename T>
    void printData(stack<T>& s) {
        if (s.empty()) return;

        T top = s.top();
        s.pop();
        cout << top << " ";

        printData(s);

        s.push(top); // Restore original stack
    }

    // =======================
    // 3. Linked List Node definition
    // =======================
    template <typename T>
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    // Print Linked List (Recursive)
    template <typename T>
    void printData(Node<T>* head) {
        if (!head) return;
        cout << head->data << " ";
        printData(head->next);
    }

    // =======================
    // 4. Print Queue (Recursive)
    // =======================
    template <typename T>
    void printData(queue<T>& q) {
        if (q.empty()) return;

        T front = q.front();
        q.pop();
        cout << front << " ";

        printData(q);

        q.push(front); // Restore original queue
    }
};

