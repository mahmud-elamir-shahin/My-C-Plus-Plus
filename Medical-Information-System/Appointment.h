#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Appointment
{
public:
    int appointmentId;
    int patientId;
    int doctorId;
    string appointmentDate;
    string appointmentTime;
    bool isConfirmed;

    Appointment(int appointmentId, int patientId, int doctorId, string appointmentDate, string appointmentTime) {
        this->appointmentId = appointmentId;
        this->patientId = patientId;
        this->doctorId = doctorId;
        this->appointmentDate = appointmentDate;
        this->appointmentTime = appointmentTime;
    }

    string toString() {
        stringstream ss;
        ss << appointmentId << "," << patientId << "," << doctorId << "," << appointmentDate << "," << appointmentTime;
        return ss.str();
    }

    static Appointment fromString(string line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        return Appointment(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]), tokens[3], tokens[4]);
    }
};

