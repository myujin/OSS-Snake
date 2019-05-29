#include "snake.h"
#include<stdlib.h>
#include"interface.h"


extern FOOD food, bonus_food;
SNAKE *snake_head = NULL, *snake_tail = NULL, *temp, front;


SNAKE check_stage_collision(SNAKE front, gameData data);
SNAKE* check_get_Food(SNAKE front, SNAKE * snake_head, gameData data);
int check_Gameover(SNAKE * snake_head);
void snake_create(gameData data);
gameData snake_move(gameData data);
gameData snake_control(gameData data);
void snake_free(void);

void snake_create(gameData data)                                    /* Make the snake at the beginning */
{

    SNAKE *p = NULL;
    snake_head = (SNAKE *)malloc(sizeof(SNAKE));
    snake_head->x = data.map_size / 2;
    snake_head->y = data.map_size / 2;
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

gameData snake_move(gameData data)
{
	
	switch (data.direction) {
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

	front = check_stage_collision(front, data);
	data.lose = check_Gameover(snake_head);
	if (data.lose == 1)
		return data;
	else
	{
		snake_head = check_get_Food(front, snake_head, data);
		return data;
	}

}

gameData snake_control(gameData data)
{
	while (!data.lose) {
		Sleep(600 / data.level);
		if (bonus_food.x != -1)
			progress_bar(data);
		if (_kbhit()) {
			data.control = _getch();
			if (data.control == 'p' || data.control == 'P')
				break;
			if (data.control == 'w' || data.control == 's' || data.control == 'a' || data.control == 'd' || data.control == 'W' || data.control == 'S' || data.control == 'A' || data.control == 'D') {
				if ((data.direction == 'w' || data.direction == 'W') && (data.control == 's' || data.control == 'S'));
				else if ((data.direction == 's' || data.direction == 'S') && (data.control == 'w' || data.control == 'W'));
				else if ((data.direction == 'a' || data.direction == 'A') && (data.control == 'd' || data.control == 'D'));
				else if ((data.direction == 'd' || data.direction == 'D') && (data.control == 'a' || data.control == 'A'));
				else data.direction = data.control;
			}
		}
		data=snake_move(data);
	}
	goprint(snake_head->x, snake_head->y, "  ");
	return data;
}

SNAKE check_stage_collision(SNAKE front,gameData data)
{
	SNAKE tmp = front;
	if (tmp.x == data.map_size)
		tmp.x = 1;
	if (tmp.x == 0)
		tmp.x = data.map_size - 1;
	if (tmp.y == data.map_size)
		tmp.y = 1;
	if (tmp.y == 0)
		tmp.y = data.map_size - 1;
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


SNAKE* check_get_Food(SNAKE front,SNAKE * snake_head,gameData data)
{
	if ((front.x == food.x && front.y == food.y) || (front.x == bonus_food.x && front.y == bonus_food.y))
	{

		temp = (SNAKE *)malloc(sizeof(SNAKE));
		*temp = front;
		temp->next = snake_head;
		snake_head = temp;
		goprint(snake_head->x, snake_head->y, "o");
		if (front.x == bonus_food.x) {
			data.score += data.bonus_score / 2 * (data.level);
			bonus_food.x = -1, bonus_food.y = -1, data.bonus_score = 100;
			notice_bonus(data);
		}
		else {
			data.bonus++;
			data.score += data.level;
			food_create(data);
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




void snake_free(void)
{
	SNAKE *p1, *p2;
	for (p1 = snake_head, p2 = p1; p1 != NULL; p2 = p1) {
		p1 = p1->next;
		free(p2);
	}
}
