#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>

bool searchInMap(std::map<std::string, std::vector<std::string>> m, const std::string& s1);

int random(int from, int to);

std::string generateSequenceByTrait(const std::string& traits, const std::string& sequenceType);

void filterSequences(const std::string& filters, std::vector<std::string>& matchingSequences);