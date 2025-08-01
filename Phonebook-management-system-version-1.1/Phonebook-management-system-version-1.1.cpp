// Phonebook-management-system-version-1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Contact {
private:
    string name;
    string phone;
    string email;

public:
    Contact(string n, string p, string e) : name(n), phone(p), email(e) {}

    string getName() const {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    string getPhone() const {
        return phone;
    }

    void setPhone(string p) {
        phone = p;
    }

    string getEmail() const {
        return email;
    }

    void setEmail(string e) {
        email = e;
    }

    friend ostream& operator<<(ostream& os, const Contact& c) {
        os << c.name << " " << c.phone << " " << c.email;
        return os;
    }
};

template<typename T>
class Phonebook {
private:
    vector<T> contacts;

public:
    void addContact(const T& contact) {
        contacts.push_back(contact);
    }

    void removeContact(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(), [name](const T& c) { return c.getName() == name; });
        if (it != contacts.end()) {
            contacts.erase(it);
        }
    }

    const T& findContact(const string& name) const {
        auto it = find_if(contacts.begin(), contacts.end(), [name](const T& c) { return c.getName() == name; });
        if (it != contacts.end()) {
            return *it;
        }
        throw runtime_error("Contact not found");
    }

    void sortContacts() {
        sort(contacts.begin(), contacts.end(), [](const T& c1, const T& c2) { return c1.getName() < c2.getName(); });
    }

    void printContacts() const {
        for (const auto& contact : contacts) {
            cout << contact << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.getName() << "," << contact.getPhone() << "," << contact.getEmail() << endl;
            }
            file.close();
        }
        else {
            throw runtime_error("Error opening file: " + filename);
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    string name = line.substr(0, pos1);
                    string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    string email = line.substr(pos2 + 1);
                    addContact(T(name, phone, email));
                }
            }
            file.close();
        }
        else {
            throw runtime_error("Error opening file: " + filename);
        }
    }
};

int main() {
    Phonebook<Contact> phonebook;

    // Load initial contacts from file
    try {
        phonebook.loadFromFile("contacts.txt");
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }

    while (true) {
        cout << "Phonebook management system:" << endl;
        cout << "1. Add contact" << endl;
        cout << "2. Remove contact" << endl;
        cout << "3. Find contact" << endl;
        cout << "4. Sort contacts" << endl;
        cout << "5. Print contacts" << endl;
        cout << "6. Save contacts to file" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cin >> choice;

        try {
            switch (choice) {
            case 1: {
                string name, phone, email;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone: ";
                cin >> phone;
                cout << "Enter email: ";
                cin >> email;
                phonebook.addContact(Contact(name, phone, email));
                break;
            }
            case 2: {
                string name;
                cout << "Enter name: ";
                cin >> name;
                phonebook.removeContact(name);
                break;
            }
            case 3: {
                string name;
                cout << "Enter name: ";
                cin >> name;
                const Contact& contact = phonebook.findContact(name);
                cout << "Contact found: " << contact << endl;
                break;
            }
            case 4: {
                phonebook.sortContacts();
                cout << "Contacts sorted" << endl;
                break;
            }
            case 5: {
                phonebook.printContacts();
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                phonebook.saveToFile(filename);
                cout << "Contacts saved to file: " << filename << endl;
                break;
            }
            case 7: {
                // Save contacts to file before exiting
                try {
                    phonebook.saveToFile("contacts.txt");
                }
                catch (exception& e) {
                    cerr << e.what() << endl;
                }
                cout << "Exiting phonebook management system" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cerr << e.what() << endl;
        }
    }

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
