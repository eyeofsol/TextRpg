#include "GameManager.h"
#include "Map.h"
#include "Orc.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Shop.h"
#include <iostream>

void GameManager::PlayGame()
{
	printf("~~ 광산 탐험 게임 ~~\n");
	Player player("플레이어", 100.0f, 20.0f);	// 플레이어 클래스 생성

	for (int i = 1; i <= MaxStage; i++)	// 최대 스테이지 개수까지 반복
	{
		Map.GenerateMap();	// 맵 생성
		Map.FindStartPosition(player.GetPosition());	// 플레이어 시작 좌표 초기화
		HasKey = false;	// 열쇠 보유 여부 초기화

		while (player.GetHealth() > 0)	// 플레이어가 죽기 전까지
		{
			printf("\n");
			Map.PrintMap(player.GetPosition());	// 맵 출력

			if (IsEnd(player.GetPosition()))	// 플레이어 출구 도달 여부
			{
				if (HasKey)	// 열쇠 보유중일 시
				{
					printf("\n");
					printf("%d층을 클리어하였습니다. 다음 층으로 내려갑니다...\n", i);
					printf("\n");
					Stage++;
					break;
				}
				else
				{
					printf("내려가는 문이 잠겨있습니다. 열쇠를 획득하고 오세요.\n");
				}
			}
			if (IsKey(player.GetPosition()))	// 플레이어 열쇠 위치 도달 여부
			{
				printf("열쇠를 획득하였습니다.\n");
				Map.PickupKey(player.GetPosition().x, player.GetPosition().y);	// 열쇠 획득 함수
				HasKey = true;
			}

			int MoveFlags = PrintAvailableMoves(player.GetPosition());	// 플레이어 이동 가능 방향 출력
			MoveDirection Direction = GetMoveInput(MoveFlags);	// 이동 가능 방향에 다른 방향 설정
			switch (Direction)
			{
			case MoveDirection::DirUp:
				player.GetPosition().y--;
				break;
			case MoveDirection::DirDown:
				player.GetPosition().y++;
				break;
			case MoveDirection::DirLeft:
				player.GetPosition().x--;
				break;
			case MoveDirection::DirRight:
				player.GetPosition().x++;
				break;
			case MoveDirection::DirNone:
			default:
				// 있을 수 없음
				break;
			}
			MoveEventProcess(player, Stage);	// 플레이어 이동 시 이벤트 처리
		}
	}
	if (player.GetHealth() > 0)
		printf("축하합니다! 게임을 클리어하셨습니다!\n");
	printf("정복한 스테이지 : %d | 최종 최대체력 : %.2f | 최종 공격력 : %.2f\n", Stage, player.GetMaxHealth(), player.GetAttackPower());
	printf("최종 마나 %d | 소지 골드 : %d\n", player.GetMana(), player.GetGold());
}

int GameManager::PrintAvailableMoves(Position& position)
{
	int MoveFlags = static_cast<int>(MoveDirection::DirNone);
	
	printf("이동할 수 있는 방향을 선택하세요 (w:위 a:왼쪽 s:아래쪽 d:오른쪽 g:체력 회복):\n");
	if (!IsWall(position.x, position.y - 1))	// 해당 방향이 벽인지 확인 검사
	{
		printf("W(↑) ");
		MoveFlags |= MoveDirection::DirUp;
	}
	if (!IsWall(position.x, position.y + 1))
	{
		printf("S(↓) ");
		MoveFlags |= MoveDirection::DirDown;
	}
	if (!IsWall(position.x - 1, position.y))
	{
		printf("A(←) ");
		MoveFlags |= MoveDirection::DirLeft;
	}
	if (!IsWall(position.x + 1, position.y))
	{
		printf("D(→) ");
		MoveFlags |= MoveDirection::DirRight;
	}
	printf("\n");

	return MoveFlags;
}

bool GameManager::IsWall(int X, int Y)	// 벽 검사 함수
{
	bool isWall = false;
	if (Y < 0 || Y >= Map.GetHeight() ||
		X < 0 || X >= Map.GetWidth() ||
		Map.GetMaze(Y, X) == MapTile::Wall)
		isWall = true;
	return isWall;
}

bool GameManager::IsEnd(Position& position)	// 출구 도달 여부 함수
{
	return Map.GetMaze(position.y, position.x) == MapTile::End;
}

bool GameManager::IsKey(Position& position)	// 열쇠 위치 도달 여부 함수
{
	return Map.GetMaze(position.y, position.x) == MapTile::Key;
}

