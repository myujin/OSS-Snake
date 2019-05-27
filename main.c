#include <stdio.h>
#include<stdlib.h>
#include "goprint.h"
#include "map.h"
#include "snake.h"
#include "food.h"
#include "interface.h"
#pragma warning(disable:4996)

int main()
{
    while(1)
    {
        welcome();
		removeCursor();
        tips();
        map_boundary(map_size);
        snake_create();
        food_create();
        _getch();
        snake_control();
        snake_free();
        if(block_head != NULL)
            block_free();
        quit();
    }
    return 0;
}
