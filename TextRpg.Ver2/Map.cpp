#include "Map.h"
#include<iostream>
#include<stdio.h>
#include<time.h>
#include<random>

void Map::ShuffleDir(int dir[])
{
	for (int i = 0; i < 4; i++)
	{
		int r = rand() % 4;
		int tmp = dir[i];
		dir[i] = dir[r];
		dir[r] = tmp;
	}
}

void Map::Carve(int x, int y)
{
	int dir[4] = { 0,1,2,3 };
	ShuffleDir(dir);

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[dir[i]] * 2;
		int ny = y + dy[dir[i]] * 2;

		// 범위 체크
		if (nx > 0 && nx < Width - 1 && ny > 0 && ny < Height - 1)
		{
			if (Maze[ny][nx] == Wall)	// 방문 안 한 경우
			{
				// 벽 허물기
				Maze[y + dy[dir[i]]][x + dx[dir[i]]] = Path;
				Maze[ny][nx] = Path;
				// 중간 출력 테스트
				//for (int y = 0; y < Height; y++)
				//{
				//	for (int x = 0; x < Width; x++)
				//	{
				//		printf("%d ", Maze[y][x]);
				//	}
				//	printf("\n");
				//}
				//int tmp = getchar();
				Carve(nx, ny);
			}
		}
	}
}

void Map::GenerateMap()
{
	srand(time(0));
	//printf("미로의 가로와 세로 길이를 입력하세요 : ");
	//std::cin >> Width >> Height;
	Width = 20, Height = 10;

	// 입력된 너비와 높이가 최대치보다 클 경우
	//if (Width > MAX) Width = MAX;
	//if (Height > MAX) Height = MAX;

	// 벽 허무는 경계를 위해 값 설정
	if (Width % 2 == 0) Width--;
	if (Height % 2 == 0) Height--;

	// 전체 벽으로 초기화
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			Maze[y][x] = Wall;
		}
	}

	// 미로 초기화 테스트
	//for (int y = 0; y < Height; y++)
	//{
	//	for (int x = 0; x < Width; x++)
	//	{
	//		printf("%d ", Maze[y][x]);
	//	}
	//	printf("\n");
	//}
	//int tmp = getchar();

	// 시작점 설정
	Maze[1][1] = Start;
	Carve(1, 1);

	// 출구 설정
	SetExitPoint();
	// 열쇠 위치 설정
	SetKeyPoint();
}

void Map::SetExitPoint()
{
	std::vector<Position> ExitPoint;

	for (int y = 1; y < Height - 1; y++)
	{
		for (int x = 1; x < Width - 1; x++)
		{
			if (x > 10 && Maze[y][x] == Path)
			{
				// 막다른 길인지 확인
				int cnt = 0;
				for (int d = 0; d < 4; d++)
				{
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx >= 0 && nx < Width && ny >= 0 && ny < Height)
					{
						if (Maze[ny][nx] == Path || Maze[ny][nx] == Start)
							cnt++;
					}
				}

				if (cnt == 1) // 길이 하나뿐이면 막다른 길
				{
					ExitPoint.push_back({ x, y });
				}
			}
		}
	}

	if (!ExitPoint.empty())
	{
		int r = rand() % ExitPoint.size();
		Maze[ExitPoint[r].y][ExitPoint[r].x] = End;
	}
}

void Map::SetKeyPoint()
{
	std::vector<Position> KeyPoint;

	for (int y = 1; y < Height - 1; y++)
	{
		for (int x = 1; x < Width - 1; x++)
		{
			if (Maze[y][x] == Path)
			{
				// 막다른 길인지 검사
				int cnt = 0;
				for (int d = 0; d < 4; d++)
				{
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx >= 0 && nx < Width && ny >= 0 && ny < Height)
					{
						if (Maze[ny][nx] == Path || Maze[ny][nx] == Start)
							cnt++;
					}
				}

				if (cnt == 1) // 막다른 길
				{
					// 출구랑 겹치면 안 됨
					if (Maze[y][x] != End)
						KeyPoint.push_back({ x, y });
				}
			}
		}
	}

	if (!KeyPoint.empty())
	{
		int r = rand() % KeyPoint.size();
		Maze[KeyPoint[r].y][KeyPoint[r].x] = Key;
	}
	else
	{
		printf("조건에 맞는 열쇠 후보가 없습니다!\n");
	}
}

void Map::FindStartPosition(Position& OutPosition)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
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

void Map::PrintMap(Position& position)
{
	// 미로 출력
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (position.x == x && position.y == y)
				printf("P ");
			else if (Maze[y][x] == Wall)
				printf("# ");
			else if (Maze[y][x] == Path)
				printf(". ");
			else if (Maze[y][x] == Start)
				printf("S ");
			else if (Maze[y][x] == End)
				printf("E ");
			else if (Maze[y][x] == Key)
				printf("K ");
		}
		printf("\n");
	}
}
