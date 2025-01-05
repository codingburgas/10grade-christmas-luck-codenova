#pragma once
#include <iostream>
#include <string>
#include <vector>

extern std::vector<std::string> sequences;

extern std::vector<std::string> menuBanner;

extern std::vector<std::string> generateBanner;

extern std::vector<std::string> sortBanner;

void clear();

void formatString(std::string& input);

void printBanner(const std::string& banner);

int getConsoleWidth();

void FullScreen();

void centerText(const std::string& text);