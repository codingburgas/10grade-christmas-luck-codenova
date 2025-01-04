#pragma once
#include <iostream>
#include <string>
#include <vector>

extern std::vector<std::string> sequences;

void clear();

void formatString(std::string& input);

int getConsoleWidth();

void FullScreen();

void centerText(const std::string& text);