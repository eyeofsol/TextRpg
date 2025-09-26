#pragma once
#include <string>
#include "ICanBattle.h"

class Actor : public ICanBattle
{
public:
	Actor() = default;
	Actor(const char* InName, float InHealth, float InAttackPower)
		: Name(InName), Health(InHealth), MaxHealth(InHealth), AttackPower(InAttackPower)
	{

	}

	/// <summary>
	/// Target���� �����ϴ� �Լ�
	/// </summary>
	/// <param name="InTarget">���� �޴� ���</param>
	virtual void ApplyDamage(ICanBattle* InTarget) override;
	/// <summary>
	/// ������ ���ط���ŭ ���ο��� ���ظ� ����
	/// </summary>
	/// <param name="InDamage">������ ���ض�</param>
	virtual void TakeDamage(float InDamage) override;

	virtual void PrintStatus();
	/// <summary>
	/// �� Actor�� ���� ���θ� �˷��ִ� �Լ�
	/// </summary>
	/// <returns>true�� ����, false�� ���</returns>
	inline bool IsAlive() { return Health > 0; }

	inline std::string GetName() { return Name; }
	inline float& GetHealth() { return Health; }
	inline float& GetAttackPower() { return AttackPower; }
	inline float& GetMaxHealth() { return MaxHealth; }

	virtual ~Actor() {}
protected:
	inline void SetHealth(float InHealth)
	{
		if (InHealth > MaxHealth)
		{
			Health = MaxHealth;
		}
		else
		{
			Health = InHealth;
		}
	}
	inline void SetAttackPower(float InAttackPower)
	{
		AttackPower = InAttackPower;
	}
	std::string Name = "����";
	float Health = 100.0f;	// ü��
	float MaxHealth = 100.0f;	// �ִ� ü��
	float AttackPower = 10.0f;	// �⺻ ���ݷ�
};

