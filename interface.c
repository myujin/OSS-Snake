#include "interface.h"
#include<stdlib.h>
#pragma warning(disable:4996)
extern FOOD bonus_food;
extern int lose, level, map_size, bonus, bonus_score;
extern char control, direction;

int margin;


void welcome(void)
{
	setConsoleSize(55, 20);
	lose = 0, level = 3, map_size = 30, score = 0, bonus = 0, margin = map_size + 5;
	control = 'w', direction = 'w';
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
		map_block(map_size);
}

void tips(void)
{
	setConsoleSize(140, 40);
	gotoxy(margin, 5);
	printf("Level: %d", level);
	gotoxy(margin, 7);
	printf("Map size: %d * %d", map_size, map_size);
	goprint(margin, 9, "Play with \"wsad\"");
	goprint(margin, 11, "Click to pause / Press \"wsad\" to continue / Press 'p' to quit");
}

void notice_bonus(void)
{
	if (bonus == 5) {
		goprint(margin, 13, "Award Food:");
		goprint(margin, 14, "0 0 0 0 0 ");
		bonus_score = 100;
		bonus = 0;
	}
	if (bonus_food.x == -1) {
		gotoxy(margin, 13);
		printf("           ");
		gotoxy(margin, 14);
		printf("                    ");
	}
	gotoxy(margin, 3);
	printf("Your score: %d", score);
}

void quit(void)
{
	if (lose) {
		system("color 01");
		Sleep(100);
		system("color 0F");
		goprint(map_size / 2 - 2, map_size / 2 - 3, "You lose!");
	}
	else
		goprint(map_size / 2 - 2, map_size / 2 - 3, "You quit!");
	gotoxy(map_size / 2 - 4, map_size / 2 - 1);
	printf("Your score: %5d", score);
	goprint(map_size / 2 - 6, map_size / 2 + 1, " Press Enter to continue");
	gotoxy(0, 0);
	while (getchar() != '\n');
	system("cls");
}

void progress_bar(void)
{
	goprint(margin + bonus_score / 10, 14, " ");
	if ((bonus_score--) == 0) {
		goprint(margin, 13, "           ");
		goprint(margin, 14, "                    ");
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