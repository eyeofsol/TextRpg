#pragma once
#include "Position.h"
#include "PlayerData.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"

enum class MazeTile
{
	Path = 0,
	Wall = 1,
	Start = 2,
	End = 3
};

enum class MoveDirection
{
	DirNone = 0,
	DirUp = 1 << 0,
	DirDown = 1 << 1,
	DirLeft = 1 << 2,
	DirRight = 1 << 3
};

inline bool operator==(int Left, MazeTile Right)
{
	return Left == static_cast<int>(Right);
}
inline bool operator==(MazeTile Left, int Right)
{
	return static_cast<int>(Left) == Right;
}
inline bool operator!=(int Left, MazeTile Right)
{
	return Left != static_cast<int>(Right);
}
inline int& operator|=(int& Left, MoveDirection Right)
{
	Left = Left | static_cast<int>(Right);
	return Left;
}
inline bool operator&(int Left, MoveDirection Right)
{
	return Left & static_cast<int>(Right);
}

class GameManager
{
public:
	/// <summary>
/// �̷� ������ �ʱ�ȭ �ϴ� �Լ�
/// </summary>
	void InitializeMaze();
	/// <summary>
	/// �̷� ������ �����ϴ� �Լ�
	/// </summary>
	void MazeEscapeRun();
	/// <summary>///
	/// �̷� ������ �����ϴ� �Լ�(�Ҵ�� �޸𸮸� �����ϴ� �Լ�)
	/// </summary> ///
	void ClearMaze();

	/// <summary>/// 
	/// �� ������ �д� �Լ�
	/// </summary>///
	/// <param name="MapFileName">�� ���� �̸�</param>
	/// <param name="OutDataString">��¿�. ���Ͽ��� ���� �ؽ�Ʈ�� �����ش�.</param>
	/// <returns>������ �дµ� �����ϸ� true, �����ϸ� false</returns>
	bool ReadMapFile(const char* MapFileName, std::string& OutDataString);
	/// <summary>///
	/// string�� �޾Ƽ� Mase�� ä��µ� �ʿ��� �����͸� �Ľ��ϴ� �Լ�
	/// </summary>/// 
	/// <param name="OutDataString">�ҽ��� ���ڿ�</param>
	/// <returns>true : �Ľ̼���, false : �ʵ�����(DataString)�� �߸��� ���</returns>
	bool ParseMapData(std::string& DataString);

	/// <summary>
	/// TargetString���� TargetCharacter�� �� ��° �ִ��� ã���ִ� �Լ�
	/// </summary>
	/// <param name="TargetString">ã���� ���ڿ�</param>
	/// <param name="TargetCharacter">ã�� ����</param>
	/// <returns>-1�̸� ��ã��, �� �ܴ� TargetCharacter�� �ε���</returns>
	int FindCharIndex(const char* TargetString, const char TargetCharacter);
	/// <summary>///
	/// Source���� �߰ߵ� ù���� �����ϴ� �Լ�
	/// </summary>/// 
	/// <param name="Source">��(\n)�� ã�� ���� ������</param>
	/// <returns>Source���� ù���� �ּ�</returns>
	char* GetLine(char** InOutSource);
	/// <summary>/// 
	/// ���ڿ� ������ �Ľ��ϴ� �Լ�
	/// </summary>/// 
	/// <param name="LineData">�Ľ��� ���ڿ�</param>
	/// <param name="Size">����� ����� �迭�� ũ��</param>
	/// <param name="OutArray">����� ����� �迭</param>
	void ParseLineData(const char* LineData, int ArraySize, int* OutArray);

	/// <summary>
	/// �̷θ� ����ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	void PrintMaze(Position& position1, Position& position2);
	/// <summary>
	/// ���� ��ġ�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	void FindStartPosition(Position& OutPosition);
	/// <summary>
	/// ������ ���� ��ġ�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">���� ����ü</param>
	void InitializeMonster(Position& OutPositions);
	/// <summary>
	/// �̵��� �� �ִ� ������ Ž���ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	/// <returns>��Ʈ�÷��� �˻縦 ���� �� �� �ִ� �ൿ�� �˻��� ��Ʈ�÷��� ��ȯ</returns>
	int PrintAvailableMoves(Position& position);
	/// <summary>
	/// ������ ��ǥ�� ������ Ȯ���ϴ� �Լ�
	/// </summary>
	/// <param name="X">��ǥ�� X��</param>
	/// <param name="Y">��ǥ�� Y��</param>
	/// <returns>���� ����</returns>
	bool IsWall(int X, int Y);
	/// <summary>
	/// ������ ��ǥ�� ������� Ȯ���ϴ� �Լ�
	/// </summary>
	/// <param name="X">��ǥ�� X��</param>
	/// <param name="Y">��ǥ�� Y��</param>
	/// <returns>���� ����</returns>
	bool IsPath(int X, int Y);
	/// <summary>
	/// �÷��̾ �ⱸ�� �����ߴ��� Ȯ���ϴ� ����
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	/// <returns>�ⱸ ���� ����</returns>
	bool IsEnd(Position& position);
	/// <summary>
	/// �÷��̾ ���� �������� Ȯ���ϴ� ����
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	/// <returns>�� ���� ����</returns>
	bool IsBattle(Position& Pposition, Position& Rposition);
	/// <summary>
	/// ��Ʈ�÷��� ������ ���� �̵� ������ ����ϴ� �Լ�
	/// </summary>
	/// <param name="MoveFlags">�̵� ������ ������ ��Ÿ���� ��Ʈ�÷���</param>
	/// <returns>Ű���� �Է¿� ���� �̵� ����</returns>
	MoveDirection GetMoveInput(int MoveFlags);
	/// <summary>
	/// ���� �̵� �Լ�
	/// </summary>
	/// <param name="Monster">���� ����ü</param>
	void MonsterMove(Monster* Monster);

	void MoveEventProcess(APlayer& Player);
	/// <summary>
	/// �������� ������ ������ ���� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	void BattleEvent(APlayer& Player, Monster* MonsterPos);
	/// <summary>/// 
	/// �������� ������ ȸ�� �̺�Ʈ �Լ�
	/// </summary>/// 
	/// <param name="pEnemy">�÷��̾� ����ü</param>
	void HealerEvent(APlayer& Player);

protected:
	const char* DirectoryName = ".\\Data\\";

	int MazeWidth = 20;
	int MazeHeight = 10;
	int** Maze = nullptr;
};