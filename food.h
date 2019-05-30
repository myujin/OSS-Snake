#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

/*

Food.h 파일은 Snake-Game에서 음식의 생성 및 출력에 대한 기능을 담당하는 파일입니다.

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

int Check_food_collision();
void Food_create(void);

#endif // FOOD_H_INCLUDED
