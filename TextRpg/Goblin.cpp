#include "Goblin.h"

void Goblin::Attack()
{
	printf("[%s]�� Ȱ�� ���ϴ�.\n", Name.c_str());
}

void Goblin::Skill(ICanBattle* InTarget)
{
	printf("[%s]�� ��ų�� �ߵ��մϴ�.\n", Name.c_str());
	Goblin::Shoot(InTarget);
}

void Goblin::Shoot(ICanBattle* InTarget)
{
	printf("[%s]�� Ȱ�� �ι� ���ϴ�.\n",Name.c_str());
	Actor::ApplyDamage(InTarget);
	Actor::ApplyDamage(InTarget);
}
