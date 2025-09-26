#include "GameManager.h"
#include "Map.h"
#include "Orc.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Shop.h"
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
			printf("\n");
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
			MoveEventProcess(player, Stage);
		}
	}
	if (player.GetHealth() > 0)
		printf("�����մϴ�! ������ Ŭ�����ϼ̽��ϴ�!");
	printf("������ �������� : %d | ���� �ִ�ü�� : %.2f | ���� ���ݷ� : %.2f\n", Stage, player.GetMaxHealth(), player.GetAttackPower());
	printf("���� ���� %d | ���� ��� : %d", player.GetMana(), player.GetGold());
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

void GameManager::MoveEventProcess(Player& Player, int InStage)
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)
	{
		printf("\n���� �����߽��ϴ�.\n");
		BattleEvent(Player, InStage);
	}
	else if (RandomValue < 0.3f)
	{
		printf("������ ������ �������ϴ�.\n");
		ShopEvent(Player);
	}
	else if (RandomValue < 0.35f)
	{
		printf("\n���� ���ڸ� �߰��߽��ϴ�!\n");
		BoxEvent(Player);
	}
	else
	{
		printf("�ƹ� �ϵ� �Ͼ�� �ʾҽ��ϴ�.\n");
	}
}

void GameManager::BattleEvent(Player& Player, int InStage)
{
	const int Size = 3;
	float AddStatus = static_cast<float>(InStage);
	Monster* Enemy[Size] = { 0 };
	Enemy[0] = new Orc("��ũ", 50.0f + (5.0f * AddStatus), 10.0f + (2.0f * AddStatus));
	Enemy[1] = new Goblin("���", 30.0f + (5.0f * AddStatus), 15.0f + (2.0f * AddStatus));
	Enemy[2] = new Zombie("����", 80.0f + (5.0f * AddStatus), 5.0f + (2.0f * AddStatus));

	int RandomMonster = rand() % 3;
	int Run = 0;

	printf("\n[%s]�� �����ƽ��ϴ�. ��Ʋ�� �����մϴ�.\n", Enemy[RandomMonster]->GetName().c_str());
	while (true)
	{
		int Input = 0;
		bool IsGuard = false;
		bool Select = false;
		printf("�� ����\n");
		Enemy[RandomMonster]->PrintStatus();
		while (!Select)
		{
			printf("\n���� ����\n");
			Player.PrintStatus();
			printf("1. ���� | 2. ��ų | 3. ������ | 4. ����\n");
			printf("�ൿ�� �����ϼ��� : ");
			if (!(std::cin >> Input))
			{
				std::cin.clear(); // failbit �ʱ�ȭ
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �߸� �Էµ� �κ� ����
				printf("�߸� �Է��ϼ̽��ϴ�. ���ڸ� �Է��ϼ���.\n");
				continue; // �ٽ� �Է� ����
			}
			printf("----------------------------------------\n");

			switch (Input)
			{
			case(1):
			{
				printf("\n�÷��̾ �����մϴ�.\n");
				Player.ApplyDamage(Enemy[RandomMonster]);
				printf("���� ���� HP : %.1f\n", Enemy[RandomMonster]->GetHealth());
				Select = true;
				break;
			}
			case(2):
			{
				// ��ų ���� �Լ�
				Player.UseSkill(Enemy[RandomMonster], &Select);
				break;
			}
			case(3):
			{
				// �κ��丮 ���� �Լ�
				Player.OpenInventory(&Select);
				break;
			}
			case(4):
			{
				printf("���� ���ݷ��� 2���� �������� �԰� ����Ĩ�ϴ�.\n");
				printf("��� �Ͻðڽ��ϱ�? 1. �� | 2. �ƴϿ� : ");
				std::cin >> Run;
				if (Run == 1)
				{
					printf("����Ĩ�ϴ�.\n");
					Player.TakeDamage(Enemy[RandomMonster]->GetAttackPower() * 2);
					Select = true;
				}
				else
				{
					printf("�޴��� ���ư��ϴ�.\n");
				}
				break;
			}
			default:
			{
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
			}
			}
		}
		if (Run == 1)
		{
			break;	// ����ħ ����
		}

		if (Enemy[RandomMonster]->GetHealth() <= 0)
		{
			printf("���� óġ�߽��ϴ�.\n");
			
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
		printf("�÷��̾��� ���� HP : %.1f\n\n", Player.GetHealth());
		Player.UpdateGuard();
		Player.UpdateBerserk();
		Player.SetMana(2);
		if (Player.GetHealth() <= 0)
		{
			printf("�й��Ͽ����ϴ�.\n");
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
			printf("���� ������ �߰��Ͽ����ϴ�.\n\n");
			Player.UsePassive(ItemInfo::MakeAttackItem("���� ����", "�⺻ ���ݷ��� 2.5 ������ŵ�ϴ�", 100, 2.5f));
			break;
		}
		case(1):
		{
			printf("Ȱ���� ������ �߰��Ͽ����ϴ�.\n\n");
			Player.UsePassive(ItemInfo::MakeMaxHPItem("Ȱ���� ����", "�ִ� ü���� 10 ������ŵ�ϴ�.", 100, 10.0f));
			break;
		}
		case(2):
		{
			printf("������ ������ �߰��Ͽ����ϴ�.\n\n");
			Player.UsePassive(ItemInfo::MakeMaxMPItem("������ ����", "�ִ� ������ 5 ������ŵ�ϴ�.", 100, 5));
			break;
		}
		}
	}
	else if (RandomItem < 25)
	{
		RandomCount = rand() % 5 + 1;
		printf("HP ���� ������ %d�� �߰��Ͽ����ϴ�.\n\n",RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeHPItem("HP ���� ����", "HP�� 10 ȸ���մϴ�.", 10, 10.0f));
	}
	else if (RandomItem < 35)
	{
		RandomCount = rand() % 2 + 1;
		printf("HP ���� ������ %d�� �߰��Ͽ����ϴ�.\n\n", RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeHPItem("HP ���� ����", "HP�� 30 ȸ���մϴ�.", 30, 30.0f));
	}
	else if (RandomItem < 45)
	{
		RandomCount = rand() % 3 + 1;
		printf("���� ������ %d�� �߰��Ͽ����ϴ�.\n\n", RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeMPItem("���� ����", "MP�� 10 ȸ���մϴ�.", 20, 10));
	}
	else
	{
		RandomCount = rand() % 100;
		printf("��带 %d�� �߰��Ͽ����ϴ�.\n");
		Player.AddGold(RandomCount);
	}
}
