#include <stdio.h>
#include<stdlib.h>
#include "goprint.h"
#include "map.h"
#include "snake.h"
#include "food.h"
#include "interface.h"
#pragma warning(disable:4996)

/*
  ***SNAKE GAME***

  원본 소스코드 개발자: SnakeSkinMan
  원본 개발자 깃허브 주소 : https://github.com/SnakeSkinMan
  소스코드 개발 : myujin,4z7l
  프로그램 목표: 소스코드를 가독성 등의 측면에서 기존의 소스코드보다 개선시키는 것
  이 프로젝트는 MIT 라이선스를 따릅니다.

  [English version]
  original source code developer : SnakeSkinMan
  original developer github address: https://github.com/SnakeSkinMan
  Clone & improve : myujin,4z7l
  goal of the program : improve original source code 
  Released under the MIT license
 */

int main()
{
	while (1)
	{
		Welcome();
		RemoveCursor();
		Tips();

		Map_boundary(map_size);
		Snake_create();
		Food_create();

		//자동으로 게임이 시작하는 것을 방지하는 역할
		_getch();

		Snake_control();

		Snake_free();
		if (block_head != NULL)
			Block_free();
		Quit();
	}
	return 0;
}