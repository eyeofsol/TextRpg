#include "Orc.h"

void Orc::Attack()
{
	printf("\n[%s]�� ����̸� ����Ĩ�ϴ�.\n", Name.c_str());
}

void Orc::Skill(ICanBattle* InTarget)
{
	printf("\n[%s]�� ��ų�� �ߵ��մϴ�.\n", Name.c_str());
	Hawling();
}

void Orc::Hawling()
{
	printf("[%s]�� ���¢���ϴ�. ���ݷ��� 1.1�� �ö󰩴ϴ�.\n", Name.c_str());
	SetAttackPower(AttackPower * 1.1f);
}
