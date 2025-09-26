#include "Actor.h"
#include "Player.h"

void Actor::ApplyDamage(ICanBattle* InTarget)
{
	Attack();
	float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);	// 난수 생성
	float Damage = AttackPower * RandomFactor;	// 기본 공격력에 난수를 곱해 데미지 초기화

	// 플레이어 스킬 검사
	Player* GuardPlayer = dynamic_cast<Player*>(InTarget);
	if (GuardPlayer && GuardPlayer->CheckGuard())
		Damage /= 2.0f;
	Player* AttackPlayer = dynamic_cast<Player*>(this);
	if (AttackPlayer && AttackPlayer->CheckBerserk())
		Damage *= 2.0f;

	InTarget->TakeDamage(Damage);	// Damage만큼 데미지 주기
}

void Actor::TakeDamage(float InDamage)
{
	//float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	//float Health = GetHealth();
	//Health -= InDamage * RandomFactor;
	float Critical = rand() % 10;	// 크리티컬 확률 설정
	if (Critical < 1)	// 10%
	{
		printf("크리티컬!\n");
		InDamage *= 2;	// 데미지 2배
	}

	SetHealth(Health - InDamage);
	printf("%s : %.1f의 피해를 입었습니다.\n", Name.c_str(), InDamage);
	printf("(%.1f/%.1f)\n", Health, MaxHealth);
	if (!IsAlive())
	{
		// 사망 처리
		printf("%s가 죽었습니다.\n", Name.c_str());
	}
}

void Actor::PrintStatus()
{
	printf("정보 출력\n");
}
