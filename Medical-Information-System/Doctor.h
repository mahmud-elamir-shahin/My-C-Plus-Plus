#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Doctor
{
public:
    int id;
    string name;
    string specialization;
    string phone;
    string address;

    Doctor(int id, string name, string specialization, string phone, string address) {
        this->id = id;
        this->name = name;
        this->specialization = specialization;
        this->phone = phone;
        this->address = address;
    }

    string toString() {
        stringstream ss;
        ss << id << "," << name << "," << specialization << "," << phone << "," << address;
        return ss.str();
    }

    static Doctor fromString(string line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return Doctor(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4]);
    }


    /*static Doctor fromString(const string& line) {
        Doctor d;
        stringstream ss(line);
        ss >> d.id >> d.name >> d.specialization >> d.phone >> d.address;
        return d;
    }

    string toString() const {
        return to_string(id) + " " + name + " " + specialization + " " + phone + " " + address;
    }*/

};

