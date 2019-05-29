#include "interface.h"
#include<stdlib.h>
#pragma warning(disable:4996)
extern FOOD bonus_food;


gameData set_GameData(gameData data)
{
	data.lose = 0; data.level = 3; data.map_size = 30; data.bonus = 0;
	data.margin = data.map_size + 5; data.score = 0; data.bonus_score = 0;
	data.control = 'w'; data.direction = 'w';

	return data;
}

gameData welcome(gameData data)
{
	setConsoleSize(55, 20);

	//data = set_GameData(data);
	//lose = 0, level = 3, map_size = 30, score = 0, bonus = 0, margin = map_size + 5;
	//control = 'w', direction = 'w';
	int opt;
	char map_choice = NULL;

	goprint(4, 4, "Welcome to the Snake by Lst");
	goprint(6, 6, "Start by number:\n\n");
	printf("1. Quick game\n2. Customized game\n3. Exit\n\n*** Please play in English Input Method ***\n");

	opt = _getch() - '0';
	switch (opt) {
	case 1:
		break;
	case 2:
		printf("\nChoose level from 1 to 9 or... (Press Enter):");
		scanf("%d", &data.level);

		do {
			printf("\nInput map size no less than 5 (Press Enter):");
			scanf("%d", &data.map_size);
			data.margin = data.map_size + 5;
		} while (data.map_size < 5);

		getchar();
		printf("\nDo you want to create the boundary blocks? Y / N:");
		map_choice = getchar();
		getchar();
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
	system("cls");
	//map_choice에 대한 기능 개선이 필요해 보임 
	if (map_choice == 'y' || map_choice == 'Y')
		map_block(data.map_size);

	return data;
}

void tips(gameData data)
{
	setConsoleSize(140, 40);
	gotoxy(data.margin, 5);
	printf("Level: %d", data.level);
	gotoxy(data.margin, 7);
	printf("Map size: %d * %d", data.map_size, data.map_size);
	goprint(data.margin, 9, "Play with \"wsad\"");
	goprint(data.margin, 11, "Click to pause / Press \"wsad\" to continue / Press 'p' to quit");
}

gameData notice_bonus(gameData data)
{
	if (data.bonus == 5) {
		goprint(data.margin, 13, "Award Food:");
		goprint(data.margin, 14, "0 0 0 0 0 ");
		data.bonus_score = 100;
		data.bonus = 0;
	}
	if (bonus_food.x == -1) {
		gotoxy(data.margin, 13);
		printf("           ");
		gotoxy(data.margin, 14);
		printf("                    ");
	}
	gotoxy(data.margin, 3);
	printf("Your score: %d", data.score);

	return data;
}

gameData quit(gameData data)
{
	if (data.lose) {
		system("color 01");
		Sleep(100);
		system("color 0F");
		goprint(data.map_size / 2 - 2, data.map_size / 2 - 3, "You lose!");
	}
	else
		goprint(data.map_size / 2 - 2, data.map_size / 2 - 3, "You quit!");

	gotoxy(data.map_size / 2 - 4, data.map_size / 2 - 1);
	printf("Your score: %5d", data.score);
	goprint(data.map_size / 2 - 6, data.map_size / 2 + 1, " Press Enter to continue");

	gotoxy(0, 0);
	while (getchar() != '\n');
	data = set_GameData(data);
	system("cls");
	return data;
}

void progress_bar(gameData data)
{
	goprint(data.margin + data.bonus_score / 10, 14, " ");
	if ((data.bonus_score--) == 0) {
		goprint(data.margin, 13, "           ");
		goprint(data.margin, 14, "                    ");
		goprint(bonus_food.x, bonus_food.y, "  ");
		bonus_food.x = -1, bonus_food.y = -1;
	}
}

void removeCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void setConsoleSize(int w, int h) { // 열, 행 
	COORD temp = { 999, 999 };
	COORD siz = { w,h };
	SMALL_RECT sr;
	sr.Left = 0;
	sr.Top = 0;
	sr.Right = w - 1;
	sr.Bottom = h - 1;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), temp);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &sr);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), siz);
}