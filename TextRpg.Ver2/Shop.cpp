#include "Shop.h"
#include <stdio.h>
#include <iostream>
#include	<limits>

void Shop::OpenShop(Player& Player)	// 상점 열기 함수
{
	while (true)
	{
		printf("\n--------판매 목록--------\n");
		int Input = -1;
		int Index = 1;	// 아이템 번호 출력
		for (auto& Item : Items)	// 아이템 출력
		{
			printf("%d. %s : %s (금액 : %d)\n",Index, Item.Name.c_str(), Item.Detail.c_str(), Item.Price);
			Index++;
		}
		printf("소지 골드 : %d\n", Player.GetGold());
		printf("구매할 아이템을 입력하세요(0을 입력 시 상점을 나갑니다.) : ");
		if (!(std::cin >> Input)) // 오입력 방지
		{
			std::cin.clear(); // failbit, badbit 초기화
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 버퍼 비우기
			printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
			continue;
		}

		if (Input == 0)
			break;
		if (Input < 0 || Input>Items.size())
		{
			printf("잘못 입력하셨습니다.\n");
			continue;
		}
		BuyItem(Player, Items[Input - 1]);	// 아이템 구매 진행
	}
}

void Shop::BuyItem(Player& Player, const ItemInfo& Item)
{
	if (Player.GetGold() < Item.Price)	// 골드 부족
	{
		printf("골드가 부족합니다.\n");
		return;
	}

	Player.GetGold() -= Item.Price;	// 골드 차감
	if (Item.HPAmount > 0 || Item.MPAmount > 0)	// 소모 아이템 일때
		Player.AddItem(Item);	// 인벤토리 추가
	else
		Player.UsePassive(Item);	// 패시브 아이템은 즉시 사용
	printf("%s을 구매했습니다.\n", Item.Name.c_str());
}
