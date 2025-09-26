#pragma once
#include <string>

struct ItemInfo // 아이템 정보
{
    std::string Name;   // 이름
    std::string Detail; // 설명
    int Price;      // 가격
    float HPAmount;   // HP 회복량
    int MPAmount;   // Mana 회복량
    float AttackAmount; // 공격력 추가량
    float MaxHPAmount;  // 체력 추가량
    int MaxMPAmount;// 마나 추가량

    static ItemInfo MakeHPItem(const std::string& Name, const std::string& Detail, int Price, float HP) // HP 물약
    {
        return { Name, Detail, Price, HP, 0, 0, 0, 0 };
    }

    static ItemInfo MakeMPItem(const std::string& Name, const std::string& Detail, int Price, int MP)   // MP 물약
    {
        return { Name, Detail, Price, 0, MP, 0, 0, 0 };
    }

    static ItemInfo MakeAttackItem(const std::string& Name, const std::string& Detail, int Price, float AttackPower)    // 힘의 물약
    {
        return { Name, Detail, Price, 0, 0, AttackPower, 0, 0 };
    }

    static ItemInfo MakeMaxHPItem(const std::string& Name, const std::string& Detail, int Price, float MaxHP)   // 활력의 물약
    {
        return { Name, Detail, Price, 0, 0, 0, MaxHP, 0 };
    }

    static ItemInfo MakeMaxMPItem(const std::string& Name, const std::string& Detail, int Price, int MaxMP) // 지능의 물약
    {
        return { Name, Detail, Price, 0, 0, 0, 0, MaxMP };
    }
};