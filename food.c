#include "food.h"
#include "interface.h"

FOOD food = { 0,0 }, bonus_food = { -1,-1 };
int bonus = 0, bonus_score = 10;

int Check_food_collision(void)
{
	SNAKE *p1;
	BLOCK *p2;
	int sign = 0;

	for (p1 = snake_head; p1 != NULL;) 
	{
		if ((food.x == p1->x && food.y == p1->y) || (bonus_food.x == p1->x && bonus_food.y == p1->y))
		{
			sign = 1;
			break;
		}
		p1 = p1->next;	
	}

	for (p2 = block_head; p2 != NULL;) 
	{
		if ((food.x == p2->x && food.y == p2->y) || (bonus_food.x == p2->x && bonus_food.y == p2->y))
		{
			sign = 1;
			break;
		}
		p2 = p2->next;	
	}
	return sign;
}

void Food_create(void)
{
    int sign = 1;

    do{
        srand(time(NULL));
        food.x = rand() % map_size;
        food.y = rand() % map_size;

        if(bonus == 5)
		{ 
            bonus_food.x = rand() % map_size;
            bonus_food.y = rand() % map_size;
        }

        if(bonus_food.x == food.x && bonus_food.y == food.y)
            continue;
		if (food.x == 0 || food.y == 0 || bonus_food.x == 0 || bonus_food.y == 0)
			continue;

		sign = 0;
		//������ �����Ǵ� ������ ���� ���ο� ������ �����Ǿ������� üũ�ϴ� �Լ�
		//snake.c�� ���� ȹ���Լ��ʹ� �ٸ� �����!!!! 
		sign = Check_food_collision();

		
    }while(sign);

    Go_print(food.x, food.y, "��");

    if(bonus == 5)
        Go_print(bonus_food.x, bonus_food.y, "��");

    Notice_bonus();
}
