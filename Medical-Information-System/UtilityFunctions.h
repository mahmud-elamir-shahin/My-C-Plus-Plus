#pragma once

#pragma warning(disable : 4996)

#include <string>
#include <ctime>
#include <sstream>

using namespace std;

    string getCurrentDateTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
            << 1 + ltm->tm_mon << "-"
            << ltm->tm_mday << " "
            << ltm->tm_hour << ":"
            << ltm->tm_min;
        return ss.str();
    }

    string encryptData(const string& data) {
        string encrypted = data;
        for (char& c : encrypted) {
            c += 3; // Simple Caesar cipher for illustration
        }
        return encrypted;
    }

    string decryptData(const string& data) {
        string decrypted = data;
        for (char& c : decrypted) {
            c -= 3;
        }
        return decrypted;
    }

