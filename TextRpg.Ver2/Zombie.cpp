#include "Zombie.h"

void Zombie::Attack()
{
	printf("[%s]�� �޷���ϴ�.\n", Name.c_str());
}

void Zombie::Skill(ICanBattle* InTarget)
{
	printf("[%s]�� ��ų�� �ߵ��մϴ�.\n", Name.c_str());
	Zombie::Recover();
}

void Zombie::Recover()
{
	printf("[%s]�� ü�� 10�� ȸ���մϴ�.\n", Name.c_str());
	SetHealth(Health + 10);
}
