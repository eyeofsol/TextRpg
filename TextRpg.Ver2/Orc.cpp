#include "Orc.h"

void Orc::Attack()
{
	printf("\n[%s]가 방망이를 내려칩니다.\n", Name.c_str());
}

void Orc::Skill(ICanBattle* InTarget)
{
	printf("\n[%s]이 스킬을 발동합니다.\n", Name.c_str());
	Hawling();
}

void Orc::Hawling()	// 오크 고유 스킬 : 포효(공격력 증가)
{
	printf("[%s]가 울부짖습니다. 공격력이 1.2배 올라갑니다.\n", Name.c_str());
	SetAttackPower(AttackPower * 1.2f);
}
