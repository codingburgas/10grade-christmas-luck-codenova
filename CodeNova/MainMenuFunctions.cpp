#include "GlobalFunctions.h"
#include "MainMenuFunctions.h"
#include <sstream>
#include "conio.h"
using namespace std;
stringstream output;

void ChangeColor(int Color) {
    output << "\033[" << Color << "m";
}

void PrintMenuOption(const string& Option) {
    int padding = (getConsoleWidth() - 38) / 2;
    output << string(padding, ' ') << char(201) << string(36, char(205)) << char(187) << endl;
    output << string(padding, ' ') << char(186) << string(36, ' ') << char(186) << endl;
    output << string(padding, ' ') << char(186) << Option << char(186) << endl;
    output << string(padding, ' ') << char(186) << string(36, ' ') << char(186) << endl;
    output << string(padding, ' ') << char(200) << string(36, char(205)) << char(188) << "\n\n";
}

MENU ShowMenu() {
    string MenuOptions[3] = {
        "         Generate Sequences         ",
        "          Sort Sequences            ",
        "               Exit                 "
    };

    int SelectedGame = 0;
    char key = 0;

    while (true) {
        output.str("");

        switch (key)
        {
        case(72): //up arrow key
            SelectedGame--;
            if (SelectedGame < 0) SelectedGame = 2;
            break;

        case(80): //Down arrow key
            SelectedGame++;
            if (SelectedGame >= 3) SelectedGame = 0;
            break;

        case(13): // Enter key
            if (SelectedGame == 0) {
                return GENERATESEQUENCES;
            }
            else if (SelectedGame == 1) {
                return SORTSEQUENCES;
            }
            else if (SelectedGame == 2) {
                return EXIT;
            }
            break;
        }

        for (int i = 0; i < 3; i++) {
            if (i == SelectedGame) {
                ChangeColor(36);
            }
            PrintMenuOption(MenuOptions[i]);
            ChangeColor(37);
        }


        cout << output.str();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
        key = _getch();
    }
}
