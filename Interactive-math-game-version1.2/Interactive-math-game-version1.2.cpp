// Interactive-math-game-version1.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <atomic>
#include <string>
using namespace std;
using namespace std::chrono;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3 };
string GetOpTypeSymbol(int op) {
    switch (op) {
    case 1: return "+";
    case 2: return "-";
    case 3: return "*";
    case 4: return "/";
    default: return "?";
    }
}

struct stQuestion {
    int Number1;
    int Number2;
    int Operation;
    int CorrectAnswer;
    int Options[4];
    bool IsCorrect = false;
};

struct stPlayer {
    string Name;
    int Score = 0;
    int CorrectStreak = 0;
    enQuestionsLevel Level = EasyLevel;
};

int TIME_LIMIT = 15;

int GenerateNumber(enQuestionsLevel level) {
    switch (level) {
    case EasyLevel: return rand() % 10 + 1;
    case MedLevel: return rand() % 40 + 10;
    case HardLevel: return rand() % 100 + 50;
    default: return rand() % 10 + 1;
    }
}

stQuestion GenerateQuestion(enQuestionsLevel level) {
    stQuestion q;
    q.Number1 = GenerateNumber(level);
    q.Number2 = GenerateNumber(level);
    q.Operation = rand() % 4 + 1;

    if (q.Operation == 4 && q.Number2 == 0) q.Number2 = 1;

    switch (q.Operation) {
    case 1: q.CorrectAnswer = q.Number1 + q.Number2; break;
    case 2: q.CorrectAnswer = q.Number1 - q.Number2; break;
    case 3: q.CorrectAnswer = q.Number1 * q.Number2; break;
    case 4: q.CorrectAnswer = q.Number1 / q.Number2; break;
    }

    q.Options[0] = q.CorrectAnswer;
    for (int i = 1; i < 4; ++i)
        q.Options[i] = q.CorrectAnswer + (rand() % 10 - 5);

    random_shuffle(begin(q.Options), end(q.Options));
    return q;
}

void PlayCorrectSound() {
    Beep(1000, 200);
}

void PlayWrongSound() {
    Beep(400, 500);
}

void SetScreenColor(bool Right) {
    if (Right) system("color 2F");
    else system("color 4F");
}

void AskQuestion(stPlayer& player, stQuestion& q, int qNum, int totalQ) {
    cout << "\nQuestion [" << qNum << "/" << totalQ << "]\n";
    cout << q.Number1 << " " << GetOpTypeSymbol(q.Operation) << " " << q.Number2 << " = ?\n";
    for (int i = 0; i < 4; ++i)
        cout << "[" << i + 1 << "] " << q.Options[i] << "  ";

    cout << "\n(You have " << TIME_LIMIT << " seconds to answer)\n";
    cout << "Answer (1-4): ";

    auto start = steady_clock::now();
    int ans = -1;
    atomic<bool> answered{ false };

    thread inputThread([&]() {
        cin >> ans;
        answered = true;
        });

    for (int i = TIME_LIMIT; i > 0; --i) {
        if (answered) break;
        cout << "\rTime left: " << setw(2) << i << "s ";
        cout.flush();
        this_thread::sleep_for(seconds(1));
    }

    if (!answered) {
        cout << "\n⏰ Time's up!\n";
        ans = -1;
    }

    if (inputThread.joinable()) inputThread.join();

    auto end = steady_clock::now();
    int timeTaken = duration_cast<seconds>(end - start).count();

    if (ans >= 1 && ans <= 4 && q.Options[ans - 1] == q.CorrectAnswer && timeTaken <= TIME_LIMIT) {
        q.IsCorrect = true;
        player.Score += 10;
        player.CorrectStreak++;
        PlayCorrectSound();
        cout << "\n✅ Correct!\n";
    }
    else {
        q.IsCorrect = false;
        player.CorrectStreak = 0;
        PlayWrongSound();
        cout << "\n❌ Wrong or Timeout! Correct answer was: " << q.CorrectAnswer << "\n";
    }

    if (player.CorrectStreak >= 3 && player.Level != HardLevel) {
        player.Level = (enQuestionsLevel)(player.Level + 1);
        cout << "🔥 You leveled up to " << (player.Level == MedLevel ? "Medium" : "Hard") << "!\n";
    }
    SetScreenColor(q.IsCorrect);
}

int ReadInt(string msg, int min, int max) {
    int val;
    do {
        cout << msg;
        cin >> val;
    } while (val < min || val > max);
    return val;
}

void SaveScore(stPlayer player) {
    ofstream file("highscores.txt", ios::app);
    if (file.is_open()) {
        file << player.Name << "," << player.Score << endl;
        file.close();
    }
}

void ShowHighScores() {
    ifstream file("highscores.txt");
    vector<pair<string, int>> scores;
    string name;
    int score;
    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos) {
            name = line.substr(0, comma);
            score = stoi(line.substr(comma + 1));
            scores.push_back({ name, score });
        }
    }
    sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });
    cout << "\n=== Scoreboard ===\n";
    for (size_t i = 0; i < scores.size() && i < 10; ++i) {
        cout << i + 1 << ". " << scores[i].first << " - " << scores[i].second << endl;
    }
}

void SinglePlayerMode() {
    stPlayer player;
    cout << "\nEnter your name: ";
    cin >> player.Name;
    for (int i = 1; i <= 10; ++i) {
        stQuestion q = GenerateQuestion(player.Level);
        AskQuestion(player, q, i, 10);
    }
    cout << "\nGame Over! Your Score: " << player.Score << endl;
    SaveScore(player);
}

void MainMenu() {
    srand(time(0));
    char again;
    do {
        system("cls");
        cout << "===== Math Quiz Game =====\n";
        cout << "[1] Single Player\n[2] Two Players\n[3] Show Scoreboard\n[4] Set Time Limit\n[5] Exit\nChoose: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: SinglePlayerMode(); break;
        case 2: cout << "Coming soon...\n"; break;
        case 3: ShowHighScores(); break;
        case 4: TIME_LIMIT = ReadInt("Enter new time limit in seconds (5-60): ", 5, 60); break;
        case 5: return;
        default: cout << "Invalid!\n";
        }
        cout << "\nPlay Again? (Y/N): "; cin >> again;
    } while (again == 'Y' || again == 'y');
}

int main() {
    MainMenu();
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
