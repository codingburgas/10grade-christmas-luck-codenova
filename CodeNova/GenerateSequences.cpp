#include <iostream>
#include <vector>
#include <string>
#include "SequenceFunctions.h"
#include "Windows.h"
#include "GlobalFunctions.h"
#include "GenerateSequences.h"
#include "MainMenuFunctions.h"
#include <conio.h>
using namespace std;

void GenerateSequences(vector<string>& sequences) {
    while (true) {  //this is put in an infinite loop not because it's meant to go on forever, but because it's the easiest way to make the function start over again if the user makes an invalid input without recursion
        string traits, sequenceType;
        centerText("Enter trait/s: ");
        getline(cin, traits);
        formatString(traits);  //The function formatString() removes the spaces from a string and makes it lowercase. It's declared in GlobalFunctions.h
        if (traits == "back") {
            clear();
            return;  //stops the function and returns the user to the main menu
        }
        clear();
        printBanner("generate");
        centerText("Enter sequence type: ");
        getline(cin, sequenceType);
        formatString(sequenceType);
        if (sequenceType == "back") {
            clear();
            return;  //stops the function and returns the user to the main menu
        }
        clear();
        printBanner("generate");

        if (traits.find("hair") != string::npos && traits.substr(traits.find("hair")+4).find("hair") != string::npos) {  //prevents the user from creating an individual with 2 different hair/eye colors at once
            centerText("Invalid input\n\n");
            continue;
        }
        if (traits.find("eyes") != string::npos && traits.substr(traits.find("eyes")+4).find("eyes") != string::npos) {
            centerText("Invalid input\n\n");
            continue;
        }
        if (traits.find("freckles") != string::npos && traits.substr(traits.find("freckles") + 4).find("freckles") != string::npos) {
            centerText("Invalid input\n\n");
            continue;
        }

        string sequence = generateSequenceByTrait(traits, sequenceType);
        if (sequence == "invalidinput") {
            centerText("Invalid input\n\n");  //The function generateSequenceByTrait() returns "invalidinput" if one or more of the traits are not found in the DNA/RNA map
            continue;
        }
        sequences.push_back(sequence);  //Adds the sequence to the main vector of sequences if generated successfully
        centerText(sequence + "\n\n");
        centerText("Press any key to continue...");
        (void)_getch();  //_getch() is similar to cin.get(), but it accepts more characters and, unlike cin.get(), it doesn't require the user to press Enter after certain characters
        clear();
        break;
    }
}