#define _CRT_SECURE_NO_WARNINGS
#include "GameManager.h"
#include<iostream>
#include<stdio.h>
#include<fstream>
#include"Orc.h"
#include"Goblin.h"
#include"Zombie.h"

void GameManager::InitializeMaze()
{
	std::string Data;
	ReadMapFile("MapData.txt", Data);	// ���� �б�

	ParseMapData(Data);	// �� �Ľ�
}

void GameManager::MazeEscapeRun()
{
	APlayer player("�÷��̾�", 100.0f, 20.0f);

	FindStartPosition(player.GetPosition());

	printf("~~ �̷� Ż�� ���� ~~\n");

	while (player.GetHealth() > 0)
	{
		PrintMaze(player.GetPosition());

		if (IsEnd(player.GetPosition()))
		{
			printf("�����մϴ�! �̷θ� Ż���߽��ϴ�.\n");
			break;
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

	if (player.GetHealth() >= 0)
	{
		// ���� Ŭ����
	}
	else
	{
		// ���� ����
	}
}

void GameManager::ClearMaze()
{
	if (Maze != nullptr)
	{
		for (int i = 0; i < MazeHeight; i++)
		{
			delete[] Maze[i];
			Maze[i] = nullptr;
		}
		delete[] Maze;
		Maze = nullptr;
	}
}

bool GameManager::ReadMapFile(const char* MapFileName, std::string& OutDataString)
{
	char FilePath[256];
	strcpy(FilePath, DirectoryName);
	strcat(FilePath, MapFileName);

	std::ifstream InputFile(FilePath);
	if (!InputFile.is_open())	// ������ ���ȴ��� Ȯ���ϴ� �Լ�
	{
		printf("������ �� �� �����ϴ�.\n");
		printf("[%s] ��θ� Ȯ���ϼ���.\n", FilePath);
		return false;
	}

	OutDataString = std::string((std::istreambuf_iterator<char>(InputFile)),
		std::istreambuf_iterator<char>()); // InputFile�� �ִ� ���ڵ��� ��� �о OutDataString�� �����ϱ�

	return true;
}

bool GameManager::ParseMapData(std::string& DataString)
{
	char Source[512];
	char* Current = Source;
	strcpy(Source, DataString.c_str());

	// ���� �и��ϱ�
	char* LinePtr = GetLine(&Current);

	// ���� �Ľ��ϱ�
	int SizeNumbers[2] = { 0 };
	ParseLineData(LinePtr, 2, SizeNumbers);

	printf("Size : %d, %d\n", SizeNumbers[0], SizeNumbers[1]);

	// ���� ũ�⸦ �˾Ҵ�. => Maze ����
	MazeWidth = SizeNumbers[0];
	MazeHeight = SizeNumbers[1];

	Maze = new int* [MazeHeight];
	for (int y = 0; y < MazeHeight; y++)
	{
		Maze[y] = new int[MazeWidth];
	}

	int HeightIndex = 0;
	while (*Current != '\0')	// Current�� \0�� �� ������ �ݺ�
	{
		LinePtr = GetLine(&Current);	// ���� �߶󳻰�
		ParseLineData(LinePtr, MazeWidth, Maze[HeightIndex]);	// �Ľ��ؼ� ������ �ְ�
		HeightIndex++;

		if (HeightIndex >= MazeHeight)	// ũ�⸦ ����� ���ϰ� üũ
			break;
	}

	return true;
}

int GameManager::FindCharIndex(const char* TargetString, const char TargetCharacter)
{
	int Index = 0;
	bool IsFind = false;
	while (TargetString[Index] != '\0')
	{
		if (TargetString[Index] == TargetCharacter)
		{
			IsFind = true;
			break;
		}
		Index++;
	}

	if (!IsFind)
	{
		Index = -1;
	}
	return Index;
}

char* GameManager::GetLine(char** InOutSource)
{
	char* Result = (*InOutSource);
	int Index = FindCharIndex((*InOutSource), '\n');
	if (Index == -1)
	{
		(*InOutSource) = (*InOutSource) + FindCharIndex((*InOutSource), '\0');
	}
	else
	{
		*((*InOutSource) + Index) = '\0';
		(*InOutSource) = (*InOutSource) + Index + 1;
	}
	return Result;
}

void GameManager::ParseLineData(const char* LineData, int ArraySize, int* OutArray)
{
	const char* LinePointer = LineData;
	int SizeIndex = 0;
	while ((*LinePointer) != '\0')
	{
		int Result = 0;
		while ((*LinePointer) != ',' && (*LinePointer) != '\0')
		{
			Result = Result * 10 + (*LinePointer) - '0';	// ���� �����
			LinePointer++;
		}
		OutArray[SizeIndex] = Result;	// ���� ��� ����
		SizeIndex++;

		if (ArraySize <= SizeIndex)	// �迭 ũ�� �̻����� �ִ� ���� ����
			break;

		if (*LinePointer < '0' || *LinePointer > '9')	// ���� �ܿ��� ��ŵ
			LinePointer++;
	}
}

void GameManager::PrintMaze(Position& position)
{
	for (int y = 0; y < MazeHeight; y++)
	{
		for (int x = 0; x < MazeWidth; x++)
		{
			if (position.x == x && position.y == y)
				printf("P ");
			else if (Maze[y][x] == MazeTile::Wall)
				printf("# ");
			else if (Maze[y][x] == MazeTile::Path)
				printf(". ");
			else if (Maze[y][x] == MazeTile::Start)
				printf("S ");
			else if (Maze[y][x] == MazeTile::End)
				printf("E ");
			else
			{
				// ������ �ȵ� == �� �����Ͱ� �߸��� ��
			}
		}
		printf("\n");
	}
}

void GameManager::FindStartPosition(Position& OutPosition)
{
	for (int y = 0; y < MazeHeight; y++)
	{
		for (int x = 0; x < MazeWidth; x++)
		{
			if (Maze[y][x] == MazeTile::Start)
			{
				OutPosition.x = x;
				OutPosition.y = y;
				return;
			}
		}
	}
	OutPosition.x = 0;
	OutPosition.y = 0;
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
	if (Y < 0 || Y >= MazeHeight ||
		X < 0 || X >= MazeWidth ||
		Maze[Y][X] == MazeTile::Wall)
		isWall = true;
	return isWall;
}

bool GameManager::IsEnd(Position& position)
{
	return Maze[position.y][position.x] == MazeTile::End;
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

void GameManager::MoveEventProcess(APlayer& Player)
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)
	{
		printf("���� �����߽��ϴ�.\n");
		BattleEvent(Player);
	}
	else if (RandomValue < 0.4f)
	{
		printf("ġ���縦 ã�ҽ��ϴ�.\n");
		HealerEvent(Player);
	}
	else
	{
		printf("�ƹ� �ϵ� �Ͼ�� �ʾҽ��ϴ�.\n");
	}
}


void GameManager::BattleEvent(APlayer& Player)
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

void GameManager::HealerEvent(APlayer& Player)
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
