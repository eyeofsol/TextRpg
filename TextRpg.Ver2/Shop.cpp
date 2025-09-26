#include "Shop.h"
#include <stdio.h>
#include <iostream>
#include	<limits>

void Shop::OpenShop(Player& Player)	// ���� ���� �Լ�
{
	while (true)
	{
		printf("\n--------�Ǹ� ���--------\n");
		int Input = -1;
		int Index = 1;	// ������ ��ȣ ���
		for (auto& Item : Items)	// ������ ���
		{
			printf("%d. %s : %s (�ݾ� : %d)\n",Index, Item.Name.c_str(), Item.Detail.c_str(), Item.Price);
			Index++;
		}
		printf("���� ��� : %d\n", Player.GetGold());
		printf("������ �������� �Է��ϼ���(0�� �Է� �� ������ �����ϴ�.) : ");
		if (!(std::cin >> Input)) // ���Է� ����
		{
			std::cin.clear(); // failbit, badbit �ʱ�ȭ
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� ����
			printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
			continue;
		}

		if (Input == 0)
			break;
		if (Input < 0 || Input>Items.size())
		{
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
			continue;
		}
		BuyItem(Player, Items[Input - 1]);	// ������ ���� ����
	}
}

void Shop::BuyItem(Player& Player, const ItemInfo& Item)
{
	if (Player.GetGold() < Item.Price)	// ��� ����
	{
		printf("��尡 �����մϴ�.\n");
		return;
	}

	Player.GetGold() -= Item.Price;	// ��� ����
	if (Item.HPAmount > 0 || Item.MPAmount > 0)	// �Ҹ� ������ �϶�
		Player.AddItem(Item);	// �κ��丮 �߰�
	else
		Player.UsePassive(Item);	// �нú� �������� ��� ���
	printf("%s�� �����߽��ϴ�.\n", Item.Name.c_str());
}
