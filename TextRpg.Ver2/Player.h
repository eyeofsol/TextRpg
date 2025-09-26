#pragma once
#include "Position.h"
#include "Actor.h"
#include "ItemInfo.h"
#include <vector>
#include <map>

struct SkillInfo	// 스킬 구조체
{
	std::string Name;	// 이름
	std::string Detail;	// 설명
	int SkillNum;		// 스킬 번호
	int RequiredLevel;	// 스킬을 배우기 위해 필요한 레벨
	int ManaCost;		// 소모 마나
	bool Learned = false;	// 스킬을 배웠는지 여부
};

class Player : public Actor
{
public:
	Player() = default;
	Player(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
		// 모든 스킬 정의
		AllSkills = {
			{"연속 베기","15의 마나를 소모하여 두 번 공격합니다.\n", 1, 3, 15, false},
			{"방패 올리기","10의 마나를 소모하여 3턴 동안 받는 피해를 절반으로 감소시킵니다.\n", 2, 5, 10, false},
			{"광폭화","30의 마나를 소모하여 5턴동안 공격력을 2배로 증가시킵니다.\n", 3, 7, 30, false}
		};
	}
	virtual void Attack() override;
	virtual void PrintStatus() override;

	// 전투 종료 함수
	void AddGold(int InGold);	// 골드 획득
	void AddExp(int InExp);		// 경험치 획득
	void Levelup();				// 레벨 업

	// 스킬 함수
	void UseSkill(ICanBattle* InTarget, bool* Select);	// 스킬 사용
	void PrintSkill();	// 사용 가능한 스킬 목록 출력
	void DoubleAttack(ICanBattle* InTarget);	// 연속 베기 스킬
	void SetGuard(int InTurn);	// 방패 올리기 스킬
	void UpdateGuard();	// 가드 턴 계산
	void SetBerserk(int InTure);	// 광폭화 스킬
	void UpdateBerserk();	// 광폭화 턴 계산
	void ResetStatus();	// 배틀 종료 후 초기화 함수
	
	// 인벤토리 함수
	void AddItem(const ItemInfo& Item);	// 인벤토리에 아이템 추가
	void OpenInventory(bool* Select);	// 인벤토리 열기
	void UseItem(const ItemInfo& Item,bool* Select);	// 인벤토리의 아이템 사용
	void UsePassive(const ItemInfo& Item);	// 패시브 아이템 획득시 바로 사용

	// 체크 및 Get,Set함수
	inline bool CheckGuard() const { return IsGuard; }
	inline bool CheckBerserker() const { return IsBerserk; }
	inline int& GetGold() { return Gold; }
	inline int& GetMana() { return Mana; }
	inline Position& GetPosition() { return CurrentPosition; }
	inline void AddAttackPower(float InAttackPower)
	{
		AttackPower += InAttackPower;
	}
	inline void SetMana(int InMana)
	{
		Mana += InMana;
		if (Mana > MaxMana)
		{
			Mana = MaxMana;
		}
	}

	virtual ~Player() {}
protected:

	Position CurrentPosition = Position(0, 0);	// 플레이어 좌표
	int Gold = 50;	// 소지 골드
	int Level = 1;	// 레벨
	int Exp = 0;	// 경험치
	int MaxExp = 30;	// 최대 경험치
	int MaxMana = 50;	// 최대 마나
	int Mana = MaxMana;	// 마나

	std::vector<SkillInfo> AllSkills;	// 스킬 벡터
	bool IsGuard = false;	// 가드 여부
	bool IsBerserk = false;	// 광폭화 여부
	int GuardTurn = 0;	// 가드 유지 턴
	int BerserkTurn = 0;	// 광폭화 유지 턴

	std::map<std::string, std::pair<ItemInfo, int>> Inventory;	// 인벤토리 맵
};

