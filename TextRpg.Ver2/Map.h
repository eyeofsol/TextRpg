#pragma once
#include<cstdint>
#include "Position.h"

enum MapTile	// �� Ÿ��
{
	Path = 0,
	Wall = 1,
	Start = 2,
	End = 3,
	Key = 4
};

enum MoveDirection	// �̵� ���� ��Ʈ�÷���
{
	DirNone = 0,
	DirUp = 1 << 0,
	DirDown = 1 << 1,
	DirLeft = 1 << 2,
	DirRight = 1 << 3
};

class Map
{
public:
	/// <summary>
	/// �������� ������ ���� �Լ�
	/// </summary>
	/// <param name="dir">���� �迭</param>
	void ShuffleDir(int dir[]);
	/// <summary>
	/// �����ִ� ���� ������ �������� �̵��Ͽ� ��η� �վ��ִ� ����Լ�
	/// </summary>
	/// <param name="x">������� ���� ��ġ�� x��ǥ</param>
	/// <param name="y">������� ���� ��ġ�� y��ǥ</param>
	void Carve(int x, int y);
	/// <summary>
	/// ���� �ʱ�ȭ �ϴ� �Լ�
	/// </summary>
	void GenerateMap();
	/// <summary>
	/// �ⱸ�� �����ϴ� �Լ�
	/// </summary>
	void SetExitPoint();
	/// <summary>
	/// ������ ��ġ�� �����ϴ� �Լ�
	/// </summary>
	void SetKeyPoint();
	/// <summary>
	/// �÷��̾ ���� ��ġ�� �����ϴ� �Լ�
	/// </summary>
	void FindStartPosition(Position& OutPosition);
	/// <summary>
	/// �÷��̾��� ��ǥ�� �޾� ���� ����ϴ� �Լ�
	/// </summary>
	/// <param name="position">�÷��̾��� ��ǥ</param>
	void PrintMap(Position& position);
	/// <summary>
	/// �÷��̾ ���踦 ȹ�� �� �ʿ��� �����ϴ� �Լ�
	/// </summary>
	/// <param name="InX">������ X��ǥ</param>
	/// <param name="InY">������ Y��ǥ</param>
	inline void PickupKey(int InX,int InY) { Maze[InY][InX] = Path; }
	
	inline int GetWidth() { return Width; }
	inline int GetHeight() { return Height; }
	inline int GetMaze(int InX,int InY) { return Maze[InX][InY]; }
private:

	static constexpr int MaxSize = 51;	// �ִ� �̷� ũ��
	int Maze[MaxSize][MaxSize];	// �̷� ����ü
	int Width = 20, Height = 10;	// �ʺ�, ����

	// ����(��, ��, ��, ��)
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { -1,1,0,0 };
};

