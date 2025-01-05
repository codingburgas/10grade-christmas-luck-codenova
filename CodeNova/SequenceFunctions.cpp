#include <iostream>
#include <map>
#include <string>
#include <random>
#include <vector>
#include "SequenceFunctions.h"
#include "GlobalFunctions.h"
#include "MainMenuFunctions.h"
using namespace std;

// GLOBAL VARIABLES

map<string, vector<string>> traitsDNA{         // trait-specific codons for each of the sequence types
    {"blackhair", {"GGG", "AGC", "ATT"}},
    {"brownhair", {"ATC", "AAA", "AGG"}},
    {"blueeyes", {"TTT", "ACC", "TCG"}},
    {"browneyes", {"GTA", "AGT", "CCC"}},
    {"freckles", {"CGA", "TGC", "AAT"}}
};

map<string, vector<string>> traitsRNA{
    {"blackhair", {"GGG", "AGC", "AUU"}},
    {"brownhair", {"AUC", "AAA", "AGG"}},
    {"blueeyes", {"UUU", "ACC", "UCG"}},
    {"browneyes", {"GUA", "AGU", "CCC"}},
    {"freckles", {"CGA", "UGC", "AAU"}}
};

// FUNCTIONS
bool searchInMap(map<string, vector<string>> m, const string& s1) {
    for (const auto& strIndex : m) {  //iterates throuch each string in the map..
        for (const auto& vecIndex : strIndex.second) {  //..and then through each vector assigned to it
            if (vecIndex == s1) {
                return true;
            }
        }
    }
    return false;  //if s1 isn't found the function returns false
}

int random(int from, int to) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(from, to);
    return distrib(gen);
}

string generateSequenceByTrait(const string& traits, const string& sequenceType) {
    map<string, vector<string>> traitsDNARNA;  //the value of these varies depending on the sequence type
    char nucleotides[4] = {};
    string sequence;
    string stopCodons[3];

    if (sequenceType == "dna") {
        traitsDNARNA = traitsDNA;
        nucleotides[0] = 'A';
        nucleotides[1] = 'T';
        nucleotides[2] = 'C';
        nucleotides[3] = 'G';

        sequence = "ATG";

        stopCodons[0] = "TAA";
        stopCodons[1] = "TAG";
        stopCodons[2] = "TGA";
    }
    else if (sequenceType == "rna") {
        traitsDNARNA = traitsRNA;
        nucleotides[0] = 'A';
        nucleotides[1] = 'U';
        nucleotides[2] = 'C';
        nucleotides[3] = 'G';

        sequence = "AUG";

        stopCodons[0] = "UAA";
        stopCodons[1] = "UAG";
        stopCodons[2] = "UGA";
    }
    else {  //if the user has made a typo while entering the sequence type the function will return this. there's a check for this in GenerateSequences.cpp
        return "invalidinput";
    }

    size_t pos = 0;
    string traitsStr = traits;
    while (!traitsStr.empty()) {  //goes through each substring between pos and the first found comma (the program assumes that commas separate traits)
        string trait;
        if ((pos = traitsStr.find(',')) != string::npos) {  //makes a temporary string for each word before the first found comma and erases it from the main string
            trait = traitsStr.substr(0, pos);
            traitsStr.erase(0, pos + 1);
        }
        else {  //if there is no comma it does the same but for the whole string
            trait = traitsStr;
            traitsStr.clear();
        }
        if (!traitsDNARNA.count(trait)) {  //if the user has made a typo while entering a trait the function will return this. there's a check for this in GenerateSequences.cpp
            return "invalidinput";
        }

        sequence += traitsDNARNA[trait][random(0, 2)];
        string codon;  //variable for a randomly generated codon
        while (true) {
            for (int i = 0; i < 5; i++) {
                while (true) {
                    codon.clear();
                    for (int j = 0; j < 3; j++) {  //each codon is 3 nucleotides long
                        codon += nucleotides[random(0, 3)];
                    }
                    if (searchInMap(traitsDNARNA, codon) ||  //if the randomly generated codon is found in the trait-specific codons map or matches one of the start/stop codons it's generated again
                        (sequenceType == "DNA" && codon == "ATG") ||
                        (sequenceType == "RNA" && codon == "AUG") ||
                        find(begin(stopCodons), end(stopCodons), codon) != end(stopCodons)) {
                        continue;
                    }
                    break;  //if the codon is unique in that sense it gets added to the sequence
                }
                sequence += codon;
                if (random(0, 1) == 1) {  //50% chance of a trait-specific codon being added to the sequence on each loop
                    sequence += traitsDNARNA[trait][random(0, 2)];
                }
            }
            if (  //in the offchance that the algorithm doesn't generate these a single time, the program regenerates the sequence because the sorting algorithm wouldn't work otherwise
                (sequenceType == "dna" && sequence.find('T') == string::npos) ||
                (sequenceType == "rna" && sequence.find('U') == string::npos)
                ) {
                sequence.clear();
                codon.clear();
                continue;
            }
            break;
        }
    }
    sequence += stopCodons[random(0, 2)];  //a random stop codon is added
    
    if (displaySequenceTraits == true) {
        sequence += " " + traits;  //Outputs the traits of the individual after the sequence. Mainly for debug purposes
    }

    return sequence;
}

void filterSequences(const string& filters, vector<string>& matchingSequences) {
    size_t pos = 0;
    string filterStr = filters;  //uses the same algorithm for going through multiple traits as the function which generates the sequences
    while (!filterStr.empty()) {
        string filter;
        if ((pos = filterStr.find(',')) != string::npos) {
            filter = filterStr.substr(0, pos);
            filterStr.erase(0, pos + 1);
        }
        else {
            filter = filterStr;
            filterStr.clear();
        }

        if (traitsDNA.count(filter)) {
            for (const auto& seq : sequences) {  //iterates through all the sequences
                bool isDNA = seq.find('T') != string::npos;  //the program decides each sequence type based on whether the sequence contains T (Thymine) or U (Uracil)
                const auto& traitCodons = isDNA ? traitsDNA[filter] : traitsRNA[filter]; 
                for (size_t i = 3; i < seq.size(); i += 3) {  //goes through every codon in the sequence
                    if (find(traitCodons.begin(), traitCodons.end(), seq.substr(i, 3)) != traitCodons.end()) {
                        matchingSequences.push_back(seq);
                        break;
                    }
                }
            }
        }
        else {
            centerText("Trait filter \"" + filter + "\" not recognized\n\n");  //the program lets the user know if they entered any filters wrong (and which ones they were) and displays the rest of the found sequences on a separate line
        }
    }
}