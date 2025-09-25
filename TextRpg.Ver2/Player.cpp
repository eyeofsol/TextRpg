#include "Player.h"
#include <iostream>

void Player::Attack()
{
	printf("[%s]�� ���� �ֵθ��ϴ�.\n", Name.c_str());
}

void Player::PrintStatus()
{
	printf("ü�� : %.2f/%.2f | ���� : %d/%d | ���ݷ� : %.2f\n", Health, MaxHealth, Mana, MaxMana, AttackPower);
	printf("���� : %d | ���� ��� : %d | ����ġ : %d/%d\n", Level, Gold, Exp, MaxExp);
}

void Player::AddGold(int InGold)
{
	printf("%d ��带 ȹ���Ͽ����ϴ�.\n", InGold);
	Gold += InGold;
}

void Player::AddExp(int InExp)
{
	printf("%d�� ����ġ�� ������ϴ�.\n", InExp);
	Exp += InExp;
	if (Exp >= MaxExp)
	{
		Levelup();
	}
}

void Player::Levelup()
{
	printf("\n������ �ö����ϴ�. ü�°� ������ ���� ȸ���մϴ�.\n");
	Level++;
	Exp -= MaxExp;
	MaxExp += 10;
	printf("ü�� + 10 | ���ݷ� + 1 | ���� + 5\n\n");
	MaxHealth += 10.0f;
	Health = MaxHealth;
	MaxMana += 5;
	Mana = MaxMana;
	AttackPower += 1.0f;

	for (auto& skill : AllSkills)
	{
		if (!skill.Learned && Level >= skill.RequiredLevel)
		{
			skill.Learned = true;
			printf("%s ��ų�� ȹ���Ͽ����ϴ�!\n", skill.Name.c_str());
		}
	}
}

void Player::PrintSkill()
{
	printf("��ų ���\n");
	for (const auto& skill : AllSkills)
	{
		if (skill.Learned)
			printf("%d. %s : %s\n",
				skill.SkillNum, skill.Name.c_str(), skill.Detail.c_str());
	}
}

void Player::DoubleAttack(ICanBattle* InTarget)
{
	printf("�� �� �����մϴ�.\n");
	ApplyDamage(InTarget);
	ApplyDamage(InTarget);
	Mana -= AllSkills[0].ManaCost;
}

void Player::SetGuard(int InTurn)
{
	printf("���и� �÷� 3�� ���� ���ظ� ���ݸ� �޽��ϴ�.\n");
	IsGuard = true;
	GuardTurn = InTurn;
	Mana -= AllSkills[1].ManaCost;
}

void Player::UpdateGuard()
{
	if (IsGuard) {
		GuardTurn--;
		if (GuardTurn <= 0) {
			IsGuard = false;
			printf("���� ���°� �����Ǿ����ϴ�.\n");
		}
	}
}

void Player::SetBerserk(int InTurn)
{
	printf("����ȭ ���¿� �����Ͽ� 5�� ���� ���ݷ��� 2��� �����˴ϴ�.\n");
	IsBerserk = true;
	BerserkTurn = InTurn;
	Mana -= AllSkills[2].ManaCost;
}

void Player::UpdateBerserk()
{
	if (IsBerserk) {
		BerserkTurn--;
		if (BerserkTurn <= 0) {
			IsBerserk = false;
			printf("����ȭ ���°� �����Ǿ����ϴ�.\n");
		}
	}
}

void Player::ResetStatus()
{
	IsGuard = false;
	GuardTurn = 0;
	IsBerserk = false;
	BerserkTurn = 0;
}

void Player::UseSkill(ICanBattle* InTarget, bool* Select)
{
	PrintSkill();
	int Input = -1;
	printf("����� ��ų�� �����ϼ���. 0�� �Է� �� ��ҵ˴ϴ�. : ");
	std::cin >> Input;
	printf("\n");
	switch (Input)
	{
	case(1):
		if (AllSkills[0].Learned)
		{
			if (Mana >= AllSkills[0].ManaCost)
			{
				DoubleAttack(InTarget);
				*Select = true;
			}
			else
				printf("������ �����մϴ�.\n");
		}
		else
			printf("����� ���� ��ų�Դϴ�.\n");
		break;
	case(2):
		if (AllSkills[1].Learned)
		{
			if (Mana >= AllSkills[1].ManaCost)
			{
				SetGuard(3);
				*Select = true;
			}
			else
				printf("������ �����մϴ�.\n");
		}
		else
			printf("����� ���� ��ų�Դϴ�.\n");
		break;
	case(3):
		if (AllSkills[2].Learned)
		{
			if (Mana >= AllSkills[2].ManaCost)
			{
				SetBerserk(5);
				*Select = true;
			}
			else
				printf("������ �����մϴ�.\n");
		}
		else
			printf("����� ���� ��ų�Դϴ�.\n");
		break;
	default:
		printf("��ų ����� ����մϴ�.\n"); break;
	}
}

