#pragma once
#include <string>

struct ItemInfo // ������ ����
{
    std::string Name;   // �̸�
    std::string Detail; // ����
    int Price;      // ����
    float HPAmount;   // HP ȸ����
    int MPAmount;   // Mana ȸ����
    float AttackAmount; // ���ݷ� �߰���
    float MaxHPAmount;  // ü�� �߰���
    int MaxMPAmount;// ���� �߰���

    static ItemInfo MakeHPItem(const std::string& Name, const std::string& Detail, int Price, float HP) // HP ����
    {
        return { Name, Detail, Price, HP, 0, 0, 0, 0 };
    }

    static ItemInfo MakeMPItem(const std::string& Name, const std::string& Detail, int Price, int MP)   // MP ����
    {
        return { Name, Detail, Price, 0, MP, 0, 0, 0 };
    }

    static ItemInfo MakeAttackItem(const std::string& Name, const std::string& Detail, int Price, float AttackPower)    // ���� ����
    {
        return { Name, Detail, Price, 0, 0, AttackPower, 0, 0 };
    }

    static ItemInfo MakeMaxHPItem(const std::string& Name, const std::string& Detail, int Price, float MaxHP)   // Ȱ���� ����
    {
        return { Name, Detail, Price, 0, 0, 0, MaxHP, 0 };
    }

    static ItemInfo MakeMaxMPItem(const std::string& Name, const std::string& Detail, int Price, int MaxMP) // ������ ����
    {
        return { Name, Detail, Price, 0, 0, 0, 0, MaxMP };
    }
};