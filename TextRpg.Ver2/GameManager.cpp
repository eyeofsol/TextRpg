#include "GameManager.h"
#include "Map.h"
#include "Orc.h"
#include "Goblin.h"
#include "Zombie.h"
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
			MoveEventProcess(player);
		}
	}
	if (player.GetHealth() > 0)
		printf("축하합니다! 게임을 클리어하셨습니다!");
	printf("정복한 스테이지 : %d, 최종 최대체력 : %.2f, 최종 공격력 : %.2f\n", Stage, player.GetMaxHealth(), player.GetAttackPower());
	printf("소지 골드 : %d", player.GetGold());
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

void GameManager::MoveEventProcess(Player& Player)
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)
	{
		printf("적이 출현했습니다.\n");
		//BattleEvent(Player);
	}
	else if (RandomValue < 0.4f)
	{
		printf("치유사를 찾았습니다.\n");
		//HealerEvent(Player);
	}
	else
	{
		printf("아무 일도 일어나지 않았습니다.\n");
	}
}


void GameManager::BattleEvent(Player& Player)
{
	const int Size = 3;
	Monster* Enemy[Size] = { 0 };
	Enemy[0] = new Orc("오크", 50.0f, 10.0f);
	Enemy[1] = new Goblin("고블린", 30.0f, 15.0f);
	Enemy[2] = new Zombie("좀비", 80.0f, 5.0f);

	int RandomMonster = rand() % 3;

	printf("[%s]을 마주쳤습니다. 배틀을 시작합니다.\n", Enemy[RandomMonster]->GetName().c_str());
	while (true)
	{
		printf("플레이어가 공격합니다.\n");
		Player.ApplyDamage(Enemy[RandomMonster]);
		printf("적의 남은 HP : %.1f\n", Enemy[RandomMonster]->GetHealth());
		if (Enemy[RandomMonster]->GetHealth() <= 0)
		{
			printf("적을 처치했습니다.\n");
			printf("%d 골드를 획득하였습니다.\n", Enemy[RandomMonster]->GetDropGold());
			Player.AddGold(Enemy[RandomMonster]->GetDropGold());
			break;
		}
		int RandomSkill = rand() % 10;
		if (RandomSkill < 3)
		{
			Enemy[RandomMonster]->Skill(&Player);
		}
		else
			Enemy[RandomMonster]->ApplyDamage(&Player);
		printf("플레이어의 남은 HP : %.1f\n", Player.GetHealth());
		if (Player.GetHealth() <= 0)
		{
			printf("패배하였습니다.\n");
			break;
		}
	}

	for (int i = 0; i < Size; i++)
	{
		delete Enemy[i];
		Enemy[i] = nullptr;
	}
}

void GameManager::HealerEvent(Player& Player)
{
	printf("치유사를 만났습니다. 얼마를 지불하시겠습니까?\n");
	printf("현재 체력 : %.1f, 현재 골드 : %d\n", Player.GetHealth(), Player.GetGold());
	int payGold = -1;
	while (payGold < 0 || payGold > Player.GetGold())
	{
		printf("지불할 골드를 입력하세요 : ");
		std::cin >> payGold;
		if (payGold <= 0)
		{
			printf("회복을 포기하였습니다.\n");
		}
		else if (payGold > Player.GetGold())
		{
			printf("소지 금액이 부족합니다.\n");
		}
		else
		{
			printf("잘못 입력하셨습니다.\n");
		}
	}
	if (payGold > 0)
	{
		float healAmout = static_cast<float>(payGold);
		float newHealth = Player.GetHealth() + healAmout;
		if (newHealth > Player.GetMaxHealth())
			newHealth = Player.GetMaxHealth();
		Player.GetHealth() = newHealth;
		Player.GetGold() -= payGold;
		printf("회복하였습니다.\n");
	}
	printf("현재 체력 : %.1f, 남은 골드 : %d\n", Player.GetHealth(), Player.GetGold());
}
