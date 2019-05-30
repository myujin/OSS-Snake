#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

/*

snake.h 파일은 snake game에서 핵심이라 할 수 있는 뱀의 몸 부분을 생성하고,
뱀의 움직임을 제어하는 기능을 제공하는 파일입니다. 

*/

#include <stdlib.h>
#include <conio.h>
#include "goprint.h"
#include "map.h"
#include "food.h"
#include "interface.h"

typedef struct SNAKE {
    int x;
    int y;
    struct SNAKE *next;
} SNAKE;

SNAKE *snake_head, *snake_tail;
extern char control, direction;
extern int lose, score, level;

SNAKE* check_get_Food(SNAKE front, SNAKE * snake_head);
int check_Gameover(SNAKE * snake_head);
void snake_create(void);
void snake_control(void);
void snake_move(void);
void snake_free(void);

#endif // SNAKE_H_INCLUDED
