#pragma once

// ============================
// Singly Linked List in C++ using Templates
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
class clsSinglyLinkedList
{

    void deleteByValue(T val) {
        if (!head) return;
        if (head->data == val) {
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }
        Node<T>* temp = head;
        while (temp->next && temp->next->data != val)
            temp = temp->next;
        if (temp->next) {
            Node<T>* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    void deleteFirstNode() {
        deleteHead();
    }

    void deleteLastNode() {
        deleteTail();
    }

    void deleteNode(T val) {
        deleteByValue(val);
    }

    bool search(T val) {
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == val) return true;
            temp = temp->next;
        }
        return false;
    }

    int length() {
        int count = 0;
        Node<T>* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    int size() {
        return length();
    }

    T getItem(int index) {
        Node<T>* temp = head;
        int i = 0;
        while (temp && i < index) {
            temp = temp->next;
            i++;
        }
        if (!temp) throw out_of_range("Index out of bounds");
        return temp->data;
    }

    void updateItem(int index, T newVal) {
        Node<T>* temp = head;
        int i = 0;
        while (temp && i < index) {
            temp = temp->next;
            i++;
        }
        if (!temp) return;
        temp->data = newVal;
    }

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    T getMiddle() {
        if (!head) throw runtime_error("List is empty");
        Node<T>* slow = head;
        Node<T>* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }

    int countOccurrences(T val) {
        int count = 0;
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == val) count++;
            temp = temp->next;
        }
        return count;
    }

    void removeDuplicates() {
        Node<T>* current = head;
        while (current) {
            Node<T>* runner = current;
            while (runner->next) {
                if (runner->next->data == current->data) {
                    Node<T>* dup = runner->next;
                    runner->next = runner->next->next;
                    delete dup;
                }
                else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    void swapNodes(T x, T y) {
        if (x == y) return;
        Node<T>* prevX = nullptr, * currX = head;
        Node<T>* prevY = nullptr, * currY = head;
        while (currX && currX->data != x) {
            prevX = currX;
            currX = currX->next;
        }
        while (currY && currY->data != y) {
            prevY = currY;
            currY = currY->next;
        }
        if (!currX || !currY) return;
        if (prevX) prevX->next = currY;
        else head = currY;
        if (prevY) prevY->next = currX;
        else head = currX;
        swap(currX->next, currY->next);
    }

    bool isPalindrome() {
        if (!head || !head->next) return true;
        Node<T>* slow = head;
        Node<T>* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = slow;
        while (curr) {
            Node<T>* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        Node<T>* first = head;
        Node<T>* second = prev;
        while (second) {
            if (first->data != second->data) return false;
            first = first->next;
            second = second->next;
        }
        return true;
    }

    void mergeWith(SinglyLinkedList<T>& other) {
        if (!head) {
            head = other.head;
            return;
        }
        Node<T>* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = other.head;
    }

    void rotate(int k) {
        if (!head || k == 0) return;
        Node<T>* temp = head;
        int len = 1;
        while (temp->next) {
            temp = temp->next;
            len++;
        }
        temp->next = head;
        k = k % len;
        for (int i = 0; i < len - k; i++)
            temp = temp->next;
        head = temp->next;
        temp->next = nullptr;
    }

    void sort() {
        if (!head || !head->next) return;
        for (Node<T>* i = head; i != nullptr; i = i->next) {
            for (Node<T>* j = head; j->next != nullptr; j = j->next) {
                if (j->data > j->next->data)
                    swap(j->data, j->next->data);
            }
        }
    }

    void display() {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

