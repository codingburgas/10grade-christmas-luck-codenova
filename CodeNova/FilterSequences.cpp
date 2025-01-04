#include "FilterSequences.h"
#include "GlobalFunctions.h"
#include "SequenceFunctions.h"
#include <conio.h>
using namespace std;
void FilterSequences() {
    if (sequences.empty()) {
        centerText("No genetic sequences found.\n\n");
        centerText("Press any key to go back...");
        (void)_getch();
        clear();
        return;
    }

    string input;
    centerText("Sequences:\n");
    for (const auto& seq : sequences) {
        centerText(seq + "\n");
    }

    cout << endl;
    centerText("Sort by: ");
    getline(cin, input);
    formatString(input);
    clear();

    vector<string> matchingSequences;
    filterSequences(input, matchingSequences);

    if (!matchingSequences.empty()) {
        centerText("Matching Sequences:\n");
        for (const auto& seq : matchingSequences) {
            centerText(seq + "\n");
        }
        cout << endl;
        centerText("Press any key to continue...");
        (void)_getch();
        clear();
        return;
    }
        centerText("No sequences found!\n\n");
        centerText("Press any key to continue...");
        (void)_getch();
        clear();
        return;
}