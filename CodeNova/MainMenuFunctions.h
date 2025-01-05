#pragma once
#include <iostream>
#include "Windows.h"
#include <string>

extern std::string MenuOptions[4];

extern bool displaySequenceTraits;

enum MENU {
    GENERATESEQUENCES,
    SORTSEQUENCES,
    DISPLAYSEQUENCETRAITS,
    EXIT
};

void ChangeColor(int Color);

void PrintMenuOption(const std::string& Option);

MENU ShowMenu();