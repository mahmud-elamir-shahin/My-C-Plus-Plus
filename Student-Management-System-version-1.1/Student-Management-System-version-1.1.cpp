// Student-Management-System-version-1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Define a structure to represent a student record
struct Student {
    string name;
    string id;
    string address;
    string phone;
    string email;
    vector<double> grades;
    double gpa;
};

// Function prototypes
void addStudent(vector<Student>& students);
void editStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);
void enterGrades(vector<Student>& students);
void calculateGPA(vector<Student>& students);
void generateReport(vector<Student>& students);
void searchStudent(vector<Student>& students);
void saveData(vector<Student>& students);
void loadData(vector<Student>& students);

int main() {
    vector<Student> students;
    loadData(students);

    int choice;
    do {
        cout << "Student Management System\n";
        cout << "-------------------------\n";
        cout << "1. Add Student\n";
        cout << "2. Edit Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Enter Grades\n";
        cout << "5. Calculate GPA\n";
        cout << "6. Generate Report\n";
        cout << "7. Search Student\n";
        cout << "8. Save Data\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(students);
            break;
        case 2:
            editStudent(students);
            break;
        case 3:
            deleteStudent(students);
            break;
        case 4:
            enterGrades(students);
            break;
        case 5:
            calculateGPA(students);
            break;
        case 6:
            generateReport(students);
            break;
        case 7:
            searchStudent(students);
            break;
        case 8:
            saveData(students);
            break;
        case 9:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}

void addStudent(vector<Student>& students) {
    Student student;
    cout << "Enter student name: ";
    getline(cin.ignore(), student.name);
    cout << "Enter student ID: ";
    getline(cin, student.id);
    cout << "Enter student address: ";
    getline(cin, student.address);
    cout << "Enter student phone: ";
    getline(cin, student.phone);
    cout << "Enter student email: ";
    getline(cin, student.email);
    students.push_back(student);
    cout << "Student added successfully.\n";
}

void editStudent(vector<Student>& students) {
    string id;
    cout << "Enter ID of student to edit: ";
    getline(cin.ignore(), id);

    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            cout << "Enter new student name: ";
            getline(cin, students[i].name);
            cout << "Enter new student address: ";
            getline(cin, students[i].address);
            cout << "Enter new student phone: ";
            getline(cin, students[i].phone);
            cout << "Enter new student email: ";
            getline(cin, students[i].email);
            cout << "Student edited successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

void deleteStudent(vector<Student>& students) {
    string id;
    cout << "Enter ID of student to delete: ";
    getline(cin.ignore(), id);

    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            cout << "Student deleted successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

void enterGrades(vector<Student>& students) {
    string id;
    cout << "Enter ID of student to enter grades: ";
    getline(cin.ignore(), id);

    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            int numGrades;
            cout << "Enter number of grades to enter: ";
            cin >> numGrades;
            students[i].grades.clear();
            for (int j = 0; j < numGrades; j++) {
                double grade;
                cout << "Enter grade " << j + 1 << ": ";
                cin >> grade;
                students[i].grades.push_back(grade);
            }
            cout << "Grades entered successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

void calculateGPA(vector<Student>& students) {
    for (int i = 0; i < students.size(); i++) {
        double total = 0;
        for (int j = 0; j < students[i].grades.size(); j++) {
            total += students[i].grades[j];
        }
        students[i].gpa = total / students[i].grades.size();
    }
    cout << "GPAs calculated successfully.\n";
}

void generateReport(vector<Student>& students) {
    cout << left << setw(20) << "Name" << setw(10) << "ID" << setw(20) << "Address" << setw(15) << "Phone" << setw(25) << "Email" << setw(10) << "GPA" << endl;
    cout << "----------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < students.size(); i++) {
        cout << left << setw(20) << students[i].name << setw(10) << students[i].id << setw(20) << students[i].address << setw(15) << students[i].phone << setw(25) << students[i].email << setw(10) << fixed << setprecision(2) << students[i].gpa << endl;
    }
}

void searchStudent(vector<Student>& students) {
    string search;
    cout << "Enter search term: ";
    getline(cin.ignore(), search);

    cout << left << setw(20) << "Name" << setw(10) << "ID" << setw(20) << "Address" << setw(15) << "Phone" << setw(25) << "Email" << setw(10) << "GPA" << endl;
    cout << "----------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < students.size(); i++) {
        if (students[i].name.find(search) != string::npos || students[i].id.find(search) != string::npos || students[i].address.find(search) != string::npos || students[i].phone.find(search) != string::npos || students[i].email.find(search) != string::npos) {
            cout << left << setw(20) << students[i].name << setw(10) << students[i].id << setw(20) << students[i].address << setw(15) << students[i].phone << setw(25) << students[i].email << setw(10) << fixed << setprecision(2) << students[i].gpa << endl;
        }
    }
}

void saveData(vector<Student>& students) {
    ofstream outFile("students.txt");

    for (int i = 0; i < students.size(); i++) {
        outFile << students[i].name << ",";
        outFile << students[i].id << ",";
        outFile << students[i].address << ",";
        outFile << students[i].phone << ",";
        outFile << students[i].email << ",";
        for (int j = 0; j < students[i].grades.size(); j++) {
            outFile << students[i].grades[j] << ",";
        }
        outFile << students[i].gpa << endl;
    }

    outFile.close();
    cout << "Data saved successfully.\n";
}

void loadData(vector<Student>& students) {
    ifstream inFile("students.txt");
    if (!inFile.is_open()) {
        cout << "Data file not found.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        Student student;
        size_t pos = 0;
        string token;
        while ((pos = line.find(",")) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);
            if (student.name.empty()) {
                student.name = token;
            }
            else if (student.id.empty()) {
                student.id = token;
            }
            else if (student.address.empty()) {
                student.address = token;
            }
            else if (student.phone.empty()) {
                student.phone = token;
            }
            else if (student.email.empty()) {
                student.email = token;
            }
            else if (line.find(",") != string::npos) {
                student.grades.push_back(stod(token));
            }
            else {
                student.gpa = stod(token);
            }
        }
        students.push_back(student);
    }

    inFile.close();
    cout << "Data loaded successfully.\n";
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
