#pragma once
#include "Position.h"
#include "Actor.h"
#include "ItemInfo.h"
#include <vector>
#include <map>

struct SkillInfo
{
	std::string Name;
	std::string Detail;
	int SkillNum;
	int RequiredLevel;
	int ManaCost;
	bool Learned = false;
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
	void AddGold(int InGold);
	void AddExp(int InExp);
	void Levelup();

	// ��ų �Լ�
	void UseSkill(ICanBattle* InTarget, bool* Select);
	void PrintSkill();
	void DoubleAttack(ICanBattle* InTarget);
	void SetGuard(int InTurn); 
	void UpdateGuard();
	void SetBerserk(int InTure);
	void UpdateBerserk();
	void ResetStatus();
	
	// �κ��丮 �Լ�
	void AddItem(const ItemInfo& Item);
	void OpenInventory(bool* Select);
	void UseItem(const ItemInfo& Item);

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

	Position CurrentPosition = Position(0, 0);
	int Gold = 0;
	int Level = 1;
	int Exp = 0;
	int MaxExp = 30;
	int MaxMana = 50;
	int Mana = MaxMana;

	std::vector<SkillInfo> AllSkills;
	bool IsGuard = false;
	bool IsBerserk = false;
	int GuardTurn = 0;
	int BerserkTurn = 0;

	std::map<std::string, std::pair<ItemInfo, int>> Inventory;
};

