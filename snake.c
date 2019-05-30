#include "snake.h"
#include "food.h"
#include"map.h"
#include<stdlib.h>

SNAKE *snake_head = NULL, *snake_tail = NULL, *temp, front;
char control = 'w', direction = 'w';
int lose = 0, score = 0, level = 3;

void snake_create(void)                                   
{

    SNAKE *p = NULL;
    snake_head = (SNAKE *)malloc(sizeof(SNAKE));

	if (snake_head == NULL)
	{
		printf("Failed to allocate memory!\n");
	}
	else
	{
		snake_head->x = map_size / 2;
		snake_head->y = map_size / 2;
		snake_head->next = (SNAKE *)malloc(sizeof(SNAKE));

		p = snake_head->next;
		p->x = snake_head->x;
		p->y = snake_head->y + 1;

		p->next = (SNAKE *)malloc(sizeof(SNAKE));
		if (p->next == NULL)
		{
			printf("Failed to allocate memory!\n");
		}
		else
		{
			snake_tail = p->next;
			snake_tail->x = snake_head->x;
			snake_tail->y = snake_head->y + 2;
			snake_tail->next = NULL;

			for (p = snake_head; p != NULL; p = p->next)
				goprint(p->x, p->y, "o");
		}
		
	}
    
}

void snake_control(void)
{
	//뱀의 움직임을 조종하는 함수 snake_control

	while (!lose) {
		Sleep(600 / level);

		if (bonus_food.x != -1)
			progress_bar();

		if (_kbhit()) {
			control = _getch();
			if (control == 'p' || control == 'P')
				break;

			if (control == 'w' || control == 's' || control == 'a' || control == 'd' || control == 'W' || control == 'S' || control == 'A' || control == 'D') 
			{
				//뱀의 현재 이동 방향 direction과 입력받은 키 값 control이 동일한 경우와 정반대인 경우가 아닐 때
				// direction값을 control값으로 변경한다. (뱀의 이동방향을 변경한다)
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
	//뱀의 머리 부분과 boundary와 충돌이 발생할 경우
	//snake를 반대방향으로 이동시키는 함수 

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


SNAKE* check_get_Food(SNAKE front,SNAKE * snake_head)
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
	}
	else
	{
		goprint(snake_tail->x, snake_tail->y, "  ");
		snake_tail->next = snake_head;
		snake_head = snake_tail;
		snake_tail = temp;
		snake_tail->next = NULL;
		snake_head->x = front.x;
		snake_head->y = front.y;
		goprint(snake_head->x, snake_head->y, "o");
	}
	return snake_head;
}


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
	snake_head = check_get_Food(front, snake_head);
}

void snake_free(void)
{
	SNAKE *p1, *p2;
	for (p1 = snake_head, p2 = p1; p1 != NULL; p2 = p1) {
		p1 = p1->next;
		free(p2);
	}
}
