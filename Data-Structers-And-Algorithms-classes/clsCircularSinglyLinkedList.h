#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

// ============================
// Circular Singly Linked List in C++ using Templates
// ============================

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class clsCircularSinglyLinkedList
{
private:
    Node<T>* head;

public:
    CircularSinglyLinkedList() {
        head = nullptr;
    }

    // Check if list is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Insert node at the head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
        head = newNode;
    }

    // Insert node at the tail
    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
    }

    // Insert after a specific value
    void insertAfter(T target, T val) {
        if (!head) return;
        Node<T>* temp = head;
        do {
            if (temp->data == target) {
                Node<T>* newNode = new Node<T>(val);
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    // Insert at specific index
    void insertAt(int index, T val) {
        if (index < 0) throw out_of_range("Index out of range");
        if (index == 0) {
            insertAtHead(val);
            return;
        }
        Node<T>* temp = head;
        int count = 0;
        while (temp->next != head && count < index - 1) {
            temp = temp->next;
            count++;
        }
        if (count != index - 1) throw out_of_range("Index out of range");
        Node<T>* newNode = new Node<T>(val);
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Delete head node
    void deleteHead() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != head)
            temp = temp->next;
        Node<T>* toDelete = head;
        temp->next = head->next;
        head = head->next;
        delete toDelete;
    }

    // Delete tail node
    void deleteTail() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* temp = head;
        while (temp->next->next != head)
            temp = temp->next;
        delete temp->next;
        temp->next = head;
    }

    // Delete node by value
    void deleteNode(T val) {
        if (!head) return;
        if (head->data == val) {
            deleteHead();
            return;
        }
        Node<T>* curr = head;
        do {
            if (curr->next->data == val) {
                Node<T>* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
                return;
            }
            curr = curr->next;
        } while (curr != head);
    }

    // Delete node at specific index
    void deleteAt(int index) {
        if (!head || index < 0) throw out_of_range("Index out of range");
        if (index == 0) {
            deleteHead();
            return;
        }
        Node<T>* temp = head;
        int count = 0;
        while (temp->next != head && count < index - 1) {
            temp = temp->next;
            count++;
        }
        if (temp->next == head || count != index - 1)
            throw out_of_range("Index out of range");
        Node<T>* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }

    // Delete first node
    void deleteFirstNode() {
        deleteHead();
    }

    // Delete last node
    void deleteLastNode() {
        deleteTail();
    }

    // Get length of list
    int length() {
        if (!head) return 0;
        int count = 0;
        Node<T>* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
        return count;
    }

    // Return number of nodes
    int size() {
        return length();
    }

    // Clear the entire list
    void clear() {
        if (!head) return;
        Node<T>* curr = head->next;
        while (curr != head) {
            Node<T>* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }

    // Get item at a specific position (0-indexed)
    T getItem(int index) {
        if (!head || index < 0) throw out_of_range("Index out of range");
        Node<T>* temp = head;
        int count = 0;
        do {
            if (count == index) return temp->data;
            temp = temp->next;
            count++;
        } while (temp != head);
        throw out_of_range("Index out of range");
    }

    // Update item at a specific index
    void updateItem(int index, T newVal) {
        if (!head || index < 0) throw out_of_range("Index out of range");
        Node<T>* temp = head;
        int count = 0;
        do {
            if (count == index) {
                temp->data = newVal;
                return;
            }
            temp = temp->next;
            count++;
        } while (temp != head);
        throw out_of_range("Index out of range");
    }

    // Sort the list (Bubble Sort)
    void sort() {
        if (!head || head->next == head) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* curr = head;
            do {
                Node<T>* nextNode = curr->next;
                if (nextNode != head && curr->data > nextNode->data) {
                    swap(curr->data, nextNode->data);
                    swapped = true;
                }
                curr = curr->next;
            } while (curr->next != head);
        } while (swapped);
    }

    // Remove duplicate values
    void removeDuplicates() {
        if (!head || head->next == head) return;
        Node<T>* curr = head;
        do {
            Node<T>* runner = curr;
            while (runner->next != head) {
                if (runner->next->data == curr->data) {
                    Node<T>* toDelete = runner->next;
                    runner->next = runner->next->next;
                    delete toDelete;
                }
                else {
                    runner = runner->next;
                }
            }
            curr = curr->next;
        } while (curr != head);
    }

    // Reverse the list
    void reverse() {
        if (!head || head->next == head) return;
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;
        Node<T>* last = head;
        while (last->next != head) last = last->next;
        do {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        } while (curr != head);
        head->next = prev;
        head = prev;
        last->next = head;
    }

    // Merge with another list
    void mergeWith(const CircularSinglyLinkedList<T>& other) {
        vector<T> otherData = other.toVector();
        for (T val : otherData) {
            insertAtTail(val);
        }
    }

    // Save list to a file
    void saveToFile(const string& filename) {
        ofstream out(filename);
        if (!head || !out) return;
        Node<T>* temp = head;
        do {
            out << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        out.close();
    }

    // Load list from a file (clears existing data)
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

    // Check if value exists in list
    bool contains(T val) {
        if (!head) return false;
        Node<T>* temp = head;
        do {
            if (temp->data == val) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    // Count how many times value occurs
    int countOccurrences(T val) {
        if (!head) return 0;
        int count = 0;
        Node<T>* temp = head;
        do {
            if (temp->data == val) count++;
            temp = temp->next;
        } while (temp != head);
        return count;
    }

    // Convert to std::vector
    vector<T> toVector() const {
        vector<T> result;
        if (!head) return result;
        Node<T>* temp = head;
        do {
            result.push_back(temp->data);
            temp = temp->next;
        } while (temp != head);
        return result;
    }

    // Display all elements
    void display() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        Node<T>* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(head)\n";
    }

};

