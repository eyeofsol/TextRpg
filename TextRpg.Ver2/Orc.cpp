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

void Orc::Hawling()	// ��ũ ���� ��ų : ��ȿ(���ݷ� ����)
{
	printf("[%s]�� ���¢���ϴ�. ���ݷ��� 1.2�� �ö󰩴ϴ�.\n", Name.c_str());
	SetAttackPower(AttackPower * 1.2f);
}
