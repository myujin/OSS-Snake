#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/* 

interface.h 파일은 게임을 플레이할 때
콘솔창에 출력되는 안내 메세지, 게임에 관한 정보 등등
사용자가 접하게 되는 출력 화면에 대한 기능을 다루는 헤더 파일입니다.

*/

#include <stdio.h>
#include "snake.h"
#include "goprint.h"

void Welcome(void);
void Tips(void);
void Notice_bonus(void);
void Quit(void);
void Progress_bar(void);
void RemoveCursor(void);
void SetConsoleSize(int w, int h);

#endif // INTERFACE_H_INCLUDED
