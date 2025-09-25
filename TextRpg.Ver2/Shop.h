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
            {"HP 소형 물약", "HP를 10 회복합니다.", 10, 10.0f, 0 },
            {"HP 대형 물약", "HP를 30 회복합니다.", 30, 30.0f, 0 },
            {"마나 물약", "MP를 10 회복합니다.", 20, 0.0f, 10 }
        };
    }
    void OpenShop(Player& Player);
    void BuyItem(Player& Player,const ItemInfo& Item);

private:
    std::vector<ItemInfo> Items;
};