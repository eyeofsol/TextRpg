C++ TextRPG

TextRPG.Ver2 기준입니다.
(TextRPG -> 몬스터 이동 구현 임시 프로젝트)

1. 제목 : 광산 미로 탐험
 
2. 기능 : 랜덤으로 생성되는 미로 광산에서 랜덤 좌표에 생성되는 열쇠를 찾아 획득하고 랜덤으로 생성되는 출구를 찾아 층을 내려가는 게임.
  움직일때마다 확률적으로 전투, 떠돌이 상인, 랜덤상자가 등장함

3. 클래스 다이어그램
<img width="1411" height="1124" alt="TextRpg_Class" src="https://github.com/user-attachments/assets/83b2c9f1-f080-4bf3-80ee-456ae810d587" />

****클래스 및 인터페이스****
1) GameManager
   게임의 기본적인 진행을 관리하는 클래스

**변수**
- Map : Map 객체를 가져오는 변수
- Stage : 진행한 스테이지를 저장하는 int형 변수
- HasKey : 플레이어의 열쇠 소지 여부를 조사하는 bool형 변수
- MaxStage : 최종 스테이지의 단계를 지정하는 int형 상수

**함수**
- PlayGame() : 게임을 시작하는 void 함수
- FindStartPosition(플레이어의 좌표) : 플레이어의 좌표를 받아와 시작 위치를 설정해주는 void 함수
- PrintAvailableMoves(플레이어의 좌표) : 플레이어의 좌표를 받아와 이동 가능한 방향을 출력해주는 int 함수
- IsWall(x좌표,y좌표) : 파라미터로 받아온 (x,Y)좌표에 있는 타일이 벽인지 확인하는 bool 함수
- IsEnd(플레이어의 좌표) : 플레이어의 좌표가 출구의 좌표와 일치하는지 확인하는 bool 함수
- IsKey(플레이어의 좌표) : 플레이어의 좌표가 열쇠 위치의 좌표와 일치하는지 확인하는 bool 함수
- GetMoveInput(이동 가능 방향) : 키보드 입력을 받아 이동 방향의 비트플래그를 리턴하는 MoveDirection 함수
- MoveEventProcess(플레이어 객체, 스테이지 단계) : 플레이어가 움직일 때마다 발생할 수 있는 이벤트를 실행하는 void 함수
- BattleEvent(플레이어 객체, 스테이지 단계) : 랜덤으로 나오는 전투 이벤트 void 함수
- ShopEvent(플레이어 객체) : 랜덤으로 나오는 상점 이벤트 void 함수
- BoxEvent(플레이어 객체) : 랜덤으로 나오는 보물상자 이벤트 void 함수

2) ICanBattle
   전투 이벤트에서 객체가 하는 행동들을 정의하는 인터페이스

**함수**
- ApplyDamage(데미지를 받는 타겟) : 파라미터로 받은 타겟에게 데미지 공식을 계산하여 Target의 TakeDamge에 넘겨주는 void 함수
- TakeDamage(데미지 수치) : 파라미터로 받은 데미지 수치를 객체 자체에 적용하는 void 함수
- Attack() : 해당 객체의 공격을 실행하는 void 함수
  
3) Actor
   전투 이벤트에 등장하는 객체들의 기본 속성과 기능을 담고 있는 클래스

**변수**
- Name : 객체의 이름을 담는 string 변수
- Health : 객체의 체력을 담는 float 변수
- MaxHealth : 객체의 최대 체력을 담는 float 변수
- AttackPower : 객체의 공격력을 담는 float 변수

