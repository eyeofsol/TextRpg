#include "GameManager.h"
#include "Map.h"
#include "Orc.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Shop.h"
#include <iostream>

void GameManager::PlayGame()
{
	printf("~~ 광산 탐험 게임 ~~\n");
	Player player("플레이어", 100.0f, 20.0f);

	for (int i = 1; i <= MaxStage; i++)
	{
		Map.GenerateMap();
		Map.FindStartPosition(player.GetPosition());
		HasKey = false;

		while (player.GetHealth() > 0)
		{
			printf("\n");
			Map.PrintMap(player.GetPosition());

			if (IsEnd(player.GetPosition()))
			{
				if (HasKey)
				{
					printf("\n");
					printf("%d층을 클리어하였습니다. 다음 층으로 내려갑니다...\n", i);
					printf("\n");
					Stage++;
					break;
				}
				else
				{
					printf("내려가는 문이 잠겨있습니다. 열쇠를 획득하고 오세요.\n");
				}
			}
			if (IsKey(player.GetPosition()))
			{
				printf("열쇠를 획득하였습니다.\n");
				Map.PickupKey(player.GetPosition().x, player.GetPosition().y);
				HasKey = true;
			}

			int MoveFlags = PrintAvailableMoves(player.GetPosition());
			MoveDirection Direction = GetMoveInput(MoveFlags);
			switch (Direction)
			{
			case MoveDirection::DirUp:
				player.GetPosition().y--;
				break;
			case MoveDirection::DirDown:
				player.GetPosition().y++;
				break;
			case MoveDirection::DirLeft:
				player.GetPosition().x--;
				break;
			case MoveDirection::DirRight:
				player.GetPosition().x++;
				break;
			case MoveDirection::DirNone:
			default:
				// 있을 수 없음
				break;
			}
			MoveEventProcess(player, Stage);
		}
	}
	if (player.GetHealth() > 0)
		printf("축하합니다! 게임을 클리어하셨습니다!");
	printf("정복한 스테이지 : %d | 최종 최대체력 : %.2f | 최종 공격력 : %.2f\n", Stage, player.GetMaxHealth(), player.GetAttackPower());
	printf("최종 마나 %d | 소지 골드 : %d", player.GetMana(), player.GetGold());
}

int GameManager::PrintAvailableMoves(Position& position)
{
	int MoveFlags = static_cast<int>(MoveDirection::DirNone);
	
	printf("이동할 수 있는 방향을 선택하세요 (w:위 a:왼쪽 s:아래쪽 d:오른쪽 g:체력 회복):\n");
	if (!IsWall(position.x, position.y - 1))
	{
		printf("W(↑) ");
		MoveFlags |= MoveDirection::DirUp;
	}
	if (!IsWall(position.x, position.y + 1))
	{
		printf("S(↓) ");
		MoveFlags |= MoveDirection::DirDown;
	}
	if (!IsWall(position.x - 1, position.y))
	{
		printf("A(←) ");
		MoveFlags |= MoveDirection::DirLeft;
	}
	if (!IsWall(position.x + 1, position.y))
	{
		printf("D(→) ");
		MoveFlags |= MoveDirection::DirRight;
	}
	printf("\n");

	return MoveFlags;
}

bool GameManager::IsWall(int X, int Y)
{
	bool isWall = false;
	if (Y < 0 || Y >= Map.GetHeight() ||
		X < 0 || X >= Map.GetWidth() ||
		Map.GetMaze(Y, X) == MazeTile::Wall)
		isWall = true;
	return isWall;
}

bool GameManager::IsEnd(Position& position)
{
	return Map.GetMaze(position.y, position.x) == MazeTile::End;
}

bool GameManager::IsKey(Position& position)
{
	return Map.GetMaze(position.y, position.x) == MazeTile::Key;
}

MoveDirection GameManager::GetMoveInput(int MoveFlags)
{
	char InputChar = 0;
	MoveDirection Direction = MoveDirection::DirNone;

	while (true)
	{
		printf("방향을 입력하세요 : ");
		std::cin >> InputChar;

		if ((InputChar == 'w' || InputChar == 'W')
			&& (MoveFlags & MoveDirection::DirUp))
		{
			Direction = MoveDirection::DirUp;
			break;
		}
		if ((InputChar == 's' || InputChar == 'S')
			&& (MoveFlags & MoveDirection::DirDown))
		{
			Direction = MoveDirection::DirDown;
			break;
		}
		if ((InputChar == 'a' || InputChar == 'A')
			&& (MoveFlags & MoveDirection::DirLeft))
		{
			Direction = MoveDirection::DirLeft;
			break;
		}
		if ((InputChar == 'd' || InputChar == 'D')
			&& (MoveFlags & MoveDirection::DirRight))
		{
			Direction = MoveDirection::DirRight;
			break;
		}
		printf("잘못된 입력입니다. 이동할 수 있는 방향 중에서 선택하세요.\n");
	}
	return Direction;
}

void GameManager::MoveEventProcess(Player& Player, int InStage)
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)
	{
		printf("\n적이 출현했습니다.\n");
		BattleEvent(Player, InStage);
	}
	else if (RandomValue < 0.3f)
	{
		printf("떠돌이 상인을 만났습니다.\n");
		ShopEvent(Player);
	}
	else if (RandomValue < 0.35f)
	{
		printf("\n보물 상자를 발견했습니다!\n");
		BoxEvent(Player);
	}
	else
	{
		printf("아무 일도 일어나지 않았습니다.\n");
	}
}

