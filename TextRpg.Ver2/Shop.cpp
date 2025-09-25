#include "Shop.h"
#include <stdio.h>
#include <iostream>

void Shop::OpenShop(Player& Player)
{
	while (true)
	{
		printf("\n--------�Ǹ� ���--------\n");
		int Input = -1;
		for (auto& Item : Items)
		{
			printf("%s : %s (�ݾ� : %d)\n", Item.Name.c_str(), Item.Detail.c_str(), Item.Price);
		}
		printf("���� ��� : %d\n", Player.GetGold());
		printf("������ �������� �Է��ϼ���(0�� �Է� �� ������ �����ϴ�.) : ");
		std::cin >> Input;

		if (Input == 0)
			break;
		if (Input < 0 || Input>Items.size())
		{
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
			continue;
		}
		BuyItem(Player, Items[Input - 1]);
	}
}

void Shop::BuyItem(Player& Player, const ItemInfo& Item)
{
	if (Player.GetGold() < Item.Price)
	{
		printf("��尡 �����մϴ�.\n");
		return;
	}

	Player.GetGold() -= Item.Price;
	Player.AddItem(Item);
	printf("%s�� �����߽��ϴ�.\n", Item.Name.c_str());
}
