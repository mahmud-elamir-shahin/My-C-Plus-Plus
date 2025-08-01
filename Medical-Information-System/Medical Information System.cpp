#include "ClinicManagementSystem.h"
#include "UserManager.h"

int main() {
    /*UserManager userManager;
    string username, password;

    cout << "Welcome to the Clinic Management System" << endl;
    cout << "Login to continue" << endl;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    User* user = userManager.login(username, password);

    if (user != nullptr) {
        user->displayMenu();
    }
    else {
        cout << "Invalid username or password." << endl;
    }

    return 0;*/


    UserManager userManager;
    string username, password;

    userManager.addUser("ad", "ad", "ad");

    cout << "Welcome to the Clinic Management System\n";

    // Initial setup: Add an admin user
    if (userManager.login("admin", "admin") == nullptr) {
        cout << "No admin found. Creating default admin account.\n";
        userManager.addUser("admin", "admin", "admin");
    }

    // Login process
    User* loggedInUser = nullptr;
    while (loggedInUser == nullptr) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        loggedInUser = userManager.login(username, password);
        if (loggedInUser == nullptr) {
            cout << "Invalid credentials. Please try again.\n";
        }
    }

    // Display user-specific menu
    loggedInUser->displayMenu();

    return 0;



}




/*

// Existing methods like addPatient, addDoctor, etc.
    // ...

    // Updated methods with logging
    void addPatient() {
        // Existing code for adding patient
        // ...
        addActivityLog("Added a new patient");
    }

    void addDoctor() {
        // Existing code for adding doctor
        // ...
        addActivityLog("Added a new doctor");
    }

    void scheduleAppointment() {
        // Existing code for scheduling appointment
        // ...
        addActivityLog("Scheduled a new appointment");
    }

    // Other updated methods with logging
    // ...

    // Updated Admin and Receptionist classes
// ...

// UserManager class remains the same with minor updates if needed
// ...







*/