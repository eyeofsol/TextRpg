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
	ReadMapFile("MapData.txt", Data);	// 파일 읽기

	ParseMapData(Data);	// 맵 파싱
}

void GameManager::MazeEscapeRun()
{
	APlayer player("플레이어", 100.0f, 20.0f);

	FindStartPosition(player.GetPosition());

	printf("~~ 미로 탈출 게임 ~~\n");

	while (player.GetHealth() > 0)
	{
		PrintMaze(player.GetPosition());

		if (IsEnd(player.GetPosition()))
		{
			printf("축하합니다! 미로를 탈출했습니다.\n");
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
			// 있을 수 없음
			break;
		}


		MoveEventProcess(player);
	}

	if (player.GetHealth() >= 0)
	{
		// 게임 클리어
	}
	else
	{
		// 게임 오버
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
	if (!InputFile.is_open())	// 파일이 열렸는지 확인하는 함수
	{
		printf("파일을 열 수 없습니다.\n");
		printf("[%s] 경로를 확인하세요.\n", FilePath);
		return false;
	}

	OutDataString = std::string((std::istreambuf_iterator<char>(InputFile)),
		std::istreambuf_iterator<char>()); // InputFile에 있는 글자들을 모두 읽어서 OutDataString에 저장하기

	return true;
}

bool GameManager::ParseMapData(std::string& DataString)
{
	char Source[512];
	char* Current = Source;
	strcpy(Source, DataString.c_str());

	// 라인 분리하기
	char* LinePtr = GetLine(&Current);

	// 라인 파싱하기
	int SizeNumbers[2] = { 0 };
	ParseLineData(LinePtr, 2, SizeNumbers);

	printf("Size : %d, %d\n", SizeNumbers[0], SizeNumbers[1]);

	// 맵의 크기를 알았다. => Maze 생성
	MazeWidth = SizeNumbers[0];
	MazeHeight = SizeNumbers[1];

	Maze = new int* [MazeHeight];
	for (int y = 0; y < MazeHeight; y++)
	{
		Maze[y] = new int[MazeWidth];
	}

	int HeightIndex = 0;
	while (*Current != '\0')	// Current가 \0이 될 때까지 반복
	{
		LinePtr = GetLine(&Current);	// 한줄 잘라내고
		ParseLineData(LinePtr, MazeWidth, Maze[HeightIndex]);	// 파싱해서 데이터 넣고
		HeightIndex++;

		if (HeightIndex >= MazeHeight)	// 크기를 벗어나지 못하게 체크
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
			Result = Result * 10 + (*LinePointer) - '0';	// 숫자 만들기
			LinePointer++;
		}
		OutArray[SizeIndex] = Result;	// 숫자 결과 저장
		SizeIndex++;

		if (ArraySize <= SizeIndex)	// 배열 크기 이상으로 넣는 것을 방지
			break;

		if (*LinePointer < '0' || *LinePointer > '9')	// 숫자 외에는 스킵
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
				// 들어오면 안됨 == 맵 데이터가 잘못된 것
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

void GameManager::MoveEventProcess(APlayer& Player)
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)
	{
		printf("적이 출현했습니다.\n");
		BattleEvent(Player);
	}
	else if (RandomValue < 0.4f)
	{
		printf("치유사를 찾았습니다.\n");
		HealerEvent(Player);
	}
	else
	{
		printf("아무 일도 일어나지 않았습니다.\n");
	}
}


void GameManager::BattleEvent(APlayer& Player)
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

void GameManager::HealerEvent(APlayer& Player)
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
