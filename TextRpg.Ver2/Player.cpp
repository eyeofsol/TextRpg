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
	printf("체력 + 10 | 공격력 + 2.5 | 마나 + 5\n\n");
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

void Player::AddItem(const ItemInfo& Item)
{
	if (Inventory.find(Item.Name) == Inventory.end())
		Inventory[Item.Name] = { Item, 1 };
	else
		Inventory[Item.Name].second++;
}

void Player::OpenInventory(bool* Select)
{
	if (Inventory.empty())
	{
		printf("인벤토리가 비어있습니다.\n");
		return;
	}

	std::cout << "\n--------인벤토리--------\n";
	std::vector<std::string> keys;
	int Index = 0;
	for (auto& iter : Inventory)
	{
		Index++;
		printf("%d. %s (%d개)\n", Index, iter.second.first.Name.c_str(), iter.second.second);
		keys.push_back(iter.first);
	}
	std::cout << "사용할 아이템을 선택하세요(0을 입력시 취소됩니다): ";

	int Input;
	std::cin >> Input;
	if (Input == 0)
		return;
	if (Input < -1 || Input > Index) {
		std::cout << "잘못된 입력입니다.\n";
		return;
	}

	std::string selected = keys[Input - 1];
	UseItem(Inventory[selected].first, Select);
	if (*Select == true)
	{
		Inventory[selected].second--;
		if (Inventory[selected].second <= 0)
			Inventory.erase(selected);
	}
}

void Player::UseItem(const ItemInfo& Item, bool* Select)
{
	if (Item.HPAmount > 0)
	{
		if (Health < MaxHealth)
		{
			Health += Item.HPAmount;
			if (Health > MaxHealth) Health = MaxHealth;
			printf("%s를 사용합니다. 체력이 %.2f 회복되었습니다.\n", Item.Name.c_str(), Item.HPAmount);
			*Select = true;
		}
		else
			printf("체력이 이미 최대치입니다.\n");
	}

	if (Item.MPAmount > 0)
	{
		if (Mana < MaxMana)
		{
			Mana += Item.MPAmount;
			if (Mana > MaxMana) Mana = MaxMana;
			printf("%s를 사용합니다. 마나가 %d 회복되었습니다.\n", Item.Name.c_str(), Item.MPAmount);
			*Select = true;
		}
		else
			printf("마나가 이미 최대치입니다.\n");
	}
}

void Player::UsePassive(const ItemInfo& Item)
{
	if (Item.AttackAmount > 0)
	{
		AddAttackPower(Item.AttackAmount);
		printf("%s를 사용합니다. 공격력이 영구적으로 %.2f 증가하었습니다.\n", Item.Name.c_str(), Item.AttackAmount);
	}

	if (Item.MaxHPAmount > 0)
	{
		MaxHealth += Item.MaxHPAmount;
		Health += Item.MaxHPAmount;
		printf("%s를 사용합니다. 체력이 영구적으로 %.2f 증가하었습니다.\n", Item.Name.c_str(), Item.MaxHPAmount);
	}

	if (Item.MaxMPAmount > 0)
	{
		MaxMana += Item.MaxMPAmount;
		Mana += Item.MaxMPAmount;
		printf("%s를 사용합니다. 마나가 영구적으로 %d 증가하었습니다.\n", Item.Name.c_str(), Item.MaxMPAmount);
	}
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

