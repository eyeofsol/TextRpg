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
		printf("������ ����Ǿ����ϴ�. �ٽ� �÷����Ͻðڽ��ϱ�?\n");
		printf("1. �� ,0. �ƴϿ� :");
		std::cin >> Menu;
	}
#endif // !TEST_MODE

	return 0;
}


