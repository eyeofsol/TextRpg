#include "Actor.h"

void Actor::ApplyDamage(ICanBattle* InTarget)
{
	// AttackPower * �Ӽ� * ���� ȿ��.....
	Attack();
	float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	AttackPower *= RandomFactor;
	InTarget->TakeDamage(AttackPower);	// AttackPower��ŭ ������ �ֱ�
}

void Actor::TakeDamage(float InDamage)
{
	//float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	//float Health = GetHealth();
	//Health -= InDamage * RandomFactor;
	SetHealth(Health-InDamage);
	printf("%s : %.1f�� ���ظ� �Ծ����ϴ�.\n", Name.c_str(), InDamage);
	printf("(%.1f/%.1f)\n", Health, MaxHealth);
	if (!IsAlive())
	{
		// ��� ó��
		printf("%s�� �׾����ϴ�.\n", Name.c_str());
	}
}