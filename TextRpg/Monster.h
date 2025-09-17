#pragma once
#include <string>
#include "Position.h"
#include "Actor.h"

// 실습 과제

// 2. 미로 탈출 게임 수정하기
// - 적을 클래스화하기(Monster로 대체)
// - 플레이어 클래스 만들고 적용하기
// - 적과 플레이어의 부모인 Actor 클래스 만들기

class Monster : public Actor
{
public:
	Monster() : Actor("몬스터", 30.0f, 5.0f) { }
	Monster(const char* InName) : Actor(InName, 30.0f, 5.0f) { }
	Monster(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}
	virtual void Attack() override;
	virtual void Skill(ICanBattle* InTarget) {};

	inline int GetDropGold() const { return DropGold; }
	inline Position& GetPosition() { return CurrentPosition; }

	virtual ~Monster() {}
protected:
	Position CurrentPosition = Position(0, 0);
	int DropGold = 10;
};

