#pragma once
#include"Monster.h"

class Orc : public Monster
{
public:
	virtual void Attack() override;
	virtual void Skill(ICanBattle* InTarget) override;
	void Hawling();

	Orc() = default;
	Orc(const char* InName, float InHealth, float InAttackPower)
		:Monster(InName,InHealth,InAttackPower)
	{

	}
	virtual ~Orc() {}
};

