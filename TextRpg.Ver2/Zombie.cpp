#include "Zombie.h"

void Zombie::Attack()
{
	printf("\n[%s]가 달려듭니다.\n", Name.c_str());
}

void Zombie::Skill(ICanBattle* InTarget)
{
	printf("\n[%s]이 스킬을 발동합니다.\n", Name.c_str());
	Recover();
}

void Zombie::Recover()	// 좀비 고유 스킬 : 회복
{
	printf("[%s]가 체력 10을 회복합니다.\n", Name.c_str());
	SetHealth(Health + 10);
}
