#include <iostream>
#include <vector>
#include <string>
#include "SequenceFunctions.h"
#include "Windows.h"
#include "GlobalFunctions.h"
#include "GenerateSequences.h"
#include <conio.h>
using namespace std;

void GenerateSequences(vector<string>& sequences) {
    while (true) {
        string traits, sequenceType;
        centerText("Enter trait/s: ");
        getline(cin, traits);
        formatString(traits);
        if (traits == "back") {
            clear();
            return;
        }
        clear();

        centerText("Enter sequence type: ");
        getline(cin, sequenceType);
        formatString(sequenceType);
        if (sequenceType == "back") {
            clear();
            return;
        }
        clear();

        string sequence = generateSequenceByTrait(traits, sequenceType);
        if (sequence == "invalidinput") {
            centerText("Invalid input\n");
            continue;
        }
        sequences.push_back(sequence);
        centerText(sequence + "\n\n");
        centerText("Press any key to continue...");
        (void)_getch();
        clear();
        break;
    }
}