MoveDirection GameManager::GetMoveInput(int MoveFlags)	// 이동 방향 입력 함수
{
	char InputChar = 0;
	MoveDirection Direction = MoveDirection::DirNone;

	while (true)
	{
		printf("방향을 입력하세요 : ");
		std::cin >> InputChar;

		if ((InputChar == 'w' || InputChar == 'W')
			&& (MoveFlags & MoveDirection::DirUp))
		{
			Direction = MoveDirection::DirUp;
			break;
		}
		if ((InputChar == 's' || InputChar == 'S')
			&& (MoveFlags & MoveDirection::DirDown))
		{
			Direction = MoveDirection::DirDown;
			break;
		}
		if ((InputChar == 'a' || InputChar == 'A')
			&& (MoveFlags & MoveDirection::DirLeft))
		{
			Direction = MoveDirection::DirLeft;
			break;
		}
		if ((InputChar == 'd' || InputChar == 'D')
			&& (MoveFlags & MoveDirection::DirRight))
		{
			Direction = MoveDirection::DirRight;
			break;
		}
		printf("잘못된 입력입니다. 이동할 수 있는 방향 중에서 선택하세요.\n");
	}
	return Direction;
}

void GameManager::MoveEventProcess(Player& Player, int InStage)	// 이동 이벤트 함수
{
	float RandomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f ~ 1.0f
	// printf("Random Value = %.2f\n", RandomValue);
	if (RandomValue < 0.2f)	// 20%
	{
		printf("\n적이 출현했습니다.\n");
		BattleEvent(Player, InStage);
	}
	else if (RandomValue < 0.3f)	// 10%
	{
		printf("떠돌이 상인을 만났습니다.\n");
		ShopEvent(Player);
	}
	else if (RandomValue < 0.35f)	// 5%
	{
		printf("\n보물 상자를 발견했습니다!\n");
		BoxEvent(Player);
	}
	else
	{
		printf("아무 일도 일어나지 않았습니다.\n");
	}
}

void GameManager::BattleEvent(Player& Player, int InStage)	// 배틀 이벤트 함수
{
	const int Size = 3;
	float AddStatus = static_cast<float>(InStage);	// 스테이지 단계에 따라 몬스터의 능력치 증가 수치
	Monster* Enemy[Size] = { 0 };	// 몬스터 객체 동적 배열 생성
	Enemy[0] = new Orc("오크", 50.0f + (5.0f * AddStatus), 10.0f + (2.0f * AddStatus));
	Enemy[1] = new Goblin("고블린", 30.0f + (5.0f * AddStatus), 15.0f + (2.0f * AddStatus));
	Enemy[2] = new Zombie("좀비", 80.0f + (5.0f * AddStatus), 5.0f + (2.0f * AddStatus));

	int RandomMonster = rand() % 3;	// 랜덤한 몬스터 등장
	int Run = 0;	// 플레이어 도망 여부

	printf("\n[%s]을 마주쳤습니다. 배틀을 시작합니다.\n", Enemy[RandomMonster]->GetName().c_str());
	while (true)
	{
		int Input = 0;
		bool IsGuard = false;	// 플레이어 가드 상태
		bool Select = false;	// 플레이어 행동 선택 여부
		printf("적 정보\n");
		Enemy[RandomMonster]->PrintStatus();	// 적 정보 출력
		while (!Select)	// 플레이어가 특정 행동을 취할 때까지 반복
		{
			printf("\n현재 상태\n");
			Player.PrintStatus();	// 플레이어 정보 출력
			printf("1. 공격 | 2. 스킬 | 3. 아이템 | 4. 도망\n");
			printf("행동을 선택하세요 : ");
			if (!(std::cin >> Input))	// 오입력 방지
			{
				std::cin.clear(); // failbit 초기화
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 잘못 입력된 부분 버림
				printf("잘못 입력하셨습니다. 숫자를 입력하세요.\n");
				continue; // 다시 입력 받음
			}
			printf("----------------------------------------\n");

			switch (Input)
			{
			case(1):
			{
				// 일반 공격
				printf("\n플레이어가 공격합니다.\n");
				Player.ApplyDamage(Enemy[RandomMonster]);
				printf("적의 남은 HP : %.1f\n", Enemy[RandomMonster]->GetHealth());
				Select = true;
				break;
			}
			case(2):
			{
				// 스킬 사용
				Player.UseSkill(Enemy[RandomMonster], &Select);
				break;
			}
			case(3):
			{
				// 아이템 사용
				Player.OpenInventory(&Select);
				break;
			}
			case(4):
			{
				// 도망치기
				printf("적의 공격력의 2배의 데미지를 입고 도망칩니다.\n");
				printf("계속 하시겠습니까? 1. 예 | 2. 아니오 : ");
				std::cin >> Run;
				if (Run == 1)
				{
					printf("도망칩니다.\n");
					Player.TakeDamage(Enemy[RandomMonster]->GetAttackPower() * 2);// 적 공격력의 2배 데미지를 받고 도망
					Select = true;
				}
				else
				{
					printf("메뉴로 돌아갑니다.\n");
				}
				break;
			}
			default:
			{
				printf("잘못 입력하셨습니다.\n");
			}
			}
		}
		if (Run == 1)
		{
			break;	// 도망침 판정
		}

		if (Enemy[RandomMonster]->GetHealth() <= 0)
		{
			printf("적을 처치했습니다.\n");
			
			Player.AddGold(Enemy[RandomMonster]->GetDropGold());	// 보상 골드 획득
			Player.AddExp(Enemy[RandomMonster]->GetDropExp());	// 보상 경험치 획득
			break;
		}
		int RandomSkill = rand() % 10;	// 몬스터 스킬 사용 여부
		if (RandomSkill < 3)	// 30%
		{
			Enemy[RandomMonster]->Skill(&Player);
		}
		else
			Enemy[RandomMonster]->ApplyDamage(&Player);
		printf("플레이어의 남은 HP : %.1f\n\n", Player.GetHealth());
		Player.UpdateGuard();	// 가드 스킬 남은 턴 업데이트
		Player.UpdateBerserk();	// 광폭화 스킬 남은 턴 업데이트
		Player.SetMana(2);	// 턴 마다 마나 2 회복
		if (Player.GetHealth() <= 0)	// 플레이어 체력 소진 시 패배
		{
			printf("패배하였습니다.\n");
			break;
		}
	}

	Player.ResetStatus();	// 전투가 끝날 때 가드와 광폭화 버프 해제
	for (int i = 0; i < Size; i++)	// 몬스터 객체 동적 배열 해제
	{
		delete Enemy[i];
		Enemy[i] = nullptr;
	}
}