**함수**
- SetHealth(체력 수치) : 파라미터로 받은 수치를 현재 체력에 적용하는 void 함수
- SetAttackPower(공격력 수치) : 파라미터로 받은 수치를 현재 공격력에 적용하는 void 함수
- ApplyDamage(데미지를 받는 타겟) : 파라미터로 받은 타겟에게 데미지 공식을 계산하여 Target의 TakeDamge에 넘겨주는 void 함수
- TakeDamage(데미지 수치) : 파라미터로 받은 데미지 수치를 객체 자체에 적용하는 void 함수
- PrintStatus() : 객체의 정보를 출력하는 void 함수
- IsAlive() : 객체가 현재 살아있는 상태인지 확인하는 bool 함수

- GetName() : 객체의 이름을 리턴해주는 string 함수
- GetHealth() : 객체의 체력을 리턴해주는 float 함수
- GetAttackPower() : 객체의 공격력을 리턴해주는 float 함수
- GetMaxHealth() : 객체의 체력을 리턴해주는 float 함수

4) Player
   사용자가 제어하는 플레이어 클래스

**변수**
- CurrentPosition : 플레이어의 현재 좌표를 담는 Position 변수
- Gold : 플레이어가 가지고 있는 골드를 담는 int 변수
- Level : 플레이어의 현재 레벨을 담는 int 변수
- Exp : 플레이어의 현재 경험치를 담는 int 변수
- MaxExp : 플레이어의 경험치 상한을 담는 int 변수
- Mana : 플레이어의 현재 마나를 담는 int 변수
- MaxMana : 플레이어의 마나 상한을 담는 int 변수
- AllSkills : 플레이어가 사용 가능한 스킬을 담는 vector 변수
- IsGuard : 플레이어의 방어(스킬2) 상태를 담는 bool 변수
- IsBerserk : 플레이어의 광폭화(스킬3) 상태를 담는 bool 변수
- GuardTurn : 플레이어의 방어(스킬2)의 남은 턴을 담는 int 변수
- BerserkTurn : 플레이어의 광폭화(스킬3)의 남은 턴을 담는 int 변수
- Inventory : 플레이어가 소지한 아이템을 담는 map 변수

**함수**
기본 기능
- Attack() : 기본 공격을 실행하는 void 함수
- PrintStatus() : 현재 상태를 출력하는 void 함수
보상 기능
- AddGold(골드 수치) : 전투 후 몬스터에게 떨어진 골드를 추가하는 void 함수
- AddExp(경험치 수치) : 전투 후 몬스터에게 떨어진 경험치를 추가하는 void 함수
- Levelup() : 전투 후 경험치가 상한에 달했을 시 플레이어의 능력치를 증가시키는 void 함수
스킬 기능
- UseSkill(스킬을 적용할 타겟, 선택 확인) : 전투 시 스킬을 사용할 때 실행되는 void 함수
- PrintSkill() : 사용 가능한 스킬을 출력하는 void 함수
- DoubleAttack(스킬을 적용할 타겟) : 연속 베기(스킬1)을 사용하는 void 함수
- SetGuard(버프 지속 턴수) : 방어(스킬2)를 사용하는 void 함수
- UpdateGuard() : 방어(스킬2)의 남은 턴을 갱신하는 void 함수
- SetBerserk(버프 지속 턴수) : 광폭화(스킬3)를 사용하는 void 함수
- UpdateBerserk() : 광폭화(스킬3)의 남은 턴을 갱신하는 void 함수
- ResetStatus() : 전투 종료 시 버프 상태를 초기화 시키는 void 함수
아이템 기능
- AddItem(아이템 정보) : 획득한 아이템을 인벤토리에 추가하는 void 함수
- OpenInventory(선택 확인) : 플레이어의 현재 인벤토리를 여는 void 함수
- UseItem(아이템 정보, 선택 확인) : 인벤토리의 소모품을 사용하는 void 함수
- UsePassiveItem(아이템 정보) : 패시브 아이템을 획득할 시 바로 사용되게 하는 void 함수

