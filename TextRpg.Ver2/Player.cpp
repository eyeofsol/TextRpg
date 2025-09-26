#include "Player.h"
#include <iostream>

void Player::Attack()	// �÷��̾� ���� �Լ�
{
	printf("[%s]�� ���� �ֵθ��ϴ�.\n", Name.c_str());
}

void Player::PrintStatus()	// �÷��̾� ���� ���
{
	printf("ü�� : %.2f/%.2f | ���� : %d/%d | ���ݷ� : %.2f\n", Health, MaxHealth, Mana, MaxMana, AttackPower);
	printf("���� : %d | ���� ��� : %d | ����ġ : %d/%d\n", Level, Gold, Exp, MaxExp);
}

void Player::AddGold(int InGold)	// ��� ȹ��
{
	printf("%d ��带 ȹ���Ͽ����ϴ�.\n", InGold);
	Gold += InGold;
}

void Player::AddExp(int InExp)	// ����ġ ȹ��
{
	printf("%d�� ����ġ�� ������ϴ�.\n", InExp);
	Exp += InExp;
	if (Exp >= MaxExp)	// ����ġ�� �ִ� ����ġ�� �Ѿ��� ��
	{
		Levelup();
	}
}

void Player::Levelup()	// ������
{
	printf("\n������ �ö����ϴ�. ü�°� ������ ���� ȸ���մϴ�.\n");
	Level++;
	Exp -= MaxExp;	// ����ġ�� �ִ� ����ġ��ŭ ����
	MaxExp += 10;
	printf("ü�� + 10 | ���ݷ� + 2.5 | ���� + 5\n\n");	// �ɷ�ġ ����
	MaxHealth += 10.0f;
	Health = MaxHealth;
	MaxMana += 5;
	Mana = MaxMana;
	AttackPower += 1.0f;

	for (auto& skill : AllSkills)
	{
		if (!skill.Learned && Level >= skill.RequiredLevel)	// ��ų�� ���� �ִ� ������ ���� �� ��ų ȹ��
		{
			skill.Learned = true;
			printf("%s ��ų�� ȹ���Ͽ����ϴ�!\n", skill.Name.c_str());
		}
	}
}

void Player::PrintSkill()	// ��� ���� ��ų ���
{
	printf("��ų ���\n");
	for (const auto& skill : AllSkills)
	{
		if (skill.Learned)
			printf("%d. %s : %s\n",
				skill.SkillNum, skill.Name.c_str(), skill.Detail.c_str());
	}
}

void Player::DoubleAttack(ICanBattle* InTarget)	// ���� ����
{
	printf("�� �� �����մϴ�.\n");
	ApplyDamage(InTarget);
	ApplyDamage(InTarget);
	Mana -= AllSkills[0].ManaCost;
}

void Player::SetGuard(int InTurn)	// ���� �ø���
{
	printf("���и� �÷� 3�� ���� ���ظ� ���ݸ� �޽��ϴ�.\n");
	IsGuard = true;
	GuardTurn = InTurn;
	Mana -= AllSkills[1].ManaCost;
}

void Player::UpdateGuard()	// ���� �� ���
{
	if (IsGuard) {
		GuardTurn--;
		if (GuardTurn <= 0) {
			IsGuard = false;
			printf("���� ���°� �����Ǿ����ϴ�.\n");
		}
	}
}

void Player::SetBerserk(int InTurn)	// ����ȭ
{
	printf("����ȭ ���¿� �����Ͽ� 5�� ���� ���ݷ��� 2��� �����˴ϴ�.\n");
	IsBerserk = true;
	BerserkTurn = InTurn;
	Mana -= AllSkills[2].ManaCost;
}

void Player::UpdateBerserk()	// ����ȭ �� ���
{
	if (IsBerserk) {
		BerserkTurn--;
		if (BerserkTurn <= 0) {
			IsBerserk = false;
			printf("����ȭ ���°� �����Ǿ����ϴ�.\n");
		}
	}
}

void Player::ResetStatus()	// ��Ʋ ���� �� ���� �ʱ�ȭ
{
	IsGuard = false;
	GuardTurn = 0;
	IsBerserk = false;
	BerserkTurn = 0;
}

void Player::AddItem(const ItemInfo& Item)	// �Ҹ� ������ �κ��丮�� �߰�
{
	if (Inventory.find(Item.Name) == Inventory.end())	// �ش� �������� �κ��丮�� ���� �� �� �׸� �߰�
		Inventory[Item.Name] = { Item, 1 };
	else	// �κ��丮�� ���� �� ���� ����
		Inventory[Item.Name].second++;
}

