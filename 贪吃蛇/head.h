#include<stdlib.h>
#include<ege.h>
#include<math.h>
#include <graphics.h>
#include<stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


//定义蛇主体链表
typedef struct LinkList
{
	int x, y, direction;
	struct LinkList *next;
}snak;
//定义方向
typedef struct Direction
{
	int x, y;
}dir;
//定义食物
typedef struct Food
{
	int x, y,z;
}food;


void mainloop();
int begin();
