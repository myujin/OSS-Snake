#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED


#include <stdlib.h>
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
int score, level;


//SNAKE* check_get_Food(SNAKE front, SNAKE * snake_head,gameData data);
int check_Gameover(SNAKE * snake_head);



#endif // SNAKE_H_INCLUDED
