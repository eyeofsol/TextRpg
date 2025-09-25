#include "Actor.h"
#include "Player.h"

void Actor::ApplyDamage(ICanBattle* InTarget)
{
	// AttackPower * �Ӽ� * ���� ȿ��.....
	Attack();
	float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	float Damage = AttackPower * RandomFactor;

	// �÷��̾� ��ų �˻�
	Player* GuardPlayer = dynamic_cast<Player*>(InTarget);
	if (GuardPlayer && GuardPlayer->CheckGuard())
		Damage /= 2.0f;
	Player* AttackPlayer = dynamic_cast<Player*>(this);
	if (AttackPlayer && AttackPlayer->CheckBerserker())
		Damage *= 2.0f;

	InTarget->TakeDamage(Damage);	// Damage��ŭ ������ �ֱ�
}

void Actor::TakeDamage(float InDamage)
{
	//float RandomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
	//float Health = GetHealth();
	//Health -= InDamage * RandomFactor;
	float Critical = rand() % 10;
	if (Critical < 1)
	{
		printf("ũ��Ƽ��!\n");
		InDamage *= 2;
	}

	SetHealth(Health - InDamage);
	printf("%s : %.1f�� ���ظ� �Ծ����ϴ�.\n", Name.c_str(), InDamage);
	printf("(%.1f/%.1f)\n", Health, MaxHealth);
	if (!IsAlive())
	{
		// ��� ó��
		printf("%s�� �׾����ϴ�.\n", Name.c_str());
	}
}

void Actor::PrintStatus()
{
	printf("���� ���\n");
}
