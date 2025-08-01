#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iterator>
#include <vector>
using namespace std;

// ============================
// Circular Doubly Linked List in C++ using Templates
// ============================

template <typename T>
class CDNode {
public:
    T data;
    CDNode* next;
    CDNode* prev;

    CDNode(T val) : data(val), next(this), prev(this) {}
};

template <typename T>
class clsCircularDoublyLinkedList
{
private:
    CDNode<T>* head;

public:
    CircularDoublyLinkedList() : head(nullptr) {}

    bool isEmpty() { return head == nullptr; }

    void insertAtHead(T val) {
        CDNode<T>* newNode = new CDNode<T>(val);
        if (!head) {
            head = newNode;
        }
        else {
            CDNode<T>* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T val) {
        if (!head) {
            insertAtHead(val);
        }
        else {
            CDNode<T>* newNode = new CDNode<T>(val);
            CDNode<T>* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
        }
    }

    void deleteHead() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            CDNode<T>* tail = head->prev;
            CDNode<T>* toDelete = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete toDelete;
        }
    }

    void deleteTail() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            CDNode<T>* tail = head->prev;
            CDNode<T>* newTail = tail->prev;
            newTail->next = head;
            head->prev = newTail;
            delete tail;
        }
    }

    void displayForward() {
        if (!head) return;
        CDNode<T>* temp = head;
        do {
            cout << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(head)\n";
    }

    void displayBackward() {
        if (!head) return;
        CDNode<T>* temp = head->prev;
        CDNode<T>* tail = temp;
        do {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        } while (temp != tail);
        cout << "(tail)\n";
    }

    int size() {
        if (!head) return 0;
        int count = 0;
        CDNode<T>* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
        return count;
    }

    void clear() {
        while (!isEmpty()) deleteHead();
    }

    void insertAfter(T target, T val) {
        if (!head) return;
        CDNode<T>* temp = head;
        do {
            if (temp->data == target) {
                CDNode<T>* newNode = new CDNode<T>(val);
                newNode->next = temp->next;
                newNode->prev = temp;
                temp->next->prev = newNode;
                temp->next = newNode;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    void deleteNode(T val) {
        if (!head) return;
        CDNode<T>* temp = head;
        do {
            if (temp->data == val) {
                if (temp == head) head = head->next;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == head && temp->next == temp) head = nullptr;
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    void updateItem(int index, T newVal) {
        if (!head || index < 0) throw out_of_range("Index out of range");
        int count = 0;
        CDNode<T>* temp = head;
        do {
            if (count == index) {
                temp->data = newVal;
                return;
            }
            count++;
            temp = temp->next;
        } while (temp != head);
        throw out_of_range("Index out of range");
    }

    T getItem(int index) {
        if (!head || index < 0) throw out_of_range("Index out of range");
        int count = 0;
        CDNode<T>* temp = head;
        do {
            if (count == index) return temp->data;
            count++;
            temp = temp->next;
        } while (temp != head);
        throw out_of_range("Index out of range");
    }

    void reverse() {
        if (!head || head->next == head) return;
        CDNode<T>* curr = head;
        do {
            swap(curr->next, curr->prev);
            curr = curr->prev;
        } while (curr != head);
        head = head->next;
    }

    CircularDoublyLinkedList<T> clone() {
        CircularDoublyLinkedList<T> copy;
        if (!head) return copy;
        CDNode<T>* temp = head;
        do {
            copy.insertAtTail(temp->data);
            temp = temp->next;
        } while (temp != head);
        return copy;
    }

    bool equals(const CircularDoublyLinkedList<T>& other) {
        if (this->size() != other.size()) return false;
        CDNode<T>* t1 = this->head;
        CDNode<T>* t2 = other.head;
        do {
            if (t1->data != t2->data) return false;
            t1 = t1->next;
            t2 = t2->next;
        } while (t1 != head);
        return true;
    }

    void mergeWith(CircularDoublyLinkedList<T>& other) {
        if (other.isEmpty()) return;
        CDNode<T>* temp = other.head;
        do {
            this->insertAtTail(temp->data);
            temp = temp->next;
        } while (temp != other.head);
    }

    T& operator[](int index) {
        if (index < 0 || index >= size()) throw out_of_range("Index out of range");
        CDNode<T>* temp = head;
        for (int i = 0; i < index; ++i) temp = temp->next;
        return temp->data;
    }

    vector<T> toVector() {
        vector<T> result;
        CDNode<T>* temp = head;
        if (!head) return result;
        do {
            result.push_back(temp->data);
            temp = temp->next;
        } while (temp != head);
        return result;
    }

    void fromVector(const vector<T>& vec) {
        clear();
        for (T val : vec) insertAtTail(val);
    }

    friend ostream& operator<<(ostream& os, const CircularDoublyLinkedList<T>& list) {
        CDNode<T>* temp = list.head;
        if (!temp) return os << "(empty)";
        do {
            os << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != list.head);
        return os << "(head)";
    }

};

