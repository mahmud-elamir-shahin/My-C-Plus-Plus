#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>//hhhhhhhhhh
#include <sstream>
#include <map>
#include <ctime>
#include <algorithm>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Billing.h"
#include "InventoryItem.h"
#include "Prescription.h"
#include "UtilityFunctions.h"

using namespace std;

class ClinicManagementSystem
{
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    vector<Billing> bills;
    vector<InventoryItem> inventory;
    vector<string> activityLogs;
    vector<Prescription> prescriptions;


    int patientCounter = 0;
    int doctorCounter = 0;
    int appointmentCounter = 0;
    int billCounter = 0;
    int inventoryCounter = 0;
    int prescriptionCounter = 0;

    // Load and save methods for all entities, including activity logs
    // ...

    void loadActivityLogs() {
        ifstream file("activity_logs.txt");
        string line;
        while (getline(file, line)) {
            activityLogs.push_back(line);
        }
        file.close();
    }

    void saveActivityLogs() {
        ofstream file("activity_logs.txt");
        for (const auto& log : activityLogs) {
            file << log << endl;
        }
        file.close();
    }

   // void addActivityLog(string activity) {//kkkkkkkkkkkkkkkkkk
   //     activityLogs.push_back(getCurrentDateTime() + " - " + activity);
   // }


public:
    ClinicManagementSystem() {
        loadPatients();
        loadDoctors();
        loadAppointments();
        loadBills();
        loadInventory();
        loadActivityLogs();
        loadPrescriptions();
    }

    ~ClinicManagementSystem() {
        savePatients();
        saveDoctors();
        saveAppointments();
        saveBills();
        saveInventory();
        saveActivityLogs();
        savePrescriptions();
    }




    void confirmAppointment() {
        int appointmentId;
        cout << "Enter Appointment ID to confirm: ";
        cin >> appointmentId;

        for (auto& appointment : appointments) {
            if (appointment.appointmentId == appointmentId) {
                appointment.isConfirmed = true;
                cout << "Appointment ID " << appointmentId << " confirmed." << endl;
                addActivityLog("Confirmed appointment with ID " + to_string(appointmentId));
                return;
            }
        }
        cout << "Appointment ID not found." << endl;
    }

    void cancelAppointment() {
        int appointmentId;
        cout << "Enter Appointment ID to cancel: ";
        cin >> appointmentId;

        auto it = find_if(appointments.begin(), appointments.end(), [&](Appointment& a) {
            return a.appointmentId == appointmentId;
            });

        if (it != appointments.end()) {
            appointments.erase(it);
            cout << "Appointment ID " << appointmentId << " canceled." << endl;
            addActivityLog("Canceled appointment with ID " + to_string(appointmentId));
        }
        else {
            cout << "Appointment ID not found." << endl;
        }
    }

    void addPrescription() {
        Prescription p;
        p.prescriptionId = ++prescriptionCounter;

        cout << "Enter Patient ID: ";
        cin >> p.patientId;

        cout << "Enter Doctor ID: ";
        cin >> p.doctorId;

        cout << "Enter Medication: ";
        cin >> p.medication;

        cout << "Enter Dosage: ";
        cin >> p.dosage;

        cout << "Enter Start Date (YYYY-MM-DD): ";
        cin >> p.startDate;

        cout << "Enter End Date (YYYY-MM-DD): ";
        cin >> p.endDate;

        prescriptions.push_back(p);
        cout << "Prescription added successfully with ID: " << p.prescriptionId << endl;
        addActivityLog("Added prescriptionID " + to_string(p.prescriptionId));
    }

    void viewPrescriptions() {
        int patientId;
        cout << "Enter Patient ID to view prescriptions: ";
        cin >> patientId;

        cout << "\nPrescriptions for Patient ID " << patientId << ":\n";
        for (const auto& prescription : prescriptions) {
            if (prescription.patientId == patientId) {
                cout << "Prescription ID: " << prescription.prescriptionId
                    << ", Doctor ID: " << prescription.doctorId
                    << ", Medication: " << prescription.medication
                    << ", Dosage: " << prescription.dosage
                    << ", Start Date: " << prescription.startDate
                    << ", End Date: " << prescription.endDate << endl;
            }
        }
    }

    void manageInventory() {
        cout << "Inventory Management\n";
        for (const auto& item : inventory) {
            cout << "Item ID: " << item.itemId
                << ", Name: " << item.itemName
                << ", Quantity: " << item.quantity
                << ", Price: " << item.price
                << ", Expiration Date: " << item.expirationDate << endl;
        }
    }

