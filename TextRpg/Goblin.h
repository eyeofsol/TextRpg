#pragma once
#include"Monster.h"

class Goblin : public Monster
{
public:
	virtual void Attack() override;
	virtual void Skill(ICanBattle* InTarget) override;
	void Shoot(ICanBattle* InTarget);

	Goblin() = default;
	Goblin(const char* InName, float InHealth, float InAttackPower)
		:Monster(InName, InHealth, InAttackPower)
	{

	}
	virtual ~Goblin() {}
};