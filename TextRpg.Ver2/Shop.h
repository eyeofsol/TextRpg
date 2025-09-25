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
            {"HP ���� ����", "HP�� 10 ȸ���մϴ�.", 10, 10.0f, 0 },
            {"HP ���� ����", "HP�� 30 ȸ���մϴ�.", 30, 30.0f, 0 },
            {"���� ����", "MP�� 10 ȸ���մϴ�.", 20, 0.0f, 10 }
        };
    }
    void OpenShop(Player& Player);
    void BuyItem(Player& Player,const ItemInfo& Item);

private:
    std::vector<ItemInfo> Items;
};