#pragma once
#include "Map.h"
#include "Position.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"

class GameManager
{
public:
	/// <summary>
	/// 게임 플레이 함수
	/// </summary>
	void PlayGame();
	/// <summary>
	/// 시작 위치를 설정하는 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	/// <summary>
	/// 시작 위치를 설정하는 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 좌표</param>
	void FindStartPosition(Position& OutPosition);
	/// <summary>
	/// 이동할 수 있는 방향을 탐색하는 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 좌표</param>
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
	/// 플레이어가 출구에 도달했는지 확인하는 여부
	/// </summary>
	/// <param name="pPlayer">플레이어 좌표</param>
	/// <returns>출구 도달 여부</returns>
	bool IsEnd(Position& position);
	/// <summary>
	/// 플레이어가 열쇠 좌표에 도달했는지 확인하는 여부
	/// </summary>
	/// <param name="position"플레이어 좌표</param>
	/// <returns>열쇠 위치 도달 여부</returns>
	bool IsKey(Position& position);
	/// <summary>
	/// 비트플래그 연산을 통해 이동 방향을 계산하는 함수
	/// </summary>
	/// <param name="MoveFlags">이동 가능한 방향을 나타내는 비트플래그</param>
	/// <returns>키보드 입력에 따른 이동 방향</returns>
	MoveDirection GetMoveInput(int MoveFlags);
	/// <summary>
	/// 움직임 이벤트 처리
	/// </summary>
	/// <param name="Player">플레이어 구조체</param>
	/// <param name="InStage">스테이지 단계</param>
	void MoveEventProcess(Player& Player, int InStage);
	/// <summary>
	/// 랜덤으로 나오는 적과의 전투 함수
	/// </summary>
	/// <param name="pPlayer">플레이어 구조체</param>
	void BattleEvent(Player& Player, int InStage);
	/// <summary>/// 
	/// 랜덤으로 나오는 상점 이벤트 함수
	/// </summary>/// 
	/// <param name="pEnemy">플레이어 구조체</param>
	void ShopEvent(Player& Player);
	/// <summary>
	/// 랜덤으로 나오는 보물상자 이벤트 함수
	/// </summary>
	/// <param name="Player">플레이어 구조체</param>
	void BoxEvent(Player& Player);
private:
	Map Map;	// 맵 클래스
	int Stage = 0;	// 스테이지 단계
	bool HasKey = false;	// 열쇠 보유 여부
	static constexpr int MaxStage = 3;	// 최대 스테이지 개수
};

