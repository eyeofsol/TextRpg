#pragma once
#include <string>
#include "Position.h"
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster() : Actor("∏ÛΩ∫≈Õ", 30.0f, 5.0f) {}
	Monster(const char* InName) : Actor(InName, 30.0f, 5.0f) {}
	Monster(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}
	virtual void Attack() override;
	virtual void Skill(ICanBattle* InTarget) {};

	inline int GetDropGold() const { return DropGold; }
	inline Position& GetPosition() { return CurrentPosition; }

	virtual ~Monster() {}
protected:
	Position CurrentPosition = Position(0, 0);
	int DropGold = 10;
};

