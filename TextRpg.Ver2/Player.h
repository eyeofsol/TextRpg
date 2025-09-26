#pragma once
#include "Position.h"
#include "Actor.h"
#include "ItemInfo.h"
#include <vector>
#include <map>

struct SkillInfo	// ��ų ����ü
{
	std::string Name;	// �̸�
	std::string Detail;	// ����
	int SkillNum;		// ��ų ��ȣ
	int RequiredLevel;	// ��ų�� ���� ���� �ʿ��� ����
	int ManaCost;		// �Ҹ� ����
	bool Learned = false;	// ��ų�� ������� ����
};

class Player : public Actor
{
public:
	Player() = default;
	Player(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
		// ��� ��ų ����
		AllSkills = {
			{"���� ����","15�� ������ �Ҹ��Ͽ� �� �� �����մϴ�.\n", 1, 3, 15, false},
			{"���� �ø���","10�� ������ �Ҹ��Ͽ� 3�� ���� �޴� ���ظ� �������� ���ҽ�ŵ�ϴ�.\n", 2, 5, 10, false},
			{"����ȭ","30�� ������ �Ҹ��Ͽ� 5�ϵ��� ���ݷ��� 2��� ������ŵ�ϴ�.\n", 3, 7, 30, false}
		};
	}
	virtual void Attack() override;
	virtual void PrintStatus() override;

	// ���� ���� �Լ�
	void AddGold(int InGold);	// ��� ȹ��
	void AddExp(int InExp);		// ����ġ ȹ��
	void Levelup();				// ���� ��

	// ��ų �Լ�
	void UseSkill(ICanBattle* InTarget, bool* Select);	// ��ų ���
	void PrintSkill();	// ��� ������ ��ų ��� ���
	void DoubleAttack(ICanBattle* InTarget);	// ���� ���� ��ų
	void SetGuard(int InTurn);	// ���� �ø��� ��ų
	void UpdateGuard();	// ���� �� ���
	void SetBerserk(int InTure);	// ����ȭ ��ų
	void UpdateBerserk();	// ����ȭ �� ���
	void ResetStatus();	// ��Ʋ ���� �� �ʱ�ȭ �Լ�
	
	// �κ��丮 �Լ�
	void AddItem(const ItemInfo& Item);	// �κ��丮�� ������ �߰�
	void OpenInventory(bool* Select);	// �κ��丮 ����
	void UseItem(const ItemInfo& Item,bool* Select);	// �κ��丮�� ������ ���
	void UsePassive(const ItemInfo& Item);	// �нú� ������ ȹ��� �ٷ� ���

	// üũ �� Get,Set�Լ�
	inline bool CheckGuard() const { return IsGuard; }
	inline bool CheckBerserker() const { return IsBerserk; }
	inline int& GetGold() { return Gold; }
	inline int& GetMana() { return Mana; }
	inline Position& GetPosition() { return CurrentPosition; }
	inline void AddAttackPower(float InAttackPower)
	{
		AttackPower += InAttackPower;
	}
	inline void SetMana(int InMana)
	{
		Mana += InMana;
		if (Mana > MaxMana)
		{
			Mana = MaxMana;
		}
	}

	virtual ~Player() {}
protected:

	Position CurrentPosition = Position(0, 0);	// �÷��̾� ��ǥ
	int Gold = 50;	// ���� ���
	int Level = 1;	// ����
	int Exp = 0;	// ����ġ
	int MaxExp = 30;	// �ִ� ����ġ
	int MaxMana = 50;	// �ִ� ����
	int Mana = MaxMana;	// ����

	std::vector<SkillInfo> AllSkills;	// ��ų ����
	bool IsGuard = false;	// ���� ����
	bool IsBerserk = false;	// ����ȭ ����
	int GuardTurn = 0;	// ���� ���� ��
	int BerserkTurn = 0;	// ����ȭ ���� ��

	std::map<std::string, std::pair<ItemInfo, int>> Inventory;	// �κ��丮 ��
};

