// Simple-Banke-System-Version-1.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Account class
class Account {
private:
    int id;
    string name;
    double balance;
public:
    Account(int id, string name, double balance) {
        this->id = id;
        this->name = name;
        this->balance = balance;
    }
    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    double getBalance() {
        return balance;
    }
    void deposit(double amount) {
        balance += amount;
    }
    void withdraw(double amount) {
        balance -= amount;
    }
};

// Bank class
class Bank {
private:
    vector<Account> accounts;
public:
    void addAccount(Account account) {
        accounts.push_back(account);
    }
    void displayAccounts() {
        cout << "Accounts:" << endl;
        for (Account account : accounts) {
            cout << "ID: " << account.getId() << ", Name: " << account.getName() << ", Balance: $" << account.getBalance() << endl;
        }
        cout << endl;
    }
    void deposit(int id, double amount) {
        for (Account& account : accounts) {
            if (account.getId() == id) {
                account.deposit(amount);
                cout << "Deposit of $" << amount << " successful for account ID " << id << "." << endl;
                return;
            }
        }
        cout << "Account with ID " << id << " not found." << endl;
    }
    void withdraw(int id, double amount) {
        for (Account& account : accounts) {
            if (account.getId() == id) {
                if (account.getBalance() < amount) {
                    cout << "Withdrawal of $" << amount << " failed for account ID " << id << " due to insufficient balance." << endl;
                }
                else {
                    account.withdraw(amount);
                    cout << "Withdrawal of $" << amount << " successful for account ID " << id << "." << endl;
                }
                return;
            }
        }
        cout << "Account with ID " << id << " not found." << endl;
    }
    void searchByName(string name) {
        vector<Account> results;
        for (Account account : accounts) {
            if (account.getName() == name) {
                results.push_back(account);
            }
        }
        if (results.size() == 0) {
            cout << "No accounts found for name " << name << "." << endl;
        }
        else {
            cout << "Accounts found for name " << name << ":" << endl;
            for (Account account : results) {
                cout << "ID: " << account.getId() << ", Name: " << account.getName() << ", Balance: $" << account.getBalance() << endl;
            }
        }
        cout << endl;
    }
    void sortById() {
        sort(accounts.begin(), accounts.end(), [](Account a, Account b) {
            return a.getId() < b.getId();
            });
        cout << "Accounts sorted by ID." << endl;
    }
    void sortByBalance() {
        sort(accounts.begin(), accounts.end(), [](Account a, Account b) {
            return a.getBalance() > b.getBalance();
            });
        cout << "Accounts sorted by balance." << endl;
    }
    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (Account account : accounts) {
                file << account.getId() << "," << account.getName() << "," << account.getBalance() << endl;
            }
            cout << "Accounts saved to file " << filename << "." << endl;
        }
        else {
            cout << "Failed to open file " << filename << "." << endl;
        }
        file.close();
    }
    void loadFromFile(string filename) {
        ifstream file(filename);
        if (file.is_open()) {
            accounts.clear();
            string line;
            while (getline(file, line)) {
                int id;
                string name;
                double balance;
                sscanf_s(line.c_str(), "%d,%[^,],%lf", &id, &name[0], &balance);
                Account account(id, name, balance);
                accounts.push_back(account);
            }
            cout << "Accounts loaded from file " << filename << "." << endl;
        }
        else {
            cout << "Failed to open file " << filename << "." << endl;
        }
        file.close();
    }
};

int main() {
    Bank bank;

    // Load accounts from file
    bank.loadFromFile("accounts.txt");

    int choice;
    do {
        cout << "1. Display accounts" << endl;
        cout << "2. Add account" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. Search by name" << endl;
        cout << "6. Sort by ID" << endl;
        cout << "7. Sort by balance" << endl;
        cout << "8. Save to file" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            bank.displayAccounts();
            break;
        case 2: {
            int id;
            string name;
            double balance;
            cout << "Enter account ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter account name: ";
            getline(cin, name);
            cout << "Enter account balance: $";
            cin >> balance;
            Account account(id, name, balance);
            bank.addAccount(account);
            cout << "Account added." << endl;
            break;
        }
        case 3: {
            int id;
            double amount;
            cout << "Enter account ID: ";
            cin >> id;
            cout << "Enter deposit amount: $";
            cin >> amount;
            bank.deposit(id, amount);
            break;
        }
        case 4: {
            int id;
            double amount;
            cout << "Enter account ID: ";
            cin >> id;
            cout << "Enter withdrawal amount: $";
            cin >> amount;
            bank.withdraw(id, amount);
            break;
        }
        case 5: {
            string name;
            cout << "Enter name to search for: ";
            cin.ignore();
            getline(cin, name);
            bank.searchByName(name);
            break;
        }
        case 6:
            bank.sortById();
            break;
        case 7:
            bank.sortByBalance();
            break;
        case 8: {
            string filename;
            cout << "Enter filename to save to: ";
            cin >> filename;
            bank.saveToFile(filename);
            break;
        }
        case 9:
            // Save accounts to file before exiting
            bank.saveToFile("accounts.txt");
            break;
        default:
            cout << "Invalid choice." << endl;
        }
        cout << endl;
    } while (choice != 9);

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
