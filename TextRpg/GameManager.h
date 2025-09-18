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
/// 미로 게임을 초기화 하는 함수
/// </summary>
	void InitializeMaze();
	/// <summary>
	/// 미로 게임을 시작하는 함수
	/// </summary>
	void MazeEscapeRun();
	/// <summary>///
	/// 미로 게임을 정리하는 함수(할당된 메모리를 해제하는 함수)
	/// </summary> ///
	void ClearMaze();

	/// <summary>/// 
	/// 맵 파일을 읽는 함수
	/// </summary>///
	/// <param name="MapFileName">맵 파일 이름</param>
	/// <param name="OutDataString">출력용. 파일에서 읽은 텍스트를 돌려준다.</param>
	/// <returns>파일을 읽는데 성공하면 true, 실패하면 false</returns>
	bool ReadMapFile(const char* MapFileName, std::string& OutDataString);
	/// <summary>///
	/// string을 받아서 Mase를 채우는데 필요한 데이터를 파싱하는 함수
	/// </summary>/// 
	/// <param name="OutDataString">소스용 문자열</param>
	/// <returns>true : 파싱성공, false : 맵데이터(DataString)가 잘못된 경우</returns>
	bool ParseMapData(std::string& DataString);

	/// <summary>
	/// TargetString에서 TargetCharacter가 몇 번째 있는지 찾아주는 함수
	/// </summary>
	/// <param name="TargetString">찾아질 문자열</param>
	/// <param name="TargetCharacter">찾을 글자</param>
	/// <returns>-1이면 못찾음, 그 외는 TargetCharacter의 인덱스</returns>
	int FindCharIndex(const char* TargetString, const char TargetCharacter);
	/// <summary>///
	/// Source에서 발견된 첫줄을 리턴하는 함수
	/// </summary>/// 
	/// <param name="Source">줄(\n)을 찾을 원본 데이터</param>
	/// <returns>Source에서 첫줄의 주소</returns>
	char* GetLine(char** InOutSource);
	/// <summary>/// 
	/// 문자열 한줄을 파싱하는 함수
	/// </summary>/// 
	/// <param name="LineData">파싱할 문자열</param>
	/// <param name="Size">결과가 저장될 배열의 크기</param>
	/// <param name="OutArray">결과가 저장될 배열</param>
	void ParseLineData(const char* LineData, int ArraySize, int* OutArray);

	/// <summary>
	/// 미로를 출력하는 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	void PrintMaze(Position& position1, Position& position2);
	/// <summary>
	/// 시작 위치를 설정하는 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	void FindStartPosition(Position& OutPosition);
	/// <summary>
	/// 몬스터의 시작 위치를 설정하는 함수
	/// </summary>
	/// <param name="pPlayer">몬스터 구조체</param>
	void InitializeMonster(Position& OutPositions);
	/// <summary>
	/// 이동할 수 있는 방향을 탐색하는 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	/// <returns>비트플래그 검사를 통해 할 수 있는 행동을 검사한 비트플래그 반환</returns>
	int PrintAvailableMoves(Position& position);
	/// <summary>
	/// 지정된 좌표가 벽인지 확인하는 함수
	/// </summary>
	/// <param name="X">좌표의 X값</param>
	/// <param name="Y">좌표의 Y값</param>
	/// <returns>벽의 여부</returns>
	bool IsWall(int X, int Y);
	/// <summary>
	/// 지정된 좌표가 통로인지 확인하는 함수
	/// </summary>
	/// <param name="X">좌표의 X값</param>
	/// <param name="Y">좌표의 Y값</param>
	/// <returns>벽의 여부</returns>
	bool IsPath(int X, int Y);
	/// <summary>
	/// 플레이어가 출구에 도달했는지 확인하는 여부
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	/// <returns>출구 도달 여부</returns>
	bool IsEnd(Position& position);
	/// <summary>
	/// 플레이어가 적을 만났는지 확인하는 여부
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	/// <returns>적 출현 여부</returns>
	bool IsBattle(Position& Pposition, Position& Rposition);
	/// <summary>
	/// 비트플래그 연산을 통해 이동 방향을 계산하는 함수
	/// </summary>
	/// <param name="MoveFlags">이동 가능한 방향을 나타내는 비트플래그</param>
	/// <returns>키보드 입력에 따른 이동 방향</returns>
	MoveDirection GetMoveInput(int MoveFlags);
	/// <summary>
	/// 몬스터 이동 함수
	/// </summary>
	/// <param name="Monster">몬스터 구조체</param>
	void MonsterMove(Monster* Monster);

	void MoveEventProcess(APlayer& Player);
	/// <summary>
	/// 랜덤으로 나오는 적과의 전투 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	void BattleEvent(APlayer& Player, Monster* MonsterPos);
	/// <summary>/// 
	/// 랜덤으로 나오는 회복 이벤트 함수
	/// </summary>/// 
	/// <param name="pEnemy">플레이어 구조체</param>
	void HealerEvent(APlayer& Player);

protected:
	const char* DirectoryName = ".\\Data\\";

	int MazeWidth = 20;
	int MazeHeight = 10;
	int** Maze = nullptr;
};