#pragma once


#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Billing
{
public:
    int billId;
    int patientId;
    double amount;
    string paymentStatus;

    Billing(int billId, int patientId, double amount, string paymentStatus) {
        this->billId = billId;
        this->patientId = patientId;
        this->amount = amount;
        this->paymentStatus = paymentStatus;
    }

    string toString(Billing B) {
        stringstream ss;
        ss << B.billId << "," << B.patientId << "," << B.amount << "," << B.paymentStatus;
        return ss.str();
    }
    string toString() {
        stringstream ss;
        ss << billId << "," << patientId << "," << amount << "," << paymentStatus;
        return ss.str();
    }

    static Billing fromString(string line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return Billing(stoi(tokens[0]), stoi(tokens[1]), stod(tokens[2]), tokens[3]);
    }
};

