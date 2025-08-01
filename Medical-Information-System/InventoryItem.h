#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class InventoryItem
{
public:
    int itemId;
    string itemName;
    int quantity;
    double price;
    string expirationDate;

    InventoryItem(int itemId, string itemName, int quantity, double price) {
        this->itemId = itemId;
        this->itemName = itemName;
        this->quantity = quantity;
        this->price = price;
    }

    string toString() {
        stringstream ss;
        ss << itemId << "," << itemName << "," << quantity << "," << price;
        return ss.str();
    }

    static InventoryItem fromString(string line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return InventoryItem(stoi(tokens[0]), tokens[1], stoi(tokens[2]), stod(tokens[3]));
    }



    /*static InventoryItem fromString(const string& line) {
        InventoryItem i;
        stringstream ss(line);
        ss >> i.itemId >> i.itemName >> i.quantity >> i.price >> i.expirationDate;
        return i;
    }

    string toString() const {
        return to_string(itemId) + " " + itemName + " " + to_string(quantity) + " " + to_string(price) + " " + expirationDate;
    }*/

};

