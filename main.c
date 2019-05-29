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
	gameData data;
	data.lose = 0; data.level = 3; data.map_size = 30; data.bonus = 0;
	data.margin = data.map_size + 5; data.score = 0; data.bonus_score = 0;
	data.control = 'w'; data.direction = 'w';
	//data = set_GameData(data);

	while (1)
	{
		data=welcome(data);
		removeCursor();
		tips(data);
		map_boundary(data.map_size);
		snake_create(data);
		food_create(data);
		_getch();
		snake_control(data);
		snake_free();
		if (block_head != NULL)
			block_free();
		quit(data);
	}
	return 0;
}