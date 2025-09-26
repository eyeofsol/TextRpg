#pragma once
#include <string>

struct ItemInfo
{
    std::string Name;
    std::string Detail;
    int Price;
    float HPAmount;   // HP 회복량
    int MPAmount;   // Mana 회복량
    float AttackAmount; // 공격력 추가량
    float MaxHPAmount;  // 체력 추가량
    int MaxMPAmount;// 마나 추가량

    static ItemInfo MakeHPItem(const std::string& Name, const std::string& Detail, int Price, float HP)
    {
        return { Name, Detail, Price, HP, 0, 0, 0, 0 };
    }

    static ItemInfo MakeMPItem(const std::string& Name, const std::string& Detail, int Price, int MP)
    {
        return { Name, Detail, Price, 0, MP, 0, 0, 0 };
    }

    static ItemInfo MakeAttackItem(const std::string& Name, const std::string& Detail, int Price, float AttackPower)
    {
        return { Name, Detail, Price, 0, 0, AttackPower, 0, 0 };
    }

    static ItemInfo MakeMaxHPItem(const std::string& Name, const std::string& Detail, int Price, float MaxHP)
    {
        return { Name, Detail, Price, 0, 0, 0, MaxHP, 0 };
    }

    static ItemInfo MakeMaxMPItem(const std::string& Name, const std::string& Detail, int Price, int MaxMP)
    {
        return { Name, Detail, Price, 0, 0, 0, 0, MaxMP };
    }
};