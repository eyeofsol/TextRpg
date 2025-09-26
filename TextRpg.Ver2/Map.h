#pragma once
#include<cstdint>
#include "Position.h"

enum MapTile	// 맵 타일
{
	Path = 0,
	Wall = 1,
	Start = 2,
	End = 3,
	Key = 4
};

enum MoveDirection	// 이동 방향 비트플래그
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
	/// 랜덤으로 방향을 섞는 함수
	/// </summary>
	/// <param name="dir">방향 배열</param>
	void ShuffleDir(int dir[]);
	/// <summary>
	/// 막혀있는 벽을 랜덤한 방향으로 이동하여 통로로 뚫어주는 재귀함수
	/// </summary>
	/// <param name="x">현재까지 뚫은 위치의 x좌표</param>
	/// <param name="y">현재까지 뚫은 위치의 y좌표</param>
	void Carve(int x, int y);
	/// <summary>
	/// 맵을 초기화 하는 함수
	/// </summary>
	void GenerateMap();
	/// <summary>
	/// 출구를 설정하는 함수
	/// </summary>
	void SetExitPoint();
	/// <summary>
	/// 열쇠의 위치를 설정하는 함수
	/// </summary>
	void SetKeyPoint();
	/// <summary>
	/// 플레이어를 시작 위치로 설정하는 함수
	/// </summary>
	void FindStartPosition(Position& OutPosition);
	/// <summary>
	/// 플레이어의 좌표를 받아 맵을 출력하는 함수
	/// </summary>
	/// <param name="position">플레이어의 좌표</param>
	void PrintMap(Position& position);
	/// <summary>
	/// 플레이어가 열쇠를 획득 시 맵에서 삭제하는 함수
	/// </summary>
	/// <param name="InX">열쇠의 X좌표</param>
	/// <param name="InY">열쇠의 Y좌표</param>
	inline void PickupKey(int InX,int InY) { Maze[InY][InX] = Path; }
	
	inline int GetWidth() { return Width; }
	inline int GetHeight() { return Height; }
	inline int GetMaze(int InX,int InY) { return Maze[InX][InY]; }
private:

	static constexpr int MaxSize = 51;	// 최대 미로 크기
	int Maze[MaxSize][MaxSize];	// 미로 구조체
	int Width = 20, Height = 10;	// 너비, 높이

	// 방향(상, 하, 좌, 우)
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { -1,1,0,0 };
};

