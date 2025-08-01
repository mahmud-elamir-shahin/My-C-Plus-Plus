// Stone-Paper-Scissors-Game-Version-1.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Player2 = 2, Computer = 3, Draw = 4 };

string Emoji(enGameChoice choice) {
    string emojis[3] = { "\U0001FAA8", "\U0001F4C4", "\u2702" }; 
    return emojis[choice - 1];
}

string ChoiceName(enGameChoice choice) {
    string names[3] = { "Stone", "Paper", "Scissors" };
    return names[choice - 1] + " " + Emoji(choice);
}

enGameChoice ReadPlayerChoice(string playerName) {
    short choice;
    do {
        cout << playerName << " - Choose: [1] Stone 🪨, [2] Paper 📄, [3] Scissors ✂: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }
    } while (choice < 1 || choice > 3);
    return (enGameChoice)choice;
}

enGameChoice GetComputerChoice(string difficulty, enGameChoice lastPlayerChoice) {
    transform(difficulty.begin(), difficulty.end(), difficulty.begin(), ::tolower);
    if (difficulty == "hard") {
        int strategy = rand() % 4;
        if (strategy <= 1) {
            switch (lastPlayerChoice) {
            case Stone: return Paper;
            case Paper: return Scissors;
            case Scissors: return Stone;
            }
        }
        else if (strategy == 2) {
            return lastPlayerChoice;
        }
    }
    return (enGameChoice)(rand() % 3 + 1);
}

enWinner GetRoundWinner(enGameChoice p1, enGameChoice p2, bool vsComputer) {
    if (p1 == p2) return Draw;
    if ((p1 == Stone && p2 == Scissors) || (p1 == Paper && p2 == Stone) || (p1 == Scissors && p2 == Paper))
        return Player1;
    return vsComputer ? Computer : Player2;
}

void SetColorByWinner(enWinner winner, bool vsComputer) {
#ifdef _WIN32
    if (winner == Draw)
        system("color 6F");
    else if ((winner == Player1) || (!vsComputer && winner == Player2))
        system("color 2F");
    else {
        system("color 4F");
        cout << "\a";
    }
#endif
}

void PrintRoundResult(string name1, string name2, enGameChoice p1, enGameChoice p2, enWinner winner) {
    SetColorByWinner(winner, name2 == "Computer");
    cout << "\n================ Round Result ================\n";
    cout << name1 << " chose: " << ChoiceName(p1) << endl;
    cout << name2 << " chose: " << ChoiceName(p2) << endl;
    if (winner == Draw) cout << "Result: Draw!\n";
    else cout << "Winner: " << (winner == Player1 ? name1 : name2) << "!\n";
    cout << "==============================================\n\n";
}

void ShowStats(int p1Wins, int p2Wins, int draws, string name1, string name2) {
    int total = p1Wins + p2Wins + draws;
    auto percent = [](int count, int total) -> double {
        return total == 0 ? 0.0 : (count * 100.0 / total);
        };
    cout << "\n====== Stats ======\n";
    cout << name1 << " Wins: " << p1Wins << " (" << percent(p1Wins, total) << "%)\n";
    cout << name2 << " Wins: " << p2Wins << " (" << percent(p2Wins, total) << "%)\n";
    cout << "Draws   : " << draws << " (" << percent(draws, total) << "%)\n";
    cout << "===================\n";
}

void SaveHighScore(string playerName, int score) {
    ifstream in("highscore.txt");
    string name;
    int maxScore = 0;
    in >> name >> maxScore;
    in.close();

    if (score > maxScore) {
        ofstream out("highscore.txt");
        out << playerName << " " << score;
        out.close();
        cout << "\n\U0001F389 New High Score by " << playerName << "! Score: " << score << " \U0001F389\n";
    }
    else {
        cout << "\nCurrent High Score: " << name << " - " << maxScore << "\n";
    }
}

void PlayGame(bool vsComputer) {
    string player1, player2;
    cout << "Enter Player 1 Name: ";
    cin >> player1;

    string difficulty = "easy";
    if (vsComputer) {
        do {
            cout << "Choose difficulty [easy/hard]: ";
            cin >> difficulty;
            transform(difficulty.begin(), difficulty.end(), difficulty.begin(), ::tolower);
        } while (difficulty != "easy" && difficulty != "hard");
        player2 = "Computer";
    }
    else {
        cout << "Enter Player 2 Name: ";
        cin >> player2;
    }

    int p1Wins = 0, p2Wins = 0, draws = 0;
    char playMore = 'Y';
    enGameChoice lastPlayerChoice = Stone;

    while (toupper(playMore) == 'Y') {
        enGameChoice p1Choice = ReadPlayerChoice(player1);
        enGameChoice p2Choice = vsComputer ? GetComputerChoice(difficulty, p1Choice) : ReadPlayerChoice(player2);
        enWinner winner = GetRoundWinner(p1Choice, p2Choice, vsComputer);

        if (winner == Player1) p1Wins++;
        else if (winner == Player2 || winner == Computer) p2Wins++;
        else draws++;

        PrintRoundResult(player1, player2, p1Choice, p2Choice, winner);
        ShowStats(p1Wins, p2Wins, draws, player1, player2);

        cout << "Play another round? [Y/N]: ";
        cin >> playMore;
        lastPlayerChoice = p1Choice;
    }

    if (vsComputer)
        SaveHighScore(player1, p1Wins);
#ifdef _WIN32
    system("color 0F");
#endif
}

int main() {
    srand((unsigned)time(0));
    int mode;
    do {
        cout << "\nChoose Game Mode:\n[1] Player vs Computer\n[2] Player vs Player\nEnter choice: ";
        cin >> mode;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            mode = 0;
        }
    } while (mode != 1 && mode != 2);

    PlayGame(mode == 1);
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
