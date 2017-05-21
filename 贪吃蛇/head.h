#include<stdlib.h>
#include<stdio.h>
#include<math.h>

//ege头文件
#include<ege.h>
#include <graphics.h>

//micSendString多媒体API头文件
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


//定义蛇主体链表
typedef struct LinkList
{
	int x;
	int	y;
	int direction;
	struct LinkList *next;
	struct LinkList *prev;
}snak;
//定义方向
typedef struct Direction
{
	int x;
	int y;
}dir;

//定义食物
typedef struct Food
{
	int x;
	int y;
	int z;
}food;

//游戏主循环
void mainloop();
int begin();
