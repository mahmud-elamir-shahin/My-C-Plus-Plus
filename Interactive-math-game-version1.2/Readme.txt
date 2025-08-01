Game Title: Math Quiz Game


What is it?

This is a console-based educational math game* built using C++. It challenges players with arithmetic questions (addition, subtraction, multiplication, and division) while incorporating game-like features such as levels, timers, and sound effects.


Main Features:

1. Multiple Game Modes:

   * Single Player (Fully implemented)
   * Two Player Mode (Coming soon)

2. Time Limit per Question:

   * Countdown timer shows remaining time.
   * If time runs out, the question is marked wrong.

3. Levels of Difficulty:

   * Easy → Medium → Hard (auto-progressive)
   * The level increases when the player answers 3 consecutive questions correctly.

4. Multiple Choice Questions (MCQ):

   * Each question provides 4 random options.
   * One correct answer is shuffled among them.

5. Sound Effects and Colors:

   * Green screen and beep for correct answer.
   * Red screen and lower beep for wrong answer or timeout.

6. Scoring and Streak System:

   * 10 points per correct answer.
   * Tracks streaks to level up.

7. High Scores Tracking:

   * Scores saved in `highscores.txt`.
   * Sorted scoreboard shows top 10 players.

8. Division Safety:

   * Prevents division by zero.

9. Settings Menu:

   * Allows adjusting the time limit (5 to 60 seconds).

---

Technologies Used:

* C++ Standard Library
* `<chrono>` for timing
* `<thread>` for concurrent input
* `<windows.h>` for sound and color effects
* File I/O for saving/loading scores


Planned Features:

* Full implementation of Two Player Mode
* Tournament Mode or Challenge Mode.
* Localization (English/Arabic).
* Enhanced question generator (word problems, etc.).
* Player progress profiles.