    void insuranceManagement() {
        int patientId;
        cout << "Enter Patient ID to manage insurance: ";
        cin >> patientId;

        for (auto& patient : patients) {
            if (patient.id == patientId) {
                cout << "Current Insurance Details: " << patient.insuranceDetails << endl;
                cout << "Enter new insurance details: ";
                cin >> patient.insuranceDetails;
                cout << "Insurance details updated." << endl;
                addActivityLog("Updated insurance details for Patient ID " + to_string(patientId));
                return;
            }
        }
        cout << "Patient ID not found." << endl;
    }

    // Existing methods like addPatient, addDoctor, etc. with encryption and logging added





    void searchPatient() {
        string searchKey;
        cout << "Enter patient name, ID, or phone number to search: ";
        cin >> searchKey;
        transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

        cout << "\nSearch Results:" << endl;
        for (const auto& patient : patients) {
            string patientData = to_string(patient.id) + patient.name + patient.phone;
            transform(patientData.begin(), patientData.end(), patientData.begin(), ::tolower);
            if (patientData.find(searchKey) != string::npos) {
                cout << "ID: " << patient.id
                    << ", Name: " << patient.name
                    << ", Age: " << patient.age
                    << ", Gender: " << patient.gender
                    << ", Phone: " << patient.phone
                    << ", Address: " << patient.address
                    << ", Medical History: " << patient.medicalHistory << endl;
            }
        }
    }

    void addActivityLog(string activity) {
        activityLogs.push_back(getCurrentDateTime() + " - " + activity);
    }

    void viewActivityLogs() {
        cout << "\nUser Activity Logs:" << endl;
        for (const auto& log : activityLogs) {
            cout << log << endl;
        }
    }





    void addPatient() {
        string name, gender, phone, address, medicalHistory, insuranceDetails;
        int age;
        cout << "Enter patient details:" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Age: ";
        cin >> age;
        cout << "Gender: ";
        cin.ignore();
        getline(cin, gender);
        cout << "Phone: ";
        getline(cin, phone);
        cout << "Address: ";
        getline(cin, address);
        cout << "Medical History: ";
        getline(cin, medicalHistory);
        cout << "insuranceDetails: ";
        getline(cin, insuranceDetails);

        patients.push_back(Patient(++patientCounter, name, age, gender, phone, address, medicalHistory, insuranceDetails));
        cout << "Patient added successfully with ID: " << patientCounter << endl;
    }

    void addDoctor() {
        string name, specialization, phone, address;
        cout << "Enter doctor details:" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Specialization: ";
        getline(cin, specialization);
        cout << "Phone: ";
        getline(cin, phone);
        cout << "Address: ";
        getline(cin, address);

        doctors.push_back(Doctor(++doctorCounter, name, specialization, phone, address));
        cout << "Doctor added successfully with ID: " << doctorCounter << endl;
    }

    void scheduleAppointment() {
        int patientId, doctorId;
        string date, time;

        cout << "Enter patient ID: ";
        cin >> patientId;

        if (!findPatientById(patientId)) {
            cout << "Patient ID not found." << endl;
            return;
        }

        cout << "Enter doctor ID: ";
        cin >> doctorId;

        if (!findDoctorById(doctorId)) {
            cout << "Doctor ID not found." << endl;
            return;
        }

        cout << "Enter appointment details:" << endl;
        cout << "Date (DD/MM/YYYY): ";
        cin.ignore();
        getline(cin, date);
        cout << "Time (HH:MM): ";
        getline(cin, time);

        appointments.push_back(Appointment(++appointmentCounter, patientId, doctorId, date, time));
        cout << "Appointment scheduled successfully with ID: " << appointmentCounter << endl;
    }

    void generateBill() {
        int patientId;
        double amount;

        cout << "Enter patient ID: ";
        cin >> patientId;

        if (!findPatientById(patientId)) {
            cout << "Patient ID not found." << endl;
            return;
        }

        cout << "Enter bill amount: ";
        cin >> amount;

        bills.push_back(Billing(++billCounter, patientId, amount, "Unpaid"));
        cout << "Bill generated successfully with ID: " << billCounter << endl;
    }

    void addInventoryItem() {
        string itemName;
        int quantity;
        double price;

        cout << "Enter inventory item details:" << endl;
        cout << "Item Name: ";
        cin.ignore();
        getline(cin, itemName);
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Price: ";
        cin >> price;



        inventory.push_back(InventoryItem(++inventoryCounter, itemName, quantity, price));
        cout << "Inventory item added successfully with ID: " << inventoryCounter << endl;
    }

    void viewPatients() {
        cout << "\nList of Patients:" << endl;
        for (const auto& patient : patients) {
            cout << "ID: " << patient.id
                << ", Name: " << patient.name
                << ", Age: " << patient.age
                << ", Gender: " << patient.gender
                << ", Phone: " << patient.phone
                << ", Address: " << patient.address
                << ", Medical History: " << patient.medicalHistory << endl;
        }
    }

