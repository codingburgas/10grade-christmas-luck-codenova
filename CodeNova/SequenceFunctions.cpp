#include <iostream>
#include <map>
#include <string>
#include <random>
#include <vector>
#include "SequenceFunctions.h"
#include "GlobalFunctions.h"
using namespace std;

// GLOBAL VARIABLES

map<string, vector<string>> traitsDNA{
    {"blackhair", {"GGG", "AGC", "ATT"}},
    {"brownhair", {"ATC", "AAA", "AGG"}},
    {"blueeyes", {"TTT", "ACC", "TCG"}},
    {"browneyes", {"GTA", "AGT", "CCC"}}
};

map<string, vector<string>> traitsRNA{
    {"blackhair", {"GGG", "AGC", "AUU"}},
    {"brownhair", {"AUC", "AAA", "AGG"}},
    {"blueeyes", {"UUU", "ACC", "UCG"}},
    {"browneyes", {"GUA", "AGU", "CCC"}}
};

// FUNCTIONS
bool searchInMap(map<string, vector<string>> m, const string& s1) {
    for (const auto& strIndex : m) {
        for (const auto& vecIndex : strIndex.second) {
            if (vecIndex == s1) {
                return true;
            }
        }
    }
    return false;
}

int random(int from, int to) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(from, to);
    return distrib(gen);
}

string generateSequenceByTrait(const string& traits, const string& sequenceType) {
    map<string, vector<string>> traitsDNARNA;
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
    else {
        return "invalidinput";
    }

    size_t pos = 0;
    string traitsStr = traits;
    while (!traitsStr.empty()) {
        string trait;
        if ((pos = traitsStr.find(',')) != string::npos) {
            trait = traitsStr.substr(0, pos);
            traitsStr.erase(0, pos + 1);
        }
        else {
            trait = traitsStr;
            traitsStr.clear();
        }
        if (!traitsDNARNA.count(trait)) {
            return "invalidinput";
        }

        sequence += traitsDNARNA[trait][random(0, 2)];
        string codon;
        for (int i = 0; i < 5; i++) {
            while (true) {
                codon.clear();
                for (int j = 0; j < 3; j++) {
                    codon += nucleotides[random(0, 3)];
                }
                if (searchInMap(traitsDNARNA, codon) ||
                    (sequenceType == "DNA" && codon == "ATG") ||
                    (sequenceType == "RNA" && codon == "AUG") ||
                    find(begin(stopCodons), end(stopCodons), codon) != end(stopCodons)) {
                    continue;
                }
                break;
            }
            sequence += codon;
            if (random(0, 1) == 1) {
                sequence += traitsDNARNA[trait][random(0, 2)];
            }
        }
    }
    sequence += stopCodons[random(0, 2)];

#define testSequences
#ifdef testSequences
    sequence += " " + traits;          //Outputs the traits of the individual after the sequence
#endif

    return sequence;
}

void filterSequences(const string& filters, vector<string>& matchingSequences) {
    size_t pos = 0;
    string filterStr = filters;
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
            for (const auto& seq : sequences) {
                bool isDNA = seq.find('T') != string::npos;
                const auto& traitCodons = isDNA ? traitsDNA[filter] : traitsRNA[filter];
                for (size_t i = 3; i < seq.size(); i += 3) {
                    if (find(traitCodons.begin(), traitCodons.end(), seq.substr(i, 3)) != traitCodons.end()) {
                        matchingSequences.push_back(seq);
                        break;
                    }
                }
            }
        }
        else {
            centerText("Trait filter \"" + filter + "\" not recognized\n");
        }
    }
}