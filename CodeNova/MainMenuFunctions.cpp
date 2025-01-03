#include "GlobalFunctions.h"
#include "MainMenuFunctions.h";
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

void ChangeColor(HANDLE Output, int Color) {
    SetConsoleTextAttribute(Output, Color);
}

void PrintMenuOption(const string& Option) {
    int padding = (getConsoleWidth() - 38) / 2;
    cout << string(padding, ' ') << char(201) << string(36, char(205)) << char(187) << endl;
    cout << string(padding, ' ') << char(186) << string(36, ' ') << char(186) << endl;
    cout << string(padding, ' ') << char(186) << Option << char(186) << endl;
    cout << string(padding, ' ') << char(186) << string(36, ' ') << char(186) << endl;
    cout << string(padding, ' ') << char(200) << string(36, char(205)) << char(188) << "\n\n";
}

void ShowMenu() {
    string MenuOptions[3] = {
        "         Generate Sequences         ",
        "          Sort Sequences            ",
        "               Exit                 "
    };

    bool timetochoose = true;
    bool firstTimeRun = true;
    int SelectedGame = 0;

    while (timetochoose) {
        if (firstTimeRun) {
            FullScreen();
            firstTimeRun = false;
        }
        system("cls");
        for (int i = 0; i < 3; i++) {
            if (i == SelectedGame) {
                ChangeColor(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
            PrintMenuOption(MenuOptions[i]);
            ChangeColor(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }

        char key = _getch();
        if (key == 72) { // Up arrow key
            SelectedGame = (SelectedGame - 1 + 3) % 3;
        }
        else if (key == 80) { // Down arrow key
            SelectedGame = (SelectedGame + 1) % 3;
        }
        else if (key == 13) { // Enter key
            timetochoose = false; // Exit loop for now (functionality TBD)
        }
    }
}