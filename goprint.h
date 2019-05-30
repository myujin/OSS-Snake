#ifndef GOPRINT_H_INCLUDED
#define GOPRINT_H_INCLUDED

/* 

goprint.h 파일은 출력과 관련된 기능인 함수를 다루는 헤더파일입니다.

*/

#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y);
void goprint(int x, int y, const char *c);

#endif // GOPRINT_H_INCLUDED
