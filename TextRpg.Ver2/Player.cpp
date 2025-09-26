#include "Player.h"
#include <iostream>

void Player::Attack()	// 플레이어 공격 함수
{
	printf("[%s]가 검을 휘두릅니다.\n", Name.c_str());
}

void Player::PrintStatus()	// 플레이어 정보 출력
{
	printf("체력 : %.2f/%.2f | 마나 : %d/%d | 공격력 : %.2f\n", Health, MaxHealth, Mana, MaxMana, AttackPower);
	printf("레벨 : %d | 소지 골드 : %d | 경험치 : %d/%d\n", Level, Gold, Exp, MaxExp);
}

void Player::AddGold(int InGold)	// 골드 획득
{
	printf("%d 골드를 획득하였습니다.\n", InGold);
	Gold += InGold;
}

void Player::AddExp(int InExp)	// 경험치 획득
{
	printf("%d의 경험치를 얻었습니다.\n", InExp);
	Exp += InExp;
	if (Exp >= MaxExp)	// 경험치가 최대 경험치를 넘었을 때
	{
		Levelup();
	}
}

void Player::Levelup()	// 레벨업
{
	printf("\n레벨이 올랐습니다. 체력과 마나를 전부 회복합니다.\n");
	Level++;
	Exp -= MaxExp;	// 경험치를 최대 경험치만큼 감소
	MaxExp += 10;
	printf("체력 + 10 | 공격력 + 2.5 | 마나 + 5\n\n");	// 능력치 증가
	MaxHealth += 10.0f;
	Health = MaxHealth;
	MaxMana += 5;
	Mana = MaxMana;
	AttackPower += 1.0f;

	for (auto& skill : AllSkills)
	{
		if (!skill.Learned && Level >= skill.RequiredLevel)	// 스킬을 배울수 있는 레벨에 도달 시 스킬 획득
		{
			skill.Learned = true;
			printf("%s 스킬을 획득하였습니다!\n", skill.Name.c_str());
		}
	}
}

void Player::PrintSkill()	// 사용 가능 스킬 출력
{
	printf("스킬 목록\n");
	for (const auto& skill : AllSkills)
	{
		if (skill.Learned)
			printf("%d. %s : %s\n",
				skill.SkillNum, skill.Name.c_str(), skill.Detail.c_str());
	}
}

void Player::DoubleAttack(ICanBattle* InTarget)	// 연속 베기
{
	printf("두 번 공격합니다.\n");
	ApplyDamage(InTarget);
	ApplyDamage(InTarget);
	Mana -= AllSkills[0].ManaCost;
}

void Player::SetGuard(int InTurn)	// 방패 올리기
{
	printf("방패를 올려 3턴 동안 피해를 절반만 받습니다.\n");
	IsGuard = true;
	GuardTurn = InTurn;
	Mana -= AllSkills[1].ManaCost;
}

void Player::UpdateGuard()	// 가드 턴 계산
{
	if (IsGuard) {
		GuardTurn--;
		if (GuardTurn <= 0) {
			IsGuard = false;
			printf("가드 상태가 해제되었습니다.\n");
		}
	}
}

void Player::SetBerserk(int InTurn)	// 광폭화
{
	printf("광폭화 상태에 돌입하여 5턴 동안 공격력이 2배로 증가됩니다.\n");
	IsBerserk = true;
	BerserkTurn = InTurn;
	Mana -= AllSkills[2].ManaCost;
}

void Player::UpdateBerserk()	// 광폭화 턴 계산
{
	if (IsBerserk) {
		BerserkTurn--;
		if (BerserkTurn <= 0) {
			IsBerserk = false;
			printf("광폭화 상태가 해제되었습니다.\n");
		}
	}
}

void Player::ResetStatus()	// 배틀 종료 시 버프 초기화
{
	IsGuard = false;
	GuardTurn = 0;
	IsBerserk = false;
	BerserkTurn = 0;
}

void Player::AddItem(const ItemInfo& Item)	// 소모 아이템 인벤토리에 추가
{
	if (Inventory.find(Item.Name) == Inventory.end())	// 해당 아이템이 인벤토리에 없을 시 새 항목 추가
		Inventory[Item.Name] = { Item, 1 };
	else	// 인벤토리에 존재 시 수량 증가
		Inventory[Item.Name].second++;
}

