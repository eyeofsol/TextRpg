#pragma once
#include <string>
#include "Position.h"
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster() : Actor("����", 30.0f, 5.0f) {}
	Monster(const char* InName) : Actor(InName, 30.0f, 5.0f) {}
	Monster(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}
	virtual void Attack() override;
	virtual void PrintStatus() override;
	virtual void Skill(ICanBattle* InTarget) {};	// ���� �ߵ� ��ų

	inline int GetDropGold() const { return DropGold; }
	inline int GetDropExp() const { return DropExp; }

	virtual ~Monster() {}
protected:
	int DropGold = rand() % 20 + 10;	// ��� ���
	int DropExp = rand() % 5 + 10;	// ��� ����ġ
};

