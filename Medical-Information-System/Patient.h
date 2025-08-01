#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Patient
{
public:
    int id;
    string name;
    int age;
    string gender;
    string phone;
    string address;
    string medicalHistory;
    string insuranceDetails;

    Patient(int id, string name, int age, string gender, string phone, string address, string medicalHistory, string insuranceDetails) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->phone = phone;
        this->address = address;
        this->medicalHistory = medicalHistory;
        this->insuranceDetails = insuranceDetails;
    }

    Patient() {};

    string toString() {
        stringstream ss;
        ss << id << "," << name << "," << age << "," << gender << "," << phone << "," << address << "," << medicalHistory << "," << insuranceDetails;
        return ss.str();
    }

    string toString() const {
        return to_string(id) + " " + name + " " + to_string(age) + " " + gender + " " + phone + " " + address + " " + medicalHistory + " " + insuranceDetails;
    }

    static Patient fromString(string line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return Patient(stoi(tokens[0]), tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5], tokens[6], tokens[6]);
    }

    /*static Patient fromString(const string& line) {
        Patient p;
        stringstream ss(line);
        ss >> p.id >> p.name >> p.age >> p.gender >> p.phone >> p.address >> p.medicalHistory >> p.insuranceDetails;
        return p;
    }*/
};