    void viewDoctors() {
        cout << "\nList of Doctors:" << endl;
        for (const auto& doctor : doctors) {
            cout << "ID: " << doctor.id
                << ", Name: " << doctor.name
                << ", Specialization: " << doctor.specialization
                << ", Phone: " << doctor.phone
                << ", Address: " << doctor.address << endl;
        }
    }

    void viewAppointments() {
        cout << "\nList of Appointments:" << endl;
        for (const auto& appointment : appointments) {
            cout << "Appointment ID: " << appointment.appointmentId
                << ", Patient ID: " << appointment.patientId
                << ", Doctor ID: " << appointment.doctorId
                << ", Date: " << appointment.appointmentDate
                << ", Time: " << appointment.appointmentTime << endl;
        }
    }

    void viewBills() {
        cout << "\nList of Bills:" << endl;
        for (const auto& bill : bills) {
            cout << "Bill ID: " << bill.billId
                << ", Patient ID: " << bill.patientId
                << ", Amount: $" << bill.amount
                << ", Payment Status: " << bill.paymentStatus << endl;
        }
    }

    void viewInventory() {
        cout << "\nList of Inventory Items:" << endl;
        for (const auto& item : inventory) {
            cout << "Item ID: " << item.itemId
                << ", Name: " << item.itemName
                << ", Quantity: " << item.quantity
                << ", Price: $" << item.price << endl;
        }
    }

    void payBill() {
        int billId;
        cout << "Enter Bill ID to mark as paid: ";
        cin >> billId;

        for (auto& bill : bills) {
            if (bill.billId == billId) {
                bill.paymentStatus = "Paid";
                cout << "Bill ID " << billId << " marked as paid." << endl;
                return;
            }
        }
        cout << "Bill ID not found." << endl;
    }

    void generateReports() {
        // Report 1: Total patients
        cout << "\nTotal Patients: " << patients.size() << endl;

        // Report 2: Total appointments
        cout << "Total Appointments: " << appointments.size() << endl;

        // Report 3: Total revenue
        double totalRevenue = 0;
        for (const auto& bill : bills) {
            totalRevenue += bill.amount;
        }
        cout << "Total Revenue: $" << totalRevenue << endl;
    }

private:
    bool findPatientById(int id) {
        for (const auto& patient : patients) {
            if (patient.id == id) {
                return true;
            }
        }
        return false;
    }

    bool findDoctorById(int id) {
        for (const auto& doctor : doctors) {
            if (doctor.id == id) {
                return true;
            }
        }
        return false;
    }

    void loadPatients() {
        ifstream file("patients.txt");
        string line;
        while (getline(file, line)) {
            patients.push_back(Patient::fromString(line));
            patientCounter++;
        }
        file.close();
    }

    void savePatients() {
        ofstream file("patients.txt");
        for (auto& patient : patients) {
            file << patient.toString() << endl;
        }
        file.close();
    }

    void loadDoctors() {
        ifstream file("doctors.txt");
        string line;
        while (getline(file, line)) {
            doctors.push_back(Doctor::fromString(line));
            doctorCounter++;
        }
        file.close();
    }

    void saveDoctors() {
        ofstream file("doctors.txt");
        for (auto& doctor : doctors) {
            file << doctor.toString() << endl;
        }
        file.close();
    }

    void loadAppointments() {
        ifstream file("appointments.txt");
        string line;
        while (getline(file, line)) {
            appointments.push_back(Appointment::fromString(line));
            appointmentCounter++;
        }
        file.close();
    }

    void saveAppointments() {
        ofstream file("appointments.txt");
        for (auto& appointment : appointments) {
            file << appointment.toString() << endl;
        }
        file.close();
    }

    void loadBills() {
        ifstream file("bills.txt");
        string line;
        while (getline(file, line)) {
            bills.push_back(Billing::fromString(line));
            billCounter++;
        }
        file.close();
    }

    void saveBills() {
        ofstream file("bills.txt");
        for (auto& bill : bills) {
            file << bill.toString(bill) << endl;
        }
        file.close();
    }

    void loadInventory() {
        ifstream file("inventory.txt");
        string line;
        while (getline(file, line)) {
            inventory.push_back(InventoryItem::fromString(line));
            inventoryCounter++;
        }
        file.close();
    }

    void saveInventory() {
        ofstream file("inventory.txt");
        for (auto& item : inventory) {
            file << item.toString() << endl;
        }
        file.close();
    }


    void loadPrescriptions() {
        ifstream file("prescriptions.txt");
        string line;
        while (getline(file, line)) {
            prescriptions.push_back(Prescription::fromString(decryptData(line)));
        }
        file.close();
    }

    void savePrescriptions() {
        ofstream file("prescriptions.txt");
        for (const auto& prescription : prescriptions) {
            file << encryptData(prescription.toString()) << endl;
        }
        file.close();
    }
};

