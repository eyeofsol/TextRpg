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
		// 모든 스킬 정의
		AllSkills = {
			{"연속 베기","15의 마나를 소모하여 두 번 공격합니다.\n", 1, 3, 15, false},
			{"방패 올리기","10의 마나를 소모하여 3턴 동안 받는 피해를 절반으로 감소시킵니다.\n", 2, 5, 10, false},
			{"광폭화","30의 마나를 소모하여 5턴동안 공격력을 2배로 증가시킵니다.\n", 3, 7, 30, false}
		};
	}
	virtual void Attack() override;
	virtual void PrintStatus() override;

	// 전투 종료 함수
	void AddGold(int InGold);
	void AddExp(int InExp);
	void Levelup();

	// 스킬 함수
	void UseSkill(ICanBattle* InTarget, bool* Select);
	void PrintSkill();
	void DoubleAttack(ICanBattle* InTarget);
	void SetGuard(int InTurn); 
	void UpdateGuard();
	void SetBerserk(int InTure);
	void UpdateBerserk();
	void ResetStatus();
	
	// 인벤토리 함수
	void AddItem(const ItemInfo& Item);
	void OpenInventory(bool* Select);
	void UseItem(const ItemInfo& Item);

	// 체크 및 Get,Set함수
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

