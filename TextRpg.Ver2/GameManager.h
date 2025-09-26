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
	/// ���� �÷��� �Լ�
	/// </summary>
	void PlayGame();
	/// <summary>
	/// ���� ��ġ�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	/// <summary>
	/// ���� ��ġ�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ��ǥ</param>
	void FindStartPosition(Position& OutPosition);
	/// <summary>
	/// �̵��� �� �ִ� ������ Ž���ϴ� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ��ǥ</param>
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
	/// �÷��̾ �ⱸ�� �����ߴ��� Ȯ���ϴ� ����
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ��ǥ</param>
	/// <returns>�ⱸ ���� ����</returns>
	bool IsEnd(Position& position);
	/// <summary>
	/// �÷��̾ ���� ��ǥ�� �����ߴ��� Ȯ���ϴ� ����
	/// </summary>
	/// <param name="position"�÷��̾� ��ǥ</param>
	/// <returns>���� ��ġ ���� ����</returns>
	bool IsKey(Position& position);
	/// <summary>
	/// ��Ʈ�÷��� ������ ���� �̵� ������ ����ϴ� �Լ�
	/// </summary>
	/// <param name="MoveFlags">�̵� ������ ������ ��Ÿ���� ��Ʈ�÷���</param>
	/// <returns>Ű���� �Է¿� ���� �̵� ����</returns>
	MoveDirection GetMoveInput(int MoveFlags);
	/// <summary>
	/// ������ �̺�Ʈ ó��
	/// </summary>
	/// <param name="Player">�÷��̾� ����ü</param>
	/// <param name="InStage">�������� �ܰ�</param>
	void MoveEventProcess(Player& Player, int InStage);
	/// <summary>
	/// �������� ������ ������ ���� �Լ�
	/// </summary>
	/// <param name="pPlayer">�÷��̾� ����ü</param>
	void BattleEvent(Player& Player, int InStage);
	/// <summary>/// 
	/// �������� ������ ���� �̺�Ʈ �Լ�
	/// </summary>/// 
	/// <param name="pEnemy">�÷��̾� ����ü</param>
	void ShopEvent(Player& Player);
	/// <summary>
	/// �������� ������ �������� �̺�Ʈ �Լ�
	/// </summary>
	/// <param name="Player">�÷��̾� ����ü</param>
	void BoxEvent(Player& Player);
private:
	Map Map;	// �� Ŭ����
	int Stage = 0;	// �������� �ܰ�
	bool HasKey = false;	// ���� ���� ����
	static constexpr int MaxStage = 3;	// �ִ� �������� ����
};

