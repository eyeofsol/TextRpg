#pragma once
#include <string>

struct ItemInfo
{
    std::string Name;
    std::string Detail;
    int Price;
    float HPAmount;   // HP 회복량
    int MPAmount;   // Mana 회복량
};