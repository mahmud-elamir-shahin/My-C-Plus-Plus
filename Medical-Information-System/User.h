#pragma once

#include <string>

using namespace std;

class User
{
protected:
    string username;
    string password;
    string role;

public:
    User(string username, string password, string role) : username(username), password(password), role(role) {}

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getRole() { return role; }

    virtual void displayMenu() = 0;
};

