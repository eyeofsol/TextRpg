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
        Items = // ���� ������ �ʱ�ȭ
        {
            ItemInfo::MakeHPItem("HP ���� ����", "HP�� 10 ȸ���մϴ�.", 10, 10.0f),
            ItemInfo::MakeHPItem("HP ���� ����", "HP�� 30 ȸ���մϴ�.", 30, 30.0f),
            ItemInfo::MakeMPItem("���� ����", "MP�� 10 ȸ���մϴ�.", 20, 10),
            ItemInfo::MakeAttackItem("���� ����", "�⺻ ���ݷ��� 2.5 ������ŵ�ϴ�", 100, 2.5f),
            ItemInfo::MakeMaxHPItem("Ȱ���� ����", "�ִ� ü���� 10 ������ŵ�ϴ�.", 100, 10.0f),
            ItemInfo::MakeMaxMPItem("������ ����", "�ִ� ������ 5 ������ŵ�ϴ�.", 100, 5),
        };
    }
    /// <summary>
    /// ������ ���� �Լ�
    /// </summary>
    /// <param name="Player">�÷��̾� ����ü</param>
    void OpenShop(Player& Player);
    /// <summary>
    /// ������ ���� �Լ�
    /// </summary>
    /// <param name="Player">�÷��̾� ����ü</param>
    /// <param name="Item">������ ������</param>
    void BuyItem(Player& Player,const ItemInfo& Item);

private:
    std::vector<ItemInfo> Items;    // ������ �迭
};