#include "Zombie.h"

void Zombie::Attack()
{
	printf("\n[%s]�� �޷���ϴ�.\n", Name.c_str());
}

void Zombie::Skill(ICanBattle* InTarget)
{
	printf("\n[%s]�� ��ų�� �ߵ��մϴ�.\n", Name.c_str());
	Recover();
}

void Zombie::Recover()	// ���� ���� ��ų : ȸ��
{
	printf("[%s]�� ü�� 10�� ȸ���մϴ�.\n", Name.c_str());
	SetHealth(Health + 10);
}