void GameManager::ShopEvent(Player& Player)	// 보물상자 이벤트
{
	Shop Shop;	// 상인 클래스
	Shop.OpenShop(Player);	// 상점 열기
}

void GameManager::BoxEvent(Player& Player)
{
	int RandomItem = rand() % 100;	// 아이템 종류 결정
	int RandomCount;
	if (RandomItem < 5)	// 5%
	{
		RandomCount = rand() % 3;	// 아이템 종류 결정
		switch (RandomCount)
		{
		case(0):
		{
			printf("힘의 물약을 발견하였습니다.\n\n");
			Player.UsePassive(ItemInfo::MakeAttackItem("힘의 물약", "기본 공격력을 2.5 증가시킵니다", 100, 2.5f));
			break;
		}
		case(1):
		{
			printf("활력의 물약을 발견하였습니다.\n\n");
			Player.UsePassive(ItemInfo::MakeMaxHPItem("활력의 물약", "최대 체력을 10 증가시킵니다.", 100, 10.0f));
			break;
		}
		case(2):
		{
			printf("지능의 물약을 발견하였습니다.\n\n");
			Player.UsePassive(ItemInfo::MakeMaxMPItem("지능의 물약", "최대 마나를 5 증가시킵니다.", 100, 5));
			break;
		}
		}
	}
	else if (RandomItem < 25)	// 20%
	{
		RandomCount = rand() % 5 + 1;	// 아이템 개수 설정
		printf("HP 소형 물약을 %d개 발견하였습니다.\n\n",RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeHPItem("HP 소형 물약", "HP를 10 회복합니다.", 10, 10.0f));
	}
	else if (RandomItem < 35)	// 10%
	{
		RandomCount = rand() % 2 + 1;	// 아이템 개수 설정
		printf("HP 대형 물약을 %d개 발견하였습니다.\n\n", RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeHPItem("HP 대형 물약", "HP를 30 회복합니다.", 30, 30.0f));
	}
	else if (RandomItem < 45)	// 10%
	{
		RandomCount = rand() % 3 + 1;	// 아이템 개수 설정
		printf("마나 물약을 %d개 발견하였습니다.\n\n", RandomCount);
		for (int i = 0; i < RandomCount; i++)
			Player.AddItem(ItemInfo::MakeMPItem("마나 물약", "MP를 10 회복합니다.", 20, 10));
	}
	else
	{
		RandomCount = rand() % 100;
		printf("골드를 %d원 발견하였습니다.\n", RandomCount);
		Player.AddGold(RandomCount);
	}
}