- CheckGuard() : 플레이어가 현재 방어 상태인지 확인하는 bool 함수
- CheckBerserk() : 플레이어가 현재 광폭화 상태인지 확인하는 bool 함수
- GetGold() : 플레이어의 소지 골드를 리턴하는 int 함수
- GetMana() : 플레이어의 현재 마나를 리턴하는 int 함수
- GetPosition() : 플레이어의 현재 좌표를 리턴하는 Position 함수
- AddAttackPower(공격력 수치) : 파라미터로 받은 공격력 수치만큼 현재 공격력에 더하는 void 함수
- SetMana(마나 수치) : 파라미터로 받은 마나 수치만큼 현재 마나에 더하는 void 함수

5) Monster
   전투 이벤트 실행시 나오는 적 클래스

**변수**
DropGold : 적이 보상으로 가지고 있는 골드를 담는 int 변수
DropExp : 적이 보상으로 가지고 있는 경험치를 담는 int 변수

**함수**
- Attack() : 기본 공격을 실행하는 void 함수
- PrintStatus() : 현재 상태를 출력하는 void 함수
- Skill(스킬을 적용할 타겟) : 적이 스킬을 사용할 때 실행되는 void 함수

- GetDropGold() : 적이 보상으로 가지고 있는 골드를 리턴하는 int 함수
- GetDropExp() : 적이 보상으로 가지고 있는 경험치를 리턴하는 int 함수

5_1) Goblin
적 중 한 종류로 나오는 고블린 클래스

**함수**
- Attack() : 기본 공격을 실행하는 void 함수
- Skill(스킬을 적용할 타겟) : 적이 스킬을 사용할 때 실행되는 void 함수
- Shoot(스킬을 적용할 타겟) : 고블린의 고유 스킬인 연속 공격을 사용하는 void 함수

5_2) Zombie
적 중 한 종류로 나오는 좀비 클래스

**함수**
- Attack() : 기본 공격을 실행하는 void 함수
- Skill(스킬을 적용할 타겟) : 적이 스킬을 사용할 때 실행되는 void 함수
- Recover() : 좀비의 고유 스킬인 회복을 사용하는 void 함수

5_3) Orc
적 중 한 종류로 나오는 오크 클래스

**함수**
- Attack() : 기본 공격을 실행하는 void 함수
- Skill(스킬을 적용할 타겟) : 적이 스킬을 사용할 때 실행되는 void 함수
- Hawling() : 오크의 고유 스킬인 공격력 증가를 사용하는 void 함수

6) Shop
   랜덤으로 나오는 상점 이벤트를 담당하는 클래스

**변수**
- Item : 판매 아이템의 종류를 담고 있는 vector 변수

**함수**
- OpenShop(플레이어 객체) : 상점을 열어 판매 아이템을 보여주는 void 함수
- BuyItem(플레이어 객체, 아이템 정보) : 플레이어가 입력한 아이템을 판매하고 골드를 차감하는 void 함수

7) Map
   맵의 생성과 출력을 담당하는 클래스

**변수**
- MaxSie : 맵의 최대 크기를 담는 int 상수
- Maze[최대 크기][최대 크기] : 만들어진 맵을 이차원 배열로 저장하는 int 변수
- Width : 맵의 너비를 담는 int 변수
- Height : 맵의 높이를 담는 int 변수
- dx[방향 수치] : 맵을 생성할때 좌우 방향을 담는 int 변수
- dy[방향 수치] : 맵을 생성할때 상하 방향을 담는 int 변수

**함수**
- ShuffleDir(방향 배열) : 맵을 생성할 때 방향을 랜덤으로 섞는 void 함수
- Carve(현재까지 뚫은 위치의 x좌표, 현재까지 뚫은 위치의 y좌표) : 벽으로 초기화된 맵에 길을 뚫는 void 함수
- GenerateMap() : 맵을 랜덤하게 생성해주는 void 함수
- SetExitPoint() : 랜덤한 위치에 출구를 생성하는 void 함수
- SetKeyPoint() : 랜덤한 위치에 열쇠를 생성하는 void 함수
- FindStartPosition(플레이어 좌표) : 플레이어의 시작 위치를 설정하는 void 함수
- PrintMap(플레이어 좌표) : 만들어진 맵을 출력하는 void 함수
- PickupKey(열쇠의 x좌표, 열쇠의 y좌표) : 플레이어가 열쇠를 획득 시 맵에서 삭제해주는 함수

