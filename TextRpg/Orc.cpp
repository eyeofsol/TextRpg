#include "Orc.h"

void Orc::Attack()
{
	printf("[%s]가 방망이를 내려칩니다.\n", Name.c_str());
}

void Orc::Skill(ICanBattle* InTarget)
{
	printf("[%s]이 스킬을 발동합니다.\n", Name.c_str());
	Hawling();
}

void Orc::Hawling()
{
	printf("[%s]가 울부짖습니다. 공격력이 1.1배 올라갑니다.\n",Name.c_str());
	SetAttackPower(AttackPower * 1.1f);
}
