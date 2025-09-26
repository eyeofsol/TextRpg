#pragma once

class ICanBattle	// ��Ʋ �������̽�
{
public:
	virtual ~ICanBattle() {}

	virtual void ApplyDamage(ICanBattle* InTarget) = 0;
	virtual void TakeDamage(float InDamage) = 0;
	virtual void Attack() = 0;

};