- GetWidth() : 맵의 너비를 리턴하는 int 함수
- GetHeight() : 맵의 높이를 리턴하는 int 함수
- GetMaze(x,y) : 파라미터로 받아온 맵의 (x,y)좌표의 타일을 리턴하는 int 함수

****구조체 및 enum****
1) SkillInfo
   스킬의 정보를 담는 구조체

**변수**
- Name : 스킬의 이름을 담는 string 변수
- Detail : 스킬의 설명을 담는 string 변수
- SkillNum : 스킬의 인덱스 넘버를 담는 int 변수
- RequiredLevel : 스킬을 배우는데 필요한 레벨을 담는 int 변수
- ManaCont : 스킬을 사용하는데 필요한 마나를 담는 int 변수
- Learned : 스킬을 배웠는지 확인하는 bool 변수

2) ItemInfo
   아이템의 정보를 담는 구조체

**변수**
- Name : 아이템의 이름을 담는 string 변수
- Detail : 아이템의 설명을 담는 string 변수
- Price : 아이템의 가격을 담는 int 변수
- HPAmount : 아이템의 체력 회복량을 담는 float 변수
- MPAmount : 아이템의 마나 회복량을 담는 int 변수
- AttackAmount : 아이템의 공격 증가량을 담는 float 변수
- MaxHPAmount : 아이템의 최대 체력 증가량을 담는 float 변수
- MaxMPAmount : 아이템의 최대 마나 증가량을 담는 int 변수

**함수**
- MakeHPItem(이름,설명,가격,체력 회복량) : 체력 회복 아이템을 만드는 ItemInfo 함수
- MakeMPItem(이름,설명,가격,마나 회복량) : 마나 회복 아이템을 만드는 ItemInfo 함수
- MakeAttackItem(이름,설명,가격,공격력 증가량) : 공격력 증가 아이템을 만드는 ItemInfo 함수
- MakeMaxHPItem(이름,설명,가격,최대 체력 증가량) : 최대 체력 증가 아이템을 만드는 ItemInfo 함수
- MakeMaxMPItem(이름,설명,가격,최대 마나 증가량) : 최대 마나 증가 아이템을 만드는 ItemInfo 함수

3) Position
   좌표를 담는 구조체

**변수**
- x : x좌표를 담는 int 변수
- y : y좌표를 담는 int 변수

**연산자**
- operator+ : 좌표를 더해주는 Position 연산자
- operator- : 좌표를 빼주는 Position 연산자
- operator== : 좌표가 일치하는지 검사하는 Position 연산자
- operator!= : 좌표를 다른지 검사하는 Position 연산자

4) MapTile
   맵의 타일을 정의하는 enum

**변수**
- Path : 통로 = 0
- Wall : 벽 = 1
- Start : 시작 위치 = 2
- End : 출구 위치 = 3
- Key : 열쇠 위치 = 4

5) MoveDirection
   이동 방향을 정의하는 enum

**변수**
- DirNone : 방향 없음 = 0
- DirUp : 위 방향 = 0001
- DirDown : 아래 방향 = 0010
- DirLeft : 좌측 방향 = 0100
- DirRight : 우측 방향 = 1000
  
4. 코드 플로우차트
<img width="1461" height="1112" alt="TextRPG_FlowChart" src="https://github.com/user-attachments/assets/ae8d23da-517c-47f0-b184-9edc5cc2f0a9" />

5. 실행 화면
<img width="979" height="512" alt="image" src="https://github.com/user-attachments/assets/af9b774d-b642-4acc-9a1a-7c68a25121c5" />
