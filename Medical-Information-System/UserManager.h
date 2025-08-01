#pragma once

#include  "User.h"
#include  "Admin.h"
#include "Receptionist.h"

class UserManager
{
private:
    map<string, User*> users;

public:
    UserManager() {
        loadUsers();
    }

    ~UserManager() {

        saveUsers();
        for (auto& user : users) {
            delete user.second;
        }
    }

    void loadUsers() {
        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password, role;
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, role, ',');

            if (role == "admin") {
                users[username] = new Admin(username, password);
            }
            else if (role == "receptionist") {
                users[username] = new Receptionist(username, password);
            }
        }
        file.close();
    }

    void saveUsers() {
        ofstream file("users.txt");
        for (const auto& user : users) {
            file << user.second->getUsername() << ","
                << user.second->getPassword() << ","
                << user.second->getRole() << endl;
        }
        file.close();
    }

    User* login(string username, string password) {
        if (users.find(username) != users.end() && users[username]->getPassword() == password) {
            return users[username];
        }
        return nullptr;
    }

    void addUser(string username, string password, string role) {
        if (role == "admin") {
            users[username] = new Admin(username, password);
        }
        else if (role == "receptionist") {
            users[username] = new Receptionist(username, password);
        }
    }
    void removeUser(string username) {
        auto it = users.find(username);
        if (it != users.end()) {
            delete it->second;
            users.erase(it);
        }
    }

    void listUsers() {
        cout << "\nRegistered Users:\n";
        for (const auto& user : users) {
            cout << "Username: " << user.second->getUsername() << ", Role: " << user.second->getRole() << endl;
        }
    }
};

