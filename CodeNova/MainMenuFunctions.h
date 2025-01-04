#pragma once
#include <iostream>
#include <string>
#include "Windows.h"
enum MENU {
    GENERATESEQUENCES,
    SORTSEQUENCES,
    EXIT
};

void ChangeColor(HANDLE Output, int Color);

void PrintMenuOption(const std::string& Option);

MENU ShowMenu();