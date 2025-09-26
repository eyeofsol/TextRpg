#pragma once
#include <string>
#include "Position.h"
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster() : Actor("몬스터", 30.0f, 5.0f) {}
	Monster(const char* InName) : Actor(InName, 30.0f, 5.0f) {}
	Monster(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}
	virtual void Attack() override;
	virtual void PrintStatus() override;
	virtual void Skill(ICanBattle* InTarget) {};	// 몬스터 발동 스킬

	inline int GetDropGold() const { return DropGold; }
	inline int GetDropExp() const { return DropExp; }

	virtual ~Monster() {}
protected:
	int DropGold = rand() % 20 + 10;	// 드랍 골드
	int DropExp = rand() % 5 + 10;	// 드랍 경험치
};

