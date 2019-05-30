#include "interface.h"
#include "snake.h"
#include "food.h"
#include "map.h"
#include<stdlib.h>
#pragma warning(disable:4996)

int margin;

void Welcome(void)
{
	SetConsoleSize(55, 20);
	lose = 0, level = 3, map_size = 30, score = 0, bonus = 0, margin = map_size + 5;
	control = 'w', direction = 'w';

	int opt;
	char map_choice = NULL;
	Go_print(4, 4, "Welcome to the Snake by Lst");
	Go_print(6, 6, "Start by number:\n\n");
	printf("1. Quick game\n2. Customized game\n3. Exit\n\n*** Please play in English Input Method ***\n");

	opt = _getch() - '0';
	switch (opt) {
	case 1:
		break;
	case 2:
		printf("\nChoose level from 1 to 9 or... (Press Enter):");
		scanf("%d", &level);
		do {
			printf("\nInput map size no less than 5 (Press Enter):");
			scanf("%d", &map_size);
			margin = map_size + 5;
		} while (map_size < 5);

		getchar();
		printf("\nDo you want to create the boundary blocks? Y / N:");
		map_choice = getchar();
		getchar();
		break;
	case 3:
		exit(0);
	}
	system("cls");
	if (map_choice == 'y' || map_choice == 'Y')
		Map_block(map_size);
}

void Tips(void)
{
	SetConsoleSize(140, 40);

	Go_to_xy(margin, 5);
	printf("Level: %d", level);

	Go_to_xy(margin, 7);
	printf("Map size: %d * %d", map_size, map_size);

	Go_print(margin, 9, "Play with \"wsad\"");
	Go_print(margin, 11, "Click to pause / Press \"wsad\" to continue / Press 'p' to quit");
}

void Notice_bonus(void)
{
	if (bonus == 5) 
	{
		Go_print(margin, 13, "Award Food:");
		Go_print(margin, 14, "0 0 0 0 0 ");
		bonus_score = 100;
		bonus = 0;
	}
	if (bonus_food.x == -1)
	{
		Go_to_xy(margin, 13);
		printf("           ");
		Go_to_xy(margin, 14);
		printf("                    ");
	}

	Go_to_xy(margin, 3);
	printf("Your score: %d", score);
}

void Quit(void)
{
	if (lose) {
		system("color 01");
		Sleep(100);
		system("color 0F");
		Go_print(map_size / 2 - 2, map_size / 2 - 3, "You lose!");
	}
	else
		Go_print(map_size / 2 - 2, map_size / 2 - 3, "You quit!");

	Go_to_xy(map_size / 2 - 4, map_size / 2 - 1);
	printf("Your score: %5d", score);

	Go_print(map_size / 2 - 6, map_size / 2 + 1, " Press Enter to continue");

	Go_to_xy(0, 0);
	while (getchar() != '\n');
	system("cls");
}

void Progress_bar(void)
{
	Go_print(margin + bonus_score / 10, 14, " ");
	if ((bonus_score--) == 0) {
		Go_print(margin, 13, "           ");
		Go_print(margin, 14, "                    ");
		Go_print(bonus_food.x, bonus_food.y, "  ");
		bonus_food.x = -1, bonus_food.y = -1;
	}
}

void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void SetConsoleSize(int w, int h) { // 열, 행 
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