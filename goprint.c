#include "goprint.h"

void Go_to_xy(int x, int y)                                  /* Go to the coordinate */
{
    COORD pos = {2 * x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void Go_print(int x, int y, const char *c)                  /* Print the char */
{
    Go_to_xy(x, y);
    printf("%s", c);
}
