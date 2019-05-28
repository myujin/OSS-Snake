#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/* This module offer the interface of the Snake game */

#include <stdio.h>
#include "snake.h"
#include "goprint.h"

void welcome(void);
void tips(void);
void show_score(void);
void quit(void);
void progress_bar(void);
void removeCursor(void);
void setConsoleSize(int w, int h);

#endif // INTERFACE_H_INCLUDED
