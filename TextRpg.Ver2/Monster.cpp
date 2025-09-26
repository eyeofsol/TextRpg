#include "Monster.h"

void Monster::Attack()	// 몬스터 공격
{
	printf("[%s]가 방망이를 휘두릅니다.\n", Name.c_str());
}

void Monster::PrintStatus()	// 몬스터 정보 출력
{
	printf("체력 : %.2f/%.2f | 공격력 : %.2f\n", Health, MaxHealth, AttackPower);
}
