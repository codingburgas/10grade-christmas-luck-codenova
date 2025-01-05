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
    Sleep(200);  //This is essential because the program may print out the main menu before putting the window in fullscreen on some devices and the CenterText() function does not adapt in real time. The value inside the brackets is in miliseconds
    MENU choice;  //MENU is an enum type, declared in MainMenuFunctions.h, and it's also the return type of the ShowMenu() function
    while ((choice = ShowMenu()) != EXIT) {
        clear();
        switch (choice) {
        case GENERATESEQUENCES:
        {
            printBanner("generate");
            GenerateSequences(sequences);
            break;
        }
        case SORTSEQUENCES:
        {
            FilterSequences();
            break;
        }
        case DISPLAYSEQUENCETRAITS:
        {
            if (displaySequenceTraits == false) {  //Displays the traits of the individual after each sequence
                MenuOptions[2] = "    Display Sequence Traits: ON     ";
                displaySequenceTraits = true;
            }
            break;
        }
        };
    }
    return 0;
}