#include "Map.h"
#include<iostream>
#include<stdio.h>
#include<time.h>
#include<random>

void Map::ShuffleDir(int dir[])	// ���� �˰���
{
	for (int i = 0; i < 4; i++)
	{
		int r = rand() % 4;
		int tmp = dir[i];
		dir[i] = dir[r];
		dir[r] = tmp;
	}
}

void Map::Carve(int x, int y)	// �����ϰ� ���� �㹫�� �Լ�
{
	int dir[4] = { 0,1,2,3 };
	ShuffleDir(dir);	// ���� ����

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[dir[i]] * 2;	// �¿� ���
		int ny = y + dy[dir[i]] * 2;	// ���� ���

		// ���� üũ
		if (nx > 0 && nx < Width - 1 && ny > 0 && ny < Height - 1)
		{
			if (Maze[ny][nx] == Wall)	// �湮 �� �� ���
			{
				// �� �㹰��
				Maze[y + dy[dir[i]]][x + dx[dir[i]]] = Path;
				Maze[ny][nx] = Path;
				// �߰� ��� �׽�Ʈ
				//for (int y = 0; y < Height; y++)
				//{
				//	for (int x = 0; x < Width; x++)
				//	{
				//		printf("%d ", Maze[y][x]);
				//	}
				//	printf("\n");
				//}
				//int tmp = getchar();
				Carve(nx, ny);	// ��� ����
			}
		}
	}
}

void Map::GenerateMap()	//	�� ����
{
	srand(time(0));
	//printf("�̷��� ���ο� ���� ���̸� �Է��ϼ��� : ");
	//std::cin >> Width >> Height;
	Width = 20, Height = 10;

	// �Էµ� �ʺ�� ���̰� �ִ�ġ���� Ŭ ���
	//if (Width > MAX) Width = MAX;
	//if (Height > MAX) Height = MAX;

	// �� �㹫�� ��踦 ���� �� ����
	if (Width % 2 == 0) Width--;
	if (Height % 2 == 0) Height--;

	// ��ü ������ �ʱ�ȭ
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			Maze[y][x] = Wall;
		}
	}

	// �̷� �ʱ�ȭ �׽�Ʈ
	//for (int y = 0; y < Height; y++)
	//{
	//	for (int x = 0; x < Width; x++)
	//	{
	//		printf("%d ", Maze[y][x]);
	//	}
	//	printf("\n");
	//}
	//int tmp = getchar();

	// ������ ����
	Maze[1][1] = Start;
	Carve(1, 1);

	// �ⱸ ����
	SetExitPoint();
	// ���� ��ġ ����
	SetKeyPoint();
}

void Map::SetExitPoint()	// �ⱸ ����
{
	std::vector<Position> ExitPoint;	// �ⱸ ���� ��ǥ ����

	for (int y = 1; y < Height - 1; y++)
	{
		for (int x = 1; x < Width - 1; x++)
		{
			if (x > 10 && Maze[y][x] == Path)
			{
				// ���ٸ� ������ Ȯ��
				int Count = 0;
				for (int d = 0; d < 4; d++)
				{
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx >= 0 && nx < Width && ny >= 0 && ny < Height)
					{
						if (Maze[ny][nx] == Path || Maze[ny][nx] == Start)	// �����¿쿡 ���̳� �������� ������ Count++
							Count++;
					}
				}

				if (Count == 1) // ���� �ϳ����̸� ���ٸ� ��
				{
					ExitPoint.push_back({ x, y });	// ���Ϳ� �Է�
				}
			}
		}
	}

	if (!ExitPoint.empty())	// �ⱸ �ĺ����� �ִٸ�
	{
		int r = rand() % ExitPoint.size();	// ������ ��ǥ �̱�
		Maze[ExitPoint[r].y][ExitPoint[r].x] = End;	// �ش� ��ǥ�� �ⱸ�� ����
	}
}

void Map::SetKeyPoint()	// ���� ��ġ ����
{
	std::vector<Position> KeyPoint;	// ���� ��ġ ���� ��ǥ ����

	for (int y = 1; y < Height - 1; y++)
	{
		for (int x = 1; x < Width - 1; x++)
		{
			if (Maze[y][x] == Path)
			{
				// ���ٸ� ������ �˻�
				int Count = 0;
				for (int d = 0; d < 4; d++)
				{
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx >= 0 && nx < Width && ny >= 0 && ny < Height)
					{
						if (Maze[ny][nx] == Path || Maze[ny][nx] == Start)	// �����¿쿡 ���̳� �������� ������ Count++
							Count++;
					}
				}

				if (Count == 1) // ���ٸ� ��
				{
					// �ⱸ�� ��ġ�� �� ��
					if (Maze[y][x] != End)
						KeyPoint.push_back({ x, y });
				}
			}
		}
	}

	if (!KeyPoint.empty())	// ���� ��ǥ �ĺ����� �ִٸ�
	{
		int r = rand() % KeyPoint.size();	// ������ ��ǥ �̱�
		Maze[KeyPoint[r].y][KeyPoint[r].x] = Key;	// �ش� ��ǥ�� ���� ��ġ�� ����
	}
}

void Map::FindStartPosition(Position& OutPosition)	// �÷��̾��� ���� ��ġ ����
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (Maze[y][x] == MapTile::Start)
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
	// �̷� ���
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