void GameManager::BattleEvent(Player& Player, int InStage)
{
	const int Size = 3;
	float AddStatus = static_cast<float>(InStage);
	Monster* Enemy[Size] = { 0 };
	Enemy[0] = new Orc("오크", 50.0f + (5.0f * AddStatus), 10.0f + (2.0f * AddStatus));
	Enemy[1] = new Goblin("고블린", 30.0f + (5.0f * AddStatus), 15.0f + (2.0f * AddStatus));
	Enemy[2] = new Zombie("좀비", 80.0f + (5.0f * AddStatus), 5.0f + (2.0f * AddStatus));

	int RandomMonster = rand() % 3;
	int Run = 0;

	printf("\n[%s]을 마주쳤습니다. 배틀을 시작합니다.\n", Enemy[RandomMonster]->GetName().c_str());
	while (true)
	{
		int Input = 0;
		bool IsGuard = false;
		bool Select = false;
		printf("적 정보\n");
		Enemy[RandomMonster]->PrintStatus();
		while (!Select)
		{
			printf("\n현재 상태\n");
			Player.PrintStatus();
			printf("1. 공격 | 2. 스킬 | 3. 아이템 | 4. 도망\n");
			printf("행동을 선택하세요 : ");
			if (!(std::cin >> Input))
			{
				std::cin.clear(); // failbit 초기화
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 잘못 입력된 부분 버림
				printf("잘못 입력하셨습니다. 숫자를 입력하세요.\n");
				continue; // 다시 입력 받음
			}
			printf("----------------------------------------\n");

			switch (Input)
			{
			case(1):
			{
				printf("\n플레이어가 공격합니다.\n");
				Player.ApplyDamage(Enemy[RandomMonster]);
				printf("적의 남은 HP : %.1f\n", Enemy[RandomMonster]->GetHealth());
				Select = true;
				break;
			}
			case(2):
			{
				// 스킬 선택 함수
				Player.UseSkill(Enemy[RandomMonster], &Select);
				break;
			}
			case(3):
			{
				// 인벤토리 오픈 함수
				Player.OpenInventory(&Select);
				break;
			}
			case(4):
			{
				printf("적의 공격력의 2배의 데미지를 입고 도망칩니다.\n");
				printf("계속 하시겠습니까? 1. 예 | 2. 아니오 : ");
				std::cin >> Run;
				if (Run == 1)
				{
					printf("도망칩니다.\n");
					Player.TakeDamage(Enemy[RandomMonster]->GetAttackPower() * 2);
					Select = true;
				}
				else
				{
					printf("메뉴로 돌아갑니다.\n");
				}
				break;
			}
			default:
			{
				printf("잘못 입력하셨습니다.\n");
			}
			}
		}
		if (Run == 1)
		{
			break;	// 도망침 판정
		}

		if (Enemy[RandomMonster]->GetHealth() <= 0)
		{
			printf("적을 처치했습니다.\n");
			
			Player.AddGold(Enemy[RandomMonster]->GetDropGold());
			Player.AddExp(Enemy[RandomMonster]->GetDropExp());
			break;
		}
		int RandomSkill = rand() % 10;
		if (RandomSkill < 3)
		{
			Enemy[RandomMonster]->Skill(&Player);
		}
		else
			Enemy[RandomMonster]->ApplyDamage(&Player);
		printf("플레이어의 남은 HP : %.1f\n\n", Player.GetHealth());
		Player.UpdateGuard();
		Player.UpdateBerserk();
		Player.SetMana(2);
		if (Player.GetHealth() <= 0)
		{
			printf("패배하였습니다.\n");
			break;
		}
	}

	Player.ResetStatus();
	for (int i = 0; i < Size; i++)
	{
		delete Enemy[i];
		Enemy[i] = nullptr;
	}
}

void GameManager::ShopEvent(Player& Player)
{
	Shop Shop;
	Shop.OpenShop(Player);
}

void GameManager::BoxEvent(Player& Player)
{
	int RandomItem = rand() % 100;
	int RandomCount;
	if (RandomItem < 5)
	{
		RandomCount = rand() % 3;
		switch (RandomCount)
		{
		case(0):
		{
			printf("힘의 물약을 발견하였습니다.\n\n");
			Player.UsePassive(ItemInfo::MakeAttackItem("힘의 물약", "기본 공격력을 2.5 증가시킵니다", 100, 2.5f));
			break;
		}
		case(1):
		{
			printf("활력의 물약을 발견하였습니다.\n\n");
			Player.UsePassive(ItemInfo::MakeMaxHPItem("활력의 물약", "최대 체력을 10 증가시킵니다.", 100, 10.0f));
			break;
		}
		case(2):
		{
			printf("지능의 물약을 발견하였습니다.\n\n");
			Player.UsePassive(ItemInfo::MakeMaxMPItem("지능의 물약", "최대 마나를 5 증가시킵니다.", 100, 5));
			break;
		}
		}
	}
	else if (RandomItem < 25)
	{
		RandomCount = rand() % 5 + 1;
		printf("HP 소형 물약을 %d개 발견하였습니다.\n\n",RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeHPItem("HP 소형 물약", "HP를 10 회복합니다.", 10, 10.0f));
	}
	else if (RandomItem < 35)
	{
		RandomCount = rand() % 2 + 1;
		printf("HP 대형 물약을 %d개 발견하였습니다.\n\n", RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeHPItem("HP 대형 물약", "HP를 30 회복합니다.", 30, 30.0f));
	}
	else if (RandomItem < 45)
	{
		RandomCount = rand() % 3 + 1;
		printf("마나 물약을 %d개 발견하였습니다.\n\n", RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeMPItem("마나 물약", "MP를 10 회복합니다.", 20, 10));
	}
	else
	{
		RandomCount = rand() % 100;
		printf("골드를 %d원 발견하였습니다.\n");
		Player.AddGold(RandomCount);
	}
}
