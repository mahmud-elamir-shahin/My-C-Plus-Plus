#pragma once

#include <string>
#include <sstream>

using namespace std;

class Prescription
{
public:
    int prescriptionId;
    int patientId;
    int doctorId;
    string medication;
    string dosage;
    string startDate;
    string endDate;

    static Prescription fromString(const string& line) {
        Prescription p;
        stringstream ss(line);
        ss >> p.prescriptionId >> p.patientId >> p.doctorId >> p.medication >> p.dosage >> p.startDate >> p.endDate;
        return p;
    }

    string toString() const {
        return to_string(prescriptionId) + " " + to_string(patientId) + " " + to_string(doctorId) + " " + medication + " " + dosage + " " + startDate + " " + endDate;
    }
};

