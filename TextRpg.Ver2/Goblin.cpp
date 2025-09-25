#include "Goblin.h"

void Goblin::Attack()
{
	printf("\n[%s]이 활을 쏩니다.\n", Name.c_str());
}

void Goblin::Skill(ICanBattle* InTarget)
{
	printf("\n[%s]이 스킬을 발동합니다.\n", Name.c_str());
	Goblin::Shoot(InTarget);
}

void Goblin::Shoot(ICanBattle* InTarget)
{
	printf("[%s]가 활을 두발 쏩니다.\n", Name.c_str());
	Actor::ApplyDamage(InTarget);
	Actor::ApplyDamage(InTarget);
}
