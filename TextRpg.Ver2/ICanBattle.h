#pragma once

class ICanBattle	// 배틀 인터페이스
{
public:
	virtual ~ICanBattle() {}

	virtual void ApplyDamage(ICanBattle* InTarget) = 0;
	virtual void TakeDamage(float InDamage) = 0;
	virtual void Attack() = 0;

};