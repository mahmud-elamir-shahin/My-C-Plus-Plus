#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <fstream>
using namespace std;

// Queue using two Stacks

template <typename T>
class clsQueueUsingStacks
{
private:
    stack<T> inputStack;   // Stack to handle enqueue
    stack<T> outputStack;  // Stack to handle dequeue

    void transfer() {
        while (!inputStack.empty()) {
            outputStack.push(inputStack.top());
            inputStack.pop();
        }
    }

public:
    void enqueue(T value) {
        inputStack.push(value);
    }

    void dequeue() {
        if (isEmpty()) throw underflow_error("Queue underflow");
        if (outputStack.empty()) transfer();
        outputStack.pop();
    }

    T front() {
        if (isEmpty()) throw underflow_error("Queue is empty");
        if (outputStack.empty()) transfer();
        return outputStack.top();
    }

    T rear() {
        if (isEmpty()) throw underflow_error("Queue is empty");
        if (!inputStack.empty()) return inputStack.top();
        while (!outputStack.empty()) {
            inputStack.push(outputStack.top());
            outputStack.pop();
        }
        return inputStack.top();
    }

    bool isEmpty() const {
        return inputStack.empty() && outputStack.empty();
    }

    int size() const {
        return inputStack.size() + outputStack.size();
    }

    void clear() {
        while (!inputStack.empty()) inputStack.pop();
        while (!outputStack.empty()) outputStack.pop();
    }

    void display() {
        stack<T> tempInput = inputStack;
        stack<T> tempOutput = outputStack;

        cout << "Queue (front to rear): ";
        while (!tempOutput.empty()) {
            cout << tempOutput.top() << " ";
            tempOutput.pop();
        }

        vector<T> reversedInput;
        while (!tempInput.empty()) {
            reversedInput.push_back(tempInput.top());
            tempInput.pop();
        }
        for (auto it = reversedInput.rbegin(); it != reversedInput.rend(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

    bool contains(T value) {
        stack<T> tempInput = inputStack;
        stack<T> tempOutput = outputStack;

        while (!tempOutput.empty()) {
            if (tempOutput.top() == value) return true;
            tempOutput.pop();
        }

        while (!tempInput.empty()) {
            if (tempInput.top() == value) return true;
            tempInput.pop();
        }

        return false;
    }

    void reverse() {
        if (outputStack.empty()) transfer();
        while (!outputStack.empty()) {
            inputStack.push(outputStack.top());
            outputStack.pop();
        }
    }

    QueueUsingStacks<T> clone() const {
        QueueUsingStacks<T> copy;
        copy.inputStack = inputStack;
        copy.outputStack = outputStack;
        return copy;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) throw runtime_error("Failed to open file");

        stack<T> tempOutput = outputStack;
        vector<T> reversedInput;
        stack<T> tempInput = inputStack;

        while (!tempOutput.empty()) {
            file << tempOutput.top() << " ";
            tempOutput.pop();
        }
        while (!tempInput.empty()) {
            reversedInput.push_back(tempInput.top());
            tempInput.pop();
        }
        for (auto it = reversedInput.rbegin(); it != reversedInput.rend(); ++it) {
            file << *it << " ";
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) throw runtime_error("Failed to open file");

        clear();
        T value;
        vector<T> values;
        while (file >> value) values.push_back(value);
        for (T v : values) enqueue(v);
    }
};

