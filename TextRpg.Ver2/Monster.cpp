#include "Monster.h"

void Monster::Attack()
{
	printf("[%s]가 방망이를 휘두릅니다.\n", Name.c_str());
}

void Monster::PrintStatus()
{
	printf("체력 : %.2f/%.2f | 공격력 : %.2f\n", Health, MaxHealth, AttackPower);
}
