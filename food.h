#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

/*

Food.h ������ Snake-Game���� ������ ���� �� ��¿� ���� ����� ����ϴ� �����Դϴ�.

*/

#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "snake.h"
#include "interface.h"

typedef struct FOOD {
    int x;
    int y;
} FOOD;

extern int bonus, bonus_score;
extern FOOD food, bonus_food;

int Check_food_collision(void);
void Food_create(void);

#endif // FOOD_H_INCLUDED
