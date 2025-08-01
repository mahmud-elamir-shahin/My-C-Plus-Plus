#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iterator>
using namespace std;

// ============================
// Doubly Linked List in C++ using Templates
// ============================

template <typename T>
class DNode {
public:
    T data;
    DNode* next;
    DNode* prev;

    DNode(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class clsDoublyLinkedList
{
private:
    DNode<T>* head;
    DNode<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Check if list is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Insert at head
    void insertAtHead(T val) {
        DNode<T>* newNode = new DNode<T>(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insert at tail
    void insertAtTail(T val) {
        DNode<T>* newNode = new DNode<T>(val);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Insert after a specific value
    void insertAfter(T target, T val) {
        DNode<T>* temp = head;
        while (temp) {
            if (temp->data == target) {
                DNode<T>* newNode = new DNode<T>(val);
                newNode->next = temp->next;
                newNode->prev = temp;
                if (temp->next) temp->next->prev = newNode;
                else tail = newNode;
                temp->next = newNode;
                return;
            }
            temp = temp->next;
        }
    }

    // Insert at specific index
    void insertAt(int index, T val) {
        if (index < 0) throw out_of_range("Index out of range");
        if (index == 0) {
            insertAtHead(val);
            return;
        }
        DNode<T>* temp = head;
        int count = 0;
        while (temp && count < index - 1) {
            temp = temp->next;
            count++;
        }
        if (!temp) throw out_of_range("Index out of range");
        DNode<T>* newNode = new DNode<T>(val);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) temp->next->prev = newNode;
        else tail = newNode;
        temp->next = newNode;
    }

    // Delete head node
    void deleteHead() {
        if (!head) return;
        DNode<T>* toDelete = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete toDelete;
    }

    // Delete tail node
    void deleteTail() {
        if (!tail) return;
        DNode<T>* toDelete = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete toDelete;
    }

    // Delete node by value
    void deleteNode(T val) {
        DNode<T>* temp = head;
        while (temp) {
            if (temp->data == val) {
                if (temp == head) deleteHead();
                else if (temp == tail) deleteTail();
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                }
                return;
            }
            temp = temp->next;
        }
    }

    // Delete at index
    void deleteAt(int index) {
        if (index < 0) throw out_of_range("Index out of range");
        if (index == 0) {
            deleteHead();
            return;
        }
        DNode<T>* temp = head;
        int count = 0;
        while (temp && count < index) {
            temp = temp->next;
            count++;
        }
        if (!temp) throw out_of_range("Index out of range");
        if (temp == tail) deleteTail();
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }

    // Update item at index
    void updateItem(int index, T newVal) {
        if (index < 0) throw out_of_range("Index out of range");
        DNode<T>* temp = head;
        int count = 0;
        while (temp && count < index) {
            temp = temp->next;
            count++;
        }
        if (!temp) throw out_of_range("Index out of range");
        temp->data = newVal;
    }

    // Get item at index
    T getItem(int index) {
        if (index < 0) throw out_of_range("Index out of range");
        DNode<T>* temp = head;
        int count = 0;
        while (temp && count < index) {
            temp = temp->next;
            count++;
        }
        if (!temp) throw out_of_range("Index out of range");
        return temp->data;
    }

    // Get list size
    int size() {
        int count = 0;
        DNode<T>* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Clear list
    void clear() {
        while (!isEmpty()) {
            deleteHead();
        }
    }

    // Remove duplicates
    void removeDuplicates() {
        DNode<T>* current = head;
        while (current) {
            DNode<T>* runner = current->next;
            while (runner) {
                if (runner->data == current->data) {
                    DNode<T>* toDelete = runner;
                    runner = runner->next;
                    if (toDelete == tail) tail = toDelete->prev;
                    toDelete->prev->next = toDelete->next;
                    if (toDelete->next) toDelete->next->prev = toDelete->prev;
                    delete toDelete;
                }
                else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    // Sort the list (bubble sort)
    void sort() {
        if (!head || head == tail) return;
        bool swapped;
        do {
            swapped = false;
            DNode<T>* curr = head;
            while (curr->next) {
                if (curr->data > curr->next->data) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    // Clone list
    DoublyLinkedList<T> clone() {
        DoublyLinkedList<T> copy;
        DNode<T>* temp = head;
        while (temp) {
            copy.insertAtTail(temp->data);
            temp = temp->next;
        }
        return copy;
    }

    // Check if two lists are equal
    bool equals(const DoublyLinkedList<T>& other) {
        DNode<T>* a = head;
        DNode<T>* b = other.head;
        while (a && b) {
            if (a->data != b->data) return false;
            a = a->next;
            b = b->next;
        }
        return a == nullptr && b == nullptr;
    }

    // Reverse the list
    void reverse() {
        DNode<T>* curr = head;
        DNode<T>* prev = nullptr;
        tail = head;
        while (curr) {
            swap(curr->next, curr->prev);
            prev = curr;
            curr = curr->prev;
        }
        head = prev;
    }

    // Merge with another list
    void mergeWith(DoublyLinkedList<T>& other) {
        if (other.isEmpty()) return;
        if (isEmpty()) {
            head = other.head;
            tail = other.tail;
        }
        else {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
        }
        other.head = other.tail = nullptr;
    }

    // Display list forward
    void displayForward() {
        DNode<T>* temp = head;
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Display list backward
    void displayBackward() {
        DNode<T>* temp = tail;
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }

    // Save to file
    void saveToFile(const string& filename) {
        ofstream out(filename);
        if (!out) return;
        DNode<T>* temp = head;
        while (temp) {
            out << temp->data << " ";
            temp = temp->next;
        }
        out.close();
    }

    // Load from file
    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) return;
        clear();
        T val;
        while (in >> val) {
            insertAtTail(val);
        }
        in.close();
    }

};

