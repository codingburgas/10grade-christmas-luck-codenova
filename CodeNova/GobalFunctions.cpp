#include "GlobalFunctions.h"
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void FullScreen() { // This function is used to fullscreen the program. The centerText() function is entirely reliant on it, given the fact that it needs the width of the console, which is influenced by the resolution
    keybd_event(VK_MENU, 0x36, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void centerText(const string& text) {
    int consoleWidth = getConsoleWidth();
    int paddingLeft = max((consoleWidth - text.length()) / 2, 0);
    cout << string(paddingLeft, ' ') << text;
}