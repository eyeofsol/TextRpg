#include "Player.h"
#include <iostream>

void Player::Attack()
{
	printf("[%s]가 검을 휘두릅니다.\n", Name.c_str());
}

void Player::PrintStatus()
{
	printf("체력 : %.2f/%.2f | 마나 : %d/%d | 공격력 : %.2f\n", Health, MaxHealth, Mana, MaxMana, AttackPower);
	printf("레벨 : %d | 소지 골드 : %d | 경험치 : %d/%d\n", Level, Gold, Exp, MaxExp);
}

void Player::AddGold(int InGold)
{
	printf("%d 골드를 획득하였습니다.\n", InGold);
	Gold += InGold;
}

void Player::AddExp(int InExp)
{
	printf("%d의 경험치를 얻었습니다.\n", InExp);
	Exp += InExp;
	if (Exp >= MaxExp)
	{
		Levelup();
	}
}

void Player::Levelup()
{
	printf("\n레벨이 올랐습니다. 체력과 마나를 전부 회복합니다.\n");
	Level++;
	Exp -= MaxExp;
	MaxExp += 10;
	printf("체력 + 10 | 공격력 + 1 | 마나 + 5\n\n");
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
			printf("%s 스킬을 획득하였습니다!\n", skill.Name.c_str());
		}
	}
}

void Player::PrintSkill()
{
	printf("스킬 목록\n");
	for (const auto& skill : AllSkills)
	{
		if (skill.Learned)
			printf("%d. %s : %s\n",
				skill.SkillNum, skill.Name.c_str(), skill.Detail.c_str());
	}
}

void Player::DoubleAttack(ICanBattle* InTarget)
{
	printf("두 번 공격합니다.\n");
	ApplyDamage(InTarget);
	ApplyDamage(InTarget);
	Mana -= AllSkills[0].ManaCost;
}

void Player::SetGuard(int InTurn)
{
	printf("방패를 올려 3턴 동안 피해를 절반만 받습니다.\n");
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
			printf("가드 상태가 해제되었습니다.\n");
		}
	}
}

void Player::SetBerserk(int InTurn)
{
	printf("광폭화 상태에 돌입하여 5턴 동안 공격력이 2배로 증가됩니다.\n");
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
			printf("광폭화 상태가 해제되었습니다.\n");
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
	printf("사용할 스킬을 선택하세요. 0을 입력 시 취소됩니다. : ");
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
				printf("마나가 부족합니다.\n");
		}
		else
			printf("배우지 않은 스킬입니다.\n");
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
				printf("마나가 부족합니다.\n");
		}
		else
			printf("배우지 않은 스킬입니다.\n");
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
				printf("마나가 부족합니다.\n");
		}
		else
			printf("배우지 않은 스킬입니다.\n");
		break;
	default:
		printf("스킬 사용을 취소합니다.\n"); break;
	}
}

