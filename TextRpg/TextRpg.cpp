#define TEST_MODE
#include<iostream>
#include<stdio.h>
#include<fstream>
#include"TextRpg.h"
#include"GameManager.h"

int main()
{
	GameManager GameManager;
#ifndef TEST_MODE
	Test test;
	test.TestBattle();
#endif // TEST_MODE

#ifdef TEST_MODE
	srand(time(0));
	int Menu = -1;
	while (Menu != 0)
	{
		GameManager.InitializeMaze();
		GameManager.MazeEscapeRun();
		GameManager.ClearMaze();
		printf("게임이 종료되었습니다. 다시 플레이하시겠습니까?\n");
		printf("1. 예 ,0. 아니오 :");
		std::cin >> Menu;
	}
#endif // !TEST_MODE

	return 0;
}


