#include "Monster.h"

void Monster::Attack()
{
	printf("[%s]�� ����̸� �ֵθ��ϴ�.\n", Name.c_str());
}

void Monster::PrintStatus()
{
	printf("ü�� : %.2f/%.2f | ���ݷ� : %.2f\n", Health, MaxHealth, AttackPower);
}
