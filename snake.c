#include "snake.h"
#include<stdlib.h>

extern int bonus_score, map_size;
extern FOOD food, bonus_food;
SNAKE *snake_head = NULL, *snake_tail = NULL, *temp, front;
char control = 'w', direction = 'w';
int lose = 0, score = 0, level = 3;

void snake_create(void)                                    /* Make the snake at the beginning */
{

    SNAKE *p = NULL;
    snake_head = (SNAKE *)malloc(sizeof(SNAKE));
    snake_head->x = map_size / 2;
    snake_head->y = map_size / 2;
    snake_head->next = (SNAKE *)malloc(sizeof(SNAKE));
    p = snake_head->next;
    p->x = snake_head->x;
    p->y = snake_head->y + 1;
    p->next = (SNAKE *)malloc(sizeof(SNAKE));
    snake_tail = p->next;
    snake_tail->x = snake_head->x;
    snake_tail->y = snake_head->y + 2;
    snake_tail->next = NULL;
    for(p = snake_head; p != NULL; p = p->next)
        goprint(p->x, p->y, "o");

}

void snake_control(void)
{
	while (!lose) {
		Sleep(600 / level);
		if (bonus_food.x != -1)
			progress_bar();
		if (_kbhit()) {
			control = _getch();
			if (control == 'p' || control == 'P')
				break;
			if (control == 'w' || control == 's' || control == 'a' || control == 'd' || control == 'W' || control == 'S' || control == 'A' || control == 'D') {
				if ((direction == 'w' || direction == 'W') && (control == 's' || control == 'S'));
				else if ((direction == 's' || direction == 'S') && (control == 'w' || control == 'W'));
				else if ((direction == 'a' || direction == 'A') && (control == 'd' || control == 'D'));
				else if ((direction == 'd' || direction == 'D') && (control == 'a' || control == 'A'));
				else direction = control;
			}
		}
		snake_move();
	}
	goprint(snake_head->x, snake_head->y, "  ");
}

SNAKE check_stage_collision(SNAKE front)
{
	SNAKE tmp = front;
	if (tmp.x == map_size)
		tmp.x = 1;
	if (tmp.x == 0)
		tmp.x = map_size - 1;
	if (tmp.y == map_size)
		tmp.y = 1;
	if (tmp.y == 0)
		tmp.y = map_size - 1;
	return tmp;
}

int check_Gameover(SNAKE * snake_head)
{
	SNAKE *p1;
	BLOCK *p2;
	int lose = 0;

	for (p1 = snake_head, p2 = block_head; p1 != snake_tail || p2 != NULL;) {
		if (p1 != snake_tail) {
			if (front.x == p1->x && front.y == p1->y) {
				lose = 1;
				break;
			}
			if (p1->next == snake_tail)
				temp = p1;
			p1 = p1->next;
		}
		if (p2 != NULL) {
			if (front.x == p2->x && front.y == p2->y) {
				lose = 1;
				break;
			}
			p2 = p2->next;
		}
	}
	return lose;
}

/*
SNAKE* check_Food_Collision(SNAKE front,SNAKE * snake_head)
{
	if ((front.x == food.x && front.y == food.y) || (front.x == bonus_food.x && front.y == bonus_food.y))
	{

		temp = (SNAKE *)malloc(sizeof(SNAKE));
		*temp = front;
		temp->next = snake_head;
		snake_head = temp;
		goprint(snake_head->x, snake_head->y, "o");
		if (front.x == bonus_food.x) {
			score += bonus_score / 2 * level;
			bonus_food.x = -1, bonus_food.y = -1, bonus_score = 100;
			notice_bonus();
		}
		else {
			bonus++;
			score += level;
			food_create();
		}
		return ;
		//return 필요함 
	}
}
*/

void snake_move(void)
{
	int flag = 0;

	switch (direction) {
	case 'w':
		front.x = snake_head->x;
		front.y = snake_head->y - 1;
		break;
	case 's':
		front.x = snake_head->x;
		front.y = snake_head->y + 1;
		break;
	case 'a':
		front.x = snake_head->x - 1;
		front.y = snake_head->y;
		break;
	case 'd':
		front.x = snake_head->x + 1;
		front.y = snake_head->y;
		break;
	case 'W':
		front.x = snake_head->x;
		front.y = snake_head->y - 1;
		break;
	case 'S':
		front.x = snake_head->x;
		front.y = snake_head->y + 1;
		break;
	case 'A':
		front.x = snake_head->x - 1;
		front.y = snake_head->y;
		break;
	case 'D':
		front.x = snake_head->x + 1;
		front.y = snake_head->y;
		break;
	}
	
	front = check_stage_collision(front);
	lose = check_Gameover(snake_head);
	if (lose == 1)
		return;
	//snake_head = check_Food_Collision(front, snake_head);
	//밑에 조건문을 함수로 분리하고자 함.... 
	if ((front.x == food.x && front.y == food.y) || (front.x == bonus_food.x && front.y == bonus_food.y))
	{

		temp = (SNAKE *)malloc(sizeof(SNAKE));
		*temp = front;
		temp->next = snake_head;
		snake_head = temp;
		goprint(snake_head->x, snake_head->y, "o");
		if (front.x == bonus_food.x) {
			score += bonus_score / 2 * level;
			bonus_food.x = -1, bonus_food.y = -1, bonus_score = 100;
			notice_bonus();
		}
		else {
			bonus++;
			score += level;
			food_create();
		}
		return;
		//return 필요함 
	}

	goprint(snake_tail->x, snake_tail->y, "  ");
	snake_tail->next = snake_head;
	snake_head = snake_tail;
	snake_tail = temp;
	snake_tail->next = NULL;
	snake_head->x = front.x;
	snake_head->y = front.y;
	goprint(snake_head->x, snake_head->y, "o");

}

void snake_free(void)
{
	SNAKE *p1, *p2;
	for (p1 = snake_head, p2 = p1; p1 != NULL; p2 = p1) {
		p1 = p1->next;
		free(p2);
	}
}
