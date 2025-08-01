// Hotel-Management-System-version-1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Room class
class Room {
private:
    int room_number;
    string guest_name;
    bool is_available;
    double price;
public:
    Room(int room_number, double price) {
        this->room_number = room_number;
        this->is_available = true;
        this->price = price;
    }
    int getRoomNumber() {
        return room_number;
    }
    bool isAvailable() {
        return is_available;
    }
    double getPrice() {
        return price;
    }
    void book(string guest_name) {
        this->guest_name = guest_name;
        is_available = false;
    }
    void checkout() {
        guest_name = "";
        is_available = true;
    }
    void setPrice(double price) {
        this->price = price;
    }
    void display() {
        cout << "Room " << room_number << " - ";
        if (is_available) {
            cout << "Available";
        }
        else {
            cout << "Occupied by " << guest_name;
        }
        cout << " - $" << fixed << setprecision(2) << price << " per night" << endl;
    }
    friend class Hotel;
};

// Hotel class
class Hotel {
private:
    string name;
    vector<Room> rooms;
public:
    Hotel(string name, int num_rooms) {
        this->name = name;
        for (int i = 1; i <= num_rooms; i++) {
            Room room(i, 100.0);
            rooms.push_back(room);
        }
    }
    void displayRooms() {
        cout << "Rooms:" << endl;
        for (Room room : rooms) {
            room.display();
        }
        cout << endl;
    }
    void bookRoom(int room_number, string guest_name) {
        for (Room& room : rooms) {
            if (room.getRoomNumber() == room_number && room.isAvailable()) {
                room.book(guest_name);
                cout << "Room " << room_number << " booked by " << guest_name << "." << endl;
                return;
            }
        }
        cout << "Room " << room_number << " is not available." << endl;
    }
    void checkoutRoom(int room_number) {
        for (Room& room : rooms) {
            if (room.getRoomNumber() == room_number && !room.isAvailable()) {
                string guest_name = room.guest_name;
                room.checkout();
                cout << "Room " << room_number << " checked out by " << guest_name << "." << endl;
                return;
            }
        }
        cout << "Room " << room_number << " is not occupied." << endl;
    }
    void setRoomPrice(int room_number, double price) {
        for (Room& room : rooms) {
            if (room.getRoomNumber() == room_number) {
                room.setPrice(price);
                cout << "Room " << room_number << " price updated to $" << fixed << setprecision(2) << price << " per night." << endl;
                return;
            }
        }
        cout << "Room " << room_number << " not found." << endl;
    }
};

int main() {

    int room_number;
    string guest_name;

    Hotel hotel("My Hotel", 5);

    int choice;
    do {
        cout << "1. View rooms" << endl;
        cout << "2. Book a room" << endl;
        cout << "3. Checkout a room" << endl;
        cout << "4. Set room price" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hotel.displayRooms();
            break;
        case 2:
            cout << "Enter the room number: ";
            cin >> room_number;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, guest_name);
            hotel.bookRoom(room_number, guest_name);
            break;
        case 3:
            cout << "Enter the room number to checkout: ";
            cin >> room_number;
            hotel.checkoutRoom(room_number);
            break;
        case 4:
            double price;
            cout << "Enter the room number to set price: ";
            cin >> room_number;
            cout << "Enter the new price: ";
            cin >> price;
            hotel.setRoomPrice(room_number, price);
            break;
        case 5:
            cout << "Exiting the system..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

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
