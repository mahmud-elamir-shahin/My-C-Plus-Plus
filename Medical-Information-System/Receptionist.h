#pragma once

#include "ClinicManagementSystem.h"
#include "User.h"

class Receptionist : public User
{
public:
    Receptionist(string username, string password) : User(username, password, "receptionist") {}

    void displayMenu() override {
        ClinicManagementSystem cms;
        int choice;

        while (true) {
            cout << "\nReceptionist Menu:" << endl;
            cout << "1. Add Patient" << endl;
            cout << "2. Schedule Appointment" << endl;
            cout << "3. Generate Bill" << endl;
            cout << "4. View Patients" << endl;
            cout << "5. View Appointments" << endl;
            cout << "6. View Bills" << endl;
            cout << "7. Pay Bill" << endl;
            cout << "8. View Prescriptions" << endl;
            cout << "9. Insurance Management" << endl;
            cout << "10. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cms.addPatient();
                break;
            case 2:
                cms.scheduleAppointment();
                break;
            case 3:
                cms.generateBill();
                break;
            case 4:
                cms.viewPatients();
                break;
            case 5:
                cms.viewAppointments();
                break;
            case 6:
                cms.viewBills();
                break;
            case 7:
                cms.payBill();
                break;
            case 8:
                cms.viewPrescriptions();
                break;
            case 9:
                cms.insuranceManagement();
                break;
            case 10:
                cout << "Exiting the system..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

};

