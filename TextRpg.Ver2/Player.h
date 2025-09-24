#pragma once
#include "Position.h"
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = default;
	Player(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}
	virtual void Attack() override;

	inline void AddGold(int InGold) { Gold += InGold; }
	inline int& GetGold() { return Gold; }
	inline Position& GetPosition() { return CurrentPosition; }

	virtual ~Player() {}
protected:
	Position CurrentPosition = Position(0, 0);
	int Gold = 0;
};

