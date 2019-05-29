#include "food.h"

extern SNAKE *snake_head;
extern BLOCK *block_head;
//extern int map_size;
FOOD food = {0, 0}, bonus_food = {-1, -1};
//int bonus = 0, bonus_score;

int check_Food_collision()
{
	SNAKE *p1;
	BLOCK *p2;
	int sign = 0;

	for (p1 = snake_head, p2 = block_head; p1 != NULL || p2 != NULL;) {

		if (p1 != NULL) {
			if ((food.x == p1->x && food.y == p1->y) || (bonus_food.x == p1->x && bonus_food.y == p1->y)) {
				sign = 1;
				break;
			}
			p1 = p1->next;
		}
		if (p2 != NULL) {
			if ((food.x == p2->x && food.y == p2->y) || (bonus_food.x == p2->x && bonus_food.y == p2->y)) {
				sign = 1;
				break;
			}
			p2 = p2->next;
		}
	}
	return sign;
}

void food_create(gameData data)
{
    int sign = 1;

    do{
        srand(time(NULL));
        food.x = rand() % data.map_size;
        food.y = rand() % data.map_size;

        if(bonus == 5){ 
            bonus_food.x = rand() % data.map_size;
            bonus_food.y = rand() % data.map_size;
        }

        if(bonus_food.x == food.x && bonus_food.y == food.y)
            continue;
		if (food.x == 0 || food.y == 0 || bonus_food.x == 0 || bonus_food.y == 0)
			continue;

		//�� �ڵ��� ��ġ�� ���� �ٸ� ���װ� �߻���.. ���ǹ��� ���� sign �������� ���� �ٸ��� �ۼ����־�� �� �� ���� 
		//if (sign)
		//	sign = 0;
		sign = 0;
		//������ �����Ǵ� ������ ���� ���ο� ������ �����Ǿ������� üũ�ϴ� �Լ�
		//snake.c�� ���� ȹ���Լ��ʹ� �ٸ� �����!!!! 
		sign = check_Food_collision();

		
    }while(sign);

    goprint(food.x, food.y, "��");
    if(bonus == 5)
        goprint(bonus_food.x, bonus_food.y, "��");
    data=notice_bonus(data);
}
