#include "snake.h"
#include "food.h"
#include"map.h"
#include<stdlib.h>

SNAKE *snake_head = NULL, *snake_tail = NULL, *temp, front;
char control = 'w', direction = 'w';
int lose = 0, score = 0, level = 3;

void Print_Snake(SNAKE *snake_head)
{
	SNAKE *p;
	for (p = snake_head; p != NULL; p = p->next)
		Go_print(p->x, p->y, "o");
}

void Remove_Snake(SNAKE *snake_tail)
{
	Go_print(snake_tail->x, snake_tail->y, "  ");
}

void Snake_create(void)                                   
{
    SNAKE *p = NULL;
    snake_head = (SNAKE *)malloc(sizeof(SNAKE));

	if (snake_head == NULL)
	{
		printf("Failed to allocate memory!\n");
		exit(1);
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
			exit(1);
		}
		else
		{
			snake_tail = p->next;
			snake_tail->x = snake_head->x;
			snake_tail->y = snake_head->y + 2;
			snake_tail->next = NULL;

			Print_Snake(snake_head);
		}
	}
}

void Snake_control(void)
{
	//���� �������� �����ϴ� �Լ� Snake_control

	while (!lose) {
		Sleep(600 / level);

		if (bonus_food.x != -1)
			Progress_bar();

		if (_kbhit()) {
			control = _getch();
			if (control == 'p' || control == 'P')
				break;

			if (control == 'w' || control == 's' || control == 'a' || control == 'd' || control == 'W' || control == 'S' || control == 'A' || control == 'D') 
			{
				//���� ���� �̵� ���� direction�� �Է¹��� Ű �� control�� ������ ���� ���ݴ��� ��찡 �ƴ� ��
				// direction���� control������ �����Ѵ�. (���� �̵������� �����Ѵ�)
				
				if ((direction == 'w' || direction == 'W') && (control == 's' || control == 'S'));
				else if ((direction == 's' || direction == 'S') && (control == 'w' || control == 'W'));
				else if ((direction == 'a' || direction == 'A') && (control == 'd' || control == 'D'));
				else if ((direction == 'd' || direction == 'D') && (control == 'a' || control == 'A'));
				else direction = control;
				
			}
		}
		Snake_move();
	}
}

SNAKE check_stage_collision(SNAKE front)
{
	//���� �Ӹ� �κа� boundary�� �浹�� �߻��� ���
	//snake�� �ݴ�������� �̵���Ű�� �Լ� 

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

int Check_Gameover(SNAKE * snake_head)
{
	SNAKE *p1;
	BLOCK *p2;
	int lose = 0;

	//���� ������ ���ǿ��� �� ������ ���� : 1. ���� �� ���� �浹 2. �ʰ� ���� �浹 
	//p1�� ���� �ݺ��� : ���� �Ӹ��� ���볢���� �浹 �˻� 
	for (p1 = snake_head; p1 != snake_tail;)
	{
		if (front.x == p1->x && front.y == p1->y)
		{
			lose = 1;
			break;
		}
		if (p1->next == snake_tail)
			temp = p1;
		p1 = p1->next;

	}

	// p2�� ���� �ݺ���: �� ���� ���� �浹 �˻�
	for (p2 = block_head;p2 != NULL;) 
	{
		if (front.x == p2->x && front.y == p2->y)
		{
			lose = 1;
			break;
		}
		p2 = p2->next;
	}

	return lose;
}

SNAKE* Add_Snake(SNAKE front,SNAKE * snake_head)
{
	temp = (SNAKE *)malloc(sizeof(SNAKE));
	if (temp == NULL)
	{
		printf("Failed to allocate memory!\n");
		exit(1);
	}
	*temp = front;
	temp->next = snake_head;
	snake_head = temp;
	Go_print(snake_head->x, snake_head->y, "o");

	return snake_head;
}

SNAKE* Check_get_Food(SNAKE front,SNAKE * snake_head)
{

	if ((front.x == food.x && front.y == food.y) || (front.x == bonus_food.x && front.y == bonus_food.y))
	{

		snake_head = Add_Snake(front,snake_head);

		if (front.x == bonus_food.x) 
		{
			score += bonus_score / 2 * level;
			bonus_food.x = -1, bonus_food.y = -1, bonus_score = 100;
			Notice_bonus();
		}
		else
		{
			bonus++;
			score += level;
			Food_create();
		}
	}
	else
	{
		Remove_Snake(snake_tail);

		snake_tail->next = snake_head;
		snake_head = snake_tail;
		snake_tail = temp;
		snake_tail->next = NULL;
		snake_head->x = front.x;
		snake_head->y = front.y;

		Go_print(snake_head->x, snake_head->y, "o");
	}
	return snake_head;
}


void Snake_move(void)
{
	switch (direction) 
	{
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
	default:
		break;
	}
	
	front = check_stage_collision(front);

	lose = Check_Gameover(snake_head);
	if (lose == 1)
		return;

	snake_head = Check_get_Food(front, snake_head);
}

void Snake_free(void)
{
	SNAKE *p1, *p2;
	for (p1 = snake_head, p2 = p1; p1 != NULL; p2 = p1) {
		p1 = p1->next;
		free(p2);
	}
}
