#include "FilterSequences.h"
#include "GlobalFunctions.h"
#include "SequenceFunctions.h"
#include <conio.h>
using namespace std;
void FilterSequences() {
    printBanner("sort");
    if (sequences.empty()) {
        centerText("No genetic sequences found.\n\n");
        centerText("Press any key to go back...");
        (void)_getch();
        clear();
        return;
    }

    string input;
    centerText("Sequences:\n");
    for (const auto& seq : sequences) {  //iterates through all of the sequences and prints them on separate lines
        centerText(seq + "\n");
    }

    cout << endl;
    centerText("Sort by: ");
    getline(cin, input);
    formatString(input);  //The function formatString() removes all the spaces from a string and makes it lowercase. It's declared in GlobalFunctions.h
    clear();
    if (input == "back") {
        return;
    }
    printBanner("sort");

    vector<string> matchingSequences;  //creates a new vector for the filtered strings
    filterSequences(input, matchingSequences);

    if (!matchingSequences.empty()) {
        centerText("Matching Sequences:\n");
        for (const auto& seq : matchingSequences) {  //iterates through the whole vector of filtered sequences and prints them on separate lines
            centerText(seq + "\n");
        }
        cout << endl;
        centerText("Press any key to continue...");
        (void)_getch();  //awaits user input, stops the function, and returns the user to the main menu
        clear();
        return;
    }
        centerText("No sequences found!\n\n");  //if the vector of filtered sequences is empty
        centerText("Press any key to continue...");
        (void)_getch();
        clear();
        return;
}