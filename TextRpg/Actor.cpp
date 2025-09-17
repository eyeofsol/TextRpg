#include "Actor.h"

void Actor::ApplyDamage(ICanBattle* InTarget)
{
	// AttackPower * 속성 * 버프 효과.....
	Attack();
	float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	AttackPower *= RandomFactor;
	InTarget->TakeDamage(AttackPower);	// AttackPower만큼 데미지 주기
}

void Actor::TakeDamage(float InDamage)
{
	//float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	//float Health = GetHealth();
	//Health -= InDamage * RandomFactor;
	SetHealth(Health-InDamage);
	printf("%s : %.1f의 피해를 입었습니다.\n", Name.c_str(), InDamage);
	printf("(%.1f/%.1f)\n", Health, MaxHealth);
	if (!IsAlive())
	{
		// 사망 처리
		printf("%s가 죽었습니다.\n", Name.c_str());
	}
}