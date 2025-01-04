#include <iostream>
#include <string>
#include <vector>
#include "GlobalFunctions.h"
#include "MainMenuFunctions.h"
#include "GenerateSequences.h"
#include "FilterSequences.h"
using namespace std;

int main() {
    FullScreen();
    Sleep(200);
    MENU choice;
    while ((choice = ShowMenu()) != EXIT) {
        clear();
        if (choice == GENERATESEQUENCES) {
            GenerateSequences(sequences);
        }
        else if (choice == SORTSEQUENCES) {
            FilterSequences();
        }
    }
    return 0;
}
