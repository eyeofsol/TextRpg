#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "ItemInfo.h"

class Shop
{
public:
    Shop()
    {
        Items =
        {
            ItemInfo::MakeHPItem("HP 소형 물약", "HP를 10 회복합니다.", 10, 10.0f),
            ItemInfo::MakeHPItem("HP 대형 물약", "HP를 30 회복합니다.", 30, 30.0f),
            ItemInfo::MakeMPItem("마나 물약", "MP를 10 회복합니다.", 20, 10),
            ItemInfo::MakeAttackItem("힘의 물약", "기본 공격력을 2.5 증가시킵니다", 100, 2.5f),
            ItemInfo::MakeMaxHPItem("활력의 물약", "최대 체력을 10 증가시킵니다.", 100, 10.0f),
            ItemInfo::MakeMaxMPItem("지능의 물약", "최대 마나를 5 증가시킵니다.", 100, 5),
        };
    }
    void OpenShop(Player& Player);
    void BuyItem(Player& Player,const ItemInfo& Item);

private:
    std::vector<ItemInfo> Items;
};