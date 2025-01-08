#include "GlobalFunctions.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Windows.h"
using namespace std;

vector<string> sequences;

vector<string> menuBanner = {  //ASCII art
"  __  __       _         __  __                  ",
" |  \\/  |     (_)       |  \\/  |                 ",
" | \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _ ",
" | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |",
" | |  | | (_| | | | | | | |  | |  __/ | | | |_| |",
"   |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n\n"
};

vector<string> generateBanner = {
R"(   _____                           _      )",
R"(  / ____|                         | |     )",
R"( | |  __  ___  _ __   ___ _ __ __ _| |_ ___)",
R"( | | |_ |/ _ \| '_ \ / _ \ '__/ _` | __/ _ \)",
R"( | |__| |  __/ | | |  __/ | | (_| | ||  __/)",
R"(  \_____|\___|_| |_|\___|_|  \__,_|\__\___|)",
};

vector<string> sortBanner = {
R"(   _____            _   )",
R"(  / ____|          | |  )",
R"( | (___   ___  _ __| |_ )",
R"(  \___ \ / _ \| '__| __|)",
R"(  ____) | (_) | |  | |_ )",
R"( |_____/ \___/|_|   \__|)"
};

void clear() {
#ifdef _WIN32
    system("cls"); //Windows-specific clear
#elif __linux__ || __APPLE__
    system("clear"); //Linux and macOS-specific clear
#endif
}

void formatString(string& input) {
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    transform(input.begin(), input.end(), input.begin(), ::tolower);
}

void printBanner(const string& banner) {
    if (banner == "menu") {
        for (string line : menuBanner) {  //iterates through each line of the ascii art and centers it using our function
            centerText(line + "\n");
        }
    }
    else if (banner == "generate") {
        for (string line : generateBanner) {  //iterates through each line of the ascii art and centers it using our function
            centerText(line + "\n");
        }
    }
    else if (banner == "sort") {
        for (string line : sortBanner) {  //iterates through each line of the ascii art and centers it using our function
            centerText(line + "\n");
        }
    }
    cout << "\n\n";
}

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return 160; //Return a default value if the function fails
    }
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void FullScreen() {  //This function is used to fullscreen the program. The centerText() function is entirely reliant on it, given the fact that it needs the width of the console, which is influenced by the resolution
    keybd_event(VK_MENU, 0x36, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);  //It works by making keyboard inputs for the user
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void centerText(const string& text) {
    int consoleWidth = getConsoleWidth();
    if (consoleWidth <= 0) {
        consoleWidth = 160; //Fall back to the default width
    }

    int paddingLeft = max((consoleWidth - (int)text.length()) / 2, 0);
    cout << string(paddingLeft, ' ') << text;
}