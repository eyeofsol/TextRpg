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
	/// Target에게 공격하는 함수
	/// </summary>
	/// <param name="InTarget">공격 받는 대상</param>
	virtual void ApplyDamage(ICanBattle* InTarget) override;
	/// <summary>
	/// 지정된 피해량만큼 본인에게 피해를 적용
	/// </summary>
	/// <param name="InDamage">적용할 피해랑</param>
	virtual void TakeDamage(float InDamage) override;

	virtual void PrintStatus();
	/// <summary>
	/// 이 Actor의 생존 여부를 알려주는 함수
	/// </summary>
	/// <returns>true면 생존, false면 사망</returns>
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
	std::string Name = "액터";
	float Health = 100.0f;	// 체력
	float MaxHealth = 100.0f;	// 최대 체력
	float AttackPower = 10.0f;	// 기본 공격력
};

