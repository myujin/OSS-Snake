#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/* This module offer the interface of the Snake game */

#include <stdio.h>
#include<stdlib.h>
#include "snake.h"
#include "goprint.h"

typedef struct gameData
{
	int margin, lose, level, map_size, bonus, bonus_score, score;
	char control, direction;
}gameData;

gameData set_GameData(gameData data);
gameData welcome(gameData data);
gameData notice_bonus(gameData data);

void tips(gameData data);
void quit(gameData data);
void progress_bar(gameData data);
void removeCursor(void);
void setConsoleSize(int w, int h);

#endif // INTERFACE_H_INCLUDED
