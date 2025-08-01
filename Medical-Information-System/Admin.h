#pragma once

#include "ClinicManagementSystem.h"
#include "User.h"

class Admin : public User
{
public:
    Admin() = default;
    Admin(string username, string password) : User(username, password, "admin") {}

    void displayMenu() override {
        ClinicManagementSystem cms;
        int choice;

        while (true) {
            cout << "\nAdmin Menu:" << endl;
            cout << "1. Add Patient" << endl;
            cout << "2. Add Doctor" << endl;
            cout << "3. Schedule Appointment" << endl;
            cout << "4. Generate Bill" << endl;
            cout << "5. Add Inventory Item" << endl;
            cout << "6. View Patients" << endl;
            cout << "7. View Doctors" << endl;
            cout << "8. View Appointments" << endl;
            cout << "9. View Bills" << endl;
            cout << "10. View Inventory" << endl;
            cout << "11. Pay Bill" << endl;
            cout << "12. Generate Reports" << endl;
            cout << "14. Confirm Appointment" << endl;
            cout << "15. Cancel Appointment" << endl;
            cout << "16. Add Prescription" << endl;
            cout << "17. View Prescriptions" << endl;
            cout << "18.  Manage Inventory" << endl;
            cout << "19. Insurance Management" << endl;
            cout << "20. View Activity Logs" << endl;
            cout << "21. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cms.addPatient();
                break;
            case 2:
                cms.addDoctor();
                break;
            case 3:
                cms.scheduleAppointment();
                break;
            case 4:
                cms.generateBill();
                break;
            case 5:
                cms.addInventoryItem();
                break;
            case 6:
                cms.viewPatients();
                break;
            case 7:
                cms.viewDoctors();
                break;
            case 8:
                cms.viewAppointments();
                break;
            case 9:
                cms.viewBills();
                break;
            case 10:
                cms.viewInventory();
                break;
            case 11:
                cms.payBill();
                break;
            case 12:
                cms.generateReports();
                break;
            case 13:
                cms.viewDoctors();
                break;
            case 14:
                cms.confirmAppointment();
                break;
            case 15:
                cms.cancelAppointment();
                break;
            case 16:
                cms.addPrescription();
                break;
            case 17:
                cms.viewPrescriptions();
                break;
            case 18:
                cms.manageInventory();
                break;
            case 19:
                cms.insuranceManagement();
                break;
            case 20:
                cms.viewActivityLogs();
                break;
            case 21:
                cout << "Exiting the system..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

};

