#include "GlobalFunctions.h"
#include "MainMenuFunctions.h"
#include <sstream>
#include <vector>
#include "conio.h"
using namespace std;

stringstream output;
int SelectedGame = 0;

bool displaySequenceTraits = false;

string MenuOptions[4] = {
    "         Generate Sequences         ",
    "          Sort Sequences            ",
    "    Display Sequence Traits: OFF    ",
    "               Exit                 "
};

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
    printBanner("menu");

    char key = 0;

    while (true) {
        output.str("");

        switch (key)
        {
        case(72): //Up arrow key
            SelectedGame--;
            if (SelectedGame < 0) SelectedGame = 3;
            break;

        case(80): //Down arrow key
            SelectedGame++;
            if (SelectedGame >= 4) SelectedGame = 0;
            break;

        case(13): //Enter key
            if (SelectedGame == 0) {
                return GENERATESEQUENCES;    //enum for better readability. declared in GlobalFunctions.h
            }
            else if (SelectedGame == 1) {
                return SORTSEQUENCES;
            }
            else if (SelectedGame == 2) {
                return DISPLAYSEQUENCETRAITS;
            }
            else if (SelectedGame == 3) {
                return EXIT;
            }
            break;
        }

        for (int i = 0; i < 4; i++) {
            if (i == SelectedGame) {  //if the index of the button matches the index of the button the user is on / wants to switch to, it turns blue
                ChangeColor(36);
            }
            PrintMenuOption(MenuOptions[i]);  //prints a button with label [i]
            ChangeColor(37);
        }


        cout << output.str();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, static_cast<SHORT>(menuBanner.size() + 4)});  //^ prints the new buttons ontop of the old ones, essentially overwriting them
        key = _getch();                                                       //  this fixes an issue where everything on the screen disappeared for a split second every time an input was made
    }   
        //^ _getch() is similar to cin.get() but it accepts additional characters and doesn't require the user to press Enter after certain characters                                                           
}       //  part of conio.h
