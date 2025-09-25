#include "Shop.h"
#include <stdio.h>
#include <iostream>

void Shop::OpenShop(Player& Player)
{
	while (true)
	{
		printf("\n--------판매 목록--------\n");
		int Input = -1;
		for (auto& Item : Items)
		{
			printf("%s : %s (금액 : %d)\n", Item.Name.c_str(), Item.Detail.c_str(), Item.Price);
		}
		printf("소지 골드 : %d\n", Player.GetGold());
		printf("구매할 아이템을 입력하세요(0을 입력 시 상점을 나갑니다.) : ");
		std::cin >> Input;

		if (Input == 0)
			break;
		if (Input < 0 || Input>Items.size())
		{
			printf("잘못 입력하셨습니다.\n");
			continue;
		}
		BuyItem(Player, Items[Input - 1]);
	}
}

void Shop::BuyItem(Player& Player, const ItemInfo& Item)
{
	if (Player.GetGold() < Item.Price)
	{
		printf("골드가 부족합니다.\n");
		return;
	}

	Player.GetGold() -= Item.Price;
	Player.AddItem(Item);
	printf("%s을 구매했습니다.\n", Item.Name.c_str());
}
