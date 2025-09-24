#pragma once
#include"Monster.h"

class Zombie : public Monster
{
public:
	virtual void Attack() override;
	virtual void Skill(ICanBattle* InTarget) override;
	void Recover();

	Zombie() = default;
	Zombie(const char* InName, float InHealth, float InAttackPower)
		:Monster(InName, InHealth, InAttackPower)
	{

	}
	virtual ~Zombie() {}
};