void Player::OpenInventory(bool* Select)	// �κ��丮 ����
{
	if (Inventory.empty())	// �κ��丮�� ��� ���� ��
	{
		printf("�κ��丮�� ����ֽ��ϴ�.\n");
		return;
	}

	std::cout << "\n--------�κ��丮--------\n";
	std::vector<std::string> keys;	// ��� ���� ������ ����
	int Index = 0;
	for (auto& iter : Inventory)
	{
		Index++;
		printf("%d. %s (%d��)\n", Index, iter.second.first.Name.c_str(), iter.second.second);	// ���� �������� �̸��� ���� ���
		keys.push_back(iter.first);
	}
	std::cout << "����� �������� �����ϼ���(0�� �Է½� ��ҵ˴ϴ�): ";

	int Input;
	std::cin >> Input;
	if (Input == 0)
		return;
	if (Input < -1 || Input > Index) {
		std::cout << "�߸��� �Է��Դϴ�.\n";
		return;
	}

	std::string selected = keys[Input - 1];	// ����� ������ ����
	UseItem(Inventory[selected].first, Select);	// ������ ���
	if (*Select == true)	// �������� ���������� ��� ��
	{
		Inventory[selected].second--;	// ������ ���� ����
		if (Inventory[selected].second <= 0)	// ������ ��� �Ҹ� ��
			Inventory.erase(selected);	// �κ��丮 �ʿ��� ����
	}
}

void Player::UseItem(const ItemInfo& Item, bool* Select)	// �Ҹ� ������ ���
{
	if (Item.HPAmount > 0)	// HP ���� �������� ��
	{
		if (Health < MaxHealth)	// ü���� �ִ�ġ���� ���ٸ�
		{
			Health += Item.HPAmount;
			if (Health > MaxHealth) Health = MaxHealth;
			printf("%s�� ����մϴ�. ü���� %.2f ȸ���Ǿ����ϴ�.\n", Item.Name.c_str(), Item.HPAmount);
			*Select = true;
		}
		else
			printf("ü���� �̹� �ִ�ġ�Դϴ�.\n");
	}

	if (Item.MPAmount > 0)	// MP ���� �������� ��
	{
		if (Mana < MaxMana)	// ������ �ִ�ġ���� ���ٸ�
		{
			Mana += Item.MPAmount;
			if (Mana > MaxMana) Mana = MaxMana;
			printf("%s�� ����մϴ�. ������ %d ȸ���Ǿ����ϴ�.\n", Item.Name.c_str(), Item.MPAmount);
			*Select = true;
		}
		else
			printf("������ �̹� �ִ�ġ�Դϴ�.\n");
	}
}

void Player::UsePassive(const ItemInfo& Item)	// �нú� ������ ���
{
	if (Item.AttackAmount > 0)	// ���ݷ� ���� �������� ��
	{
		AddAttackPower(Item.AttackAmount);
		printf("%s�� ����մϴ�. ���ݷ��� ���������� %.2f �����Ͼ����ϴ�.\n", Item.Name.c_str(), Item.AttackAmount);
	}

	if (Item.MaxHPAmount > 0)	// �ִ� ü�� ���� �������� ��
	{
		MaxHealth += Item.MaxHPAmount;
		Health += Item.MaxHPAmount;
		printf("%s�� ����մϴ�. ü���� ���������� %.2f �����Ͼ����ϴ�.\n", Item.Name.c_str(), Item.MaxHPAmount);
	}

	if (Item.MaxMPAmount > 0)	// �ִ� ���� ���� �������� ��
	{
		MaxMana += Item.MaxMPAmount;
		Mana += Item.MaxMPAmount;
		printf("%s�� ����մϴ�. ������ ���������� %d �����Ͼ����ϴ�.\n", Item.Name.c_str(), Item.MaxMPAmount);
	}
}

void Player::UseSkill(ICanBattle* InTarget, bool* Select)	// ��ų ���
{
	PrintSkill();	// ���� ��ų ���
	int Input = -1;
	printf("����� ��ų�� �����ϼ���. 0�� �Է� �� ��ҵ˴ϴ�. : ");
	std::cin >> Input;
	printf("\n");
	switch (Input)
	{
	case(1):
		if (AllSkills[0].Learned)	// �ش� ��ų�� �����
		{
			if (Mana >= AllSkills[0].ManaCost)	// ��ų�� �ʿ��� ������ ���� ��
			{
				DoubleAttack(InTarget);	// ��ų �ߵ�
				*Select = true;
			}
			else
				printf("������ �����մϴ�.\n");
		}
		else
			printf("����� ���� ��ų�Դϴ�.\n");
		break;
	case(2):
		if (AllSkills[1].Learned)	// �ش� ��ų�� �����
		{
			if (Mana >= AllSkills[1].ManaCost)	// ��ų�� �ʿ��� ������ ���� ��
			{
				SetGuard(3);	// ��ų �ߵ�
				*Select = true;
			}
			else
				printf("������ �����մϴ�.\n");
		}
		else
			printf("����� ���� ��ų�Դϴ�.\n");
		break;
	case(3):
		if (AllSkills[2].Learned)	// �ش� ��ų�� �����
		{
			if (Mana >= AllSkills[2].ManaCost)	// ��ų�� �ʿ��� ������ ���� ��
			{
				SetBerserk(5);	// ��ų �ߵ�
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