void Player::OpenInventory(bool* Select)	// 인벤토리 열기
{
	if (Inventory.empty())	// 인벤토리가 비어 잇을 때
	{
		printf("인벤토리가 비어있습니다.\n");
		return;
	}

	std::cout << "\n--------인벤토리--------\n";
	std::vector<std::string> keys;	// 사용 가능 아이템 벡터
	int Index = 0;
	for (auto& iter : Inventory)
	{
		Index++;
		printf("%d. %s (%d개)\n", Index, iter.second.first.Name.c_str(), iter.second.second);	// 보유 아이템의 이름과 개수 출력
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

	std::string selected = keys[Input - 1];	// 사용할 아이템 선택
	UseItem(Inventory[selected].first, Select);	// 아이템 사용
	if (*Select == true)	// 아이템이 정상적으로 사용 시
	{
		Inventory[selected].second--;	// 아이템 개수 감소
		if (Inventory[selected].second <= 0)	// 아이템 모두 소모 시
			Inventory.erase(selected);	// 인벤토리 맵에서 삭제
	}
}

void Player::UseItem(const ItemInfo& Item, bool* Select)	// 소모 아이템 사용
{
	if (Item.HPAmount > 0)	// HP 관련 아이템일 시
	{
		if (Health < MaxHealth)	// 체력이 최대치보다 낮다면
		{
			Health += Item.HPAmount;
			if (Health > MaxHealth) Health = MaxHealth;
			printf("%s를 사용합니다. 체력이 %.2f 회복되었습니다.\n", Item.Name.c_str(), Item.HPAmount);
			*Select = true;
		}
		else
			printf("체력이 이미 최대치입니다.\n");
	}

	if (Item.MPAmount > 0)	// MP 관련 아이템일 시
	{
		if (Mana < MaxMana)	// 마나가 최대치보다 낮다면
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

void Player::UsePassive(const ItemInfo& Item)	// 패시브 아이템 사용
{
	if (Item.AttackAmount > 0)	// 공격력 관련 아이템일 시
	{
		AddAttackPower(Item.AttackAmount);
		printf("%s를 사용합니다. 공격력이 영구적으로 %.2f 증가하었습니다.\n", Item.Name.c_str(), Item.AttackAmount);
	}

	if (Item.MaxHPAmount > 0)	// 최대 체력 관련 아이템일 시
	{
		MaxHealth += Item.MaxHPAmount;
		Health += Item.MaxHPAmount;
		printf("%s를 사용합니다. 체력이 영구적으로 %.2f 증가하었습니다.\n", Item.Name.c_str(), Item.MaxHPAmount);
	}

	if (Item.MaxMPAmount > 0)	// 최대 마나 관련 아이템일 시
	{
		MaxMana += Item.MaxMPAmount;
		Mana += Item.MaxMPAmount;
		printf("%s를 사용합니다. 마나가 영구적으로 %d 증가하었습니다.\n", Item.Name.c_str(), Item.MaxMPAmount);
	}
}

void Player::UseSkill(ICanBattle* InTarget, bool* Select)	// 스킬 사용
{
	PrintSkill();	// 보유 스킬 출력
	int Input = -1;
	printf("사용할 스킬을 선택하세요. 0을 입력 시 취소됩니다. : ");
	std::cin >> Input;
	printf("\n");
	switch (Input)
	{
	case(1):
		if (AllSkills[0].Learned)	// 해당 스킬을 배웠고
		{
			if (Mana >= AllSkills[0].ManaCost)	// 스킬에 필요한 마나가 있을 시
			{
				DoubleAttack(InTarget);	// 스킬 발동
				*Select = true;
			}
			else
				printf("마나가 부족합니다.\n");
		}
		else
			printf("배우지 않은 스킬입니다.\n");
		break;
	case(2):
		if (AllSkills[1].Learned)	// 해당 스킬을 배웠고
		{
			if (Mana >= AllSkills[1].ManaCost)	// 스킬에 필요한 마나가 있을 시
			{
				SetGuard(3);	// 스킬 발동
				*Select = true;
			}
			else
				printf("마나가 부족합니다.\n");
		}
		else
			printf("배우지 않은 스킬입니다.\n");
		break;
	case(3):
		if (AllSkills[2].Learned)	// 해당 스킬을 배웠고
		{
			if (Mana >= AllSkills[2].ManaCost)	// 스킬에 필요한 마나가 있을 시
			{
				SetBerserk(5);	// 스킬 발동
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

