#pragma once
#include "Position.h"
#include "Actor.h"

class APlayer : public Actor
{
public:
	APlayer() = default;
	APlayer(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}
	virtual void Attack() override;

	inline void AddGold(int InGold) { Gold += InGold; }
	inline int& GetGold() { return Gold; }
	inline Position& GetPosition() { return CurrentPosition; }

	virtual ~APlayer() {}
protected:
	Position CurrentPosition = Position(0, 0);
	int Gold = 0;
};

