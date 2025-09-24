#include "GameManager.h"
#include "Map.h"
#include "Orc.h"
#include "Goblin.h"
#include "Zombie.h"
#include <iostream>

void GameManager::PlayGame()
{
	printf("~~ ���� Ž�� ���� ~~\n");
	Player player("�÷��̾�", 100.0f, 20.0f);

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
					printf("%d���� Ŭ�����Ͽ����ϴ�. ���� ������ �������ϴ�...\n", i);
					printf("\n");
					Stage++;
					break;
				}
				else
				{
					printf("�������� ���� ����ֽ��ϴ�. ���踦 ȹ���ϰ� ������.\n");
				}
			}
			if (IsKey(player.GetPosition()))
			{
				printf("���踦 ȹ���Ͽ����ϴ�.\n");
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
				// ���� �� ����
				break;
			}
			MoveEventProcess(player);
		}
	}
	if (player.GetHealth() > 0)
		printf("�����մϴ�! ������ Ŭ�����ϼ̽��ϴ�!");
	printf("������ �������� : %d, ���� �ִ�ü�� : %.2f, ���� ���ݷ� : %.2f\n", Stage, player.GetMaxHealth(), player.GetAttackPower());
	printf("���� ��� : %d", player.GetGold());
}

int GameManager::PrintAvailableMoves(Position& position)
{
	int MoveFlags = static_cast<int>(MoveDirection::DirNone);

	printf("�̵��� �� �ִ� ������ �����ϼ��� (w:�� a:���� s:�Ʒ��� d:������ g:ü�� ȸ��):\n");
	if (!IsWall(position.x, position.y - 1))
	{
		printf("W(��) ");
		MoveFlags |= MoveDirection::DirUp;
	}
	if (!IsWall(position.x, position.y + 1))
	{
		printf("S(��) ");
		MoveFlags |= MoveDirection::DirDown;
	}
	if (!IsWall(position.x - 1, position.y))
	{
		printf("A(��) ");
		MoveFlags |= MoveDirection::DirLeft;
	}
	if (!IsWall(position.x + 1, position.y))
	{
		printf("D(��) ");
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
		printf("������ �Է��ϼ��� : ");
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
		printf("�߸��� �Է��Դϴ�. �̵��� �� �ִ� ���� �߿��� �����ϼ���.\n");
	}
	return Direction;
}

void GameManager::MoveEventProcess(Player& Player)
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)
	{
		printf("���� �����߽��ϴ�.\n");
		//BattleEvent(Player);
	}
	else if (RandomValue < 0.4f)
	{
		printf("ġ���縦 ã�ҽ��ϴ�.\n");
		//HealerEvent(Player);
	}
	else
	{
		printf("�ƹ� �ϵ� �Ͼ�� �ʾҽ��ϴ�.\n");
	}
}


void GameManager::BattleEvent(Player& Player)
{
	const int Size = 3;
	Monster* Enemy[Size] = { 0 };
	Enemy[0] = new Orc("��ũ", 50.0f, 10.0f);
	Enemy[1] = new Goblin("���", 30.0f, 15.0f);
	Enemy[2] = new Zombie("����", 80.0f, 5.0f);

	int RandomMonster = rand() % 3;

	printf("[%s]�� �����ƽ��ϴ�. ��Ʋ�� �����մϴ�.\n", Enemy[RandomMonster]->GetName().c_str());
	while (true)
	{
		printf("�÷��̾ �����մϴ�.\n");
		Player.ApplyDamage(Enemy[RandomMonster]);
		printf("���� ���� HP : %.1f\n", Enemy[RandomMonster]->GetHealth());
		if (Enemy[RandomMonster]->GetHealth() <= 0)
		{
			printf("���� óġ�߽��ϴ�.\n");
			printf("%d ��带 ȹ���Ͽ����ϴ�.\n", Enemy[RandomMonster]->GetDropGold());
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
		printf("�÷��̾��� ���� HP : %.1f\n", Player.GetHealth());
		if (Player.GetHealth() <= 0)
		{
			printf("�й��Ͽ����ϴ�.\n");
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
	printf("ġ���縦 �������ϴ�. �󸶸� �����Ͻðڽ��ϱ�?\n");
	printf("���� ü�� : %.1f, ���� ��� : %d\n", Player.GetHealth(), Player.GetGold());
	int payGold = -1;
	while (payGold < 0 || payGold > Player.GetGold())
	{
		printf("������ ��带 �Է��ϼ��� : ");
		std::cin >> payGold;
		if (payGold <= 0)
		{
			printf("ȸ���� �����Ͽ����ϴ�.\n");
		}
		else if (payGold > Player.GetGold())
		{
			printf("���� �ݾ��� �����մϴ�.\n");
		}
		else
		{
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
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
		printf("ȸ���Ͽ����ϴ�.\n");
	}
	printf("���� ü�� : %.1f, ���� ��� : %d\n", Player.GetHealth(), Player.GetGold());
}
