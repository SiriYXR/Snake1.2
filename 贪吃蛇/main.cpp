//===============================
//程序名称：贪吃蛇
//制作人：杨新瑞
//创建时间：2016.12.22
//上次修改时间：2017.2.11 20:53
//总制作天数：5
//===============================
#include"head.h"

//窗口尺寸
#define Win_L 654
#define Win_H 509

int main(void)
{
	char ch;

	ege::setinitmode(ege::INIT_ANIMATION);
	// 图形初始化
	ege::initgraph(Win_L, Win_H);
	// 随机数初始化，如果需要使用随机数的话
	ege::randomize();
	// 程序主循环
	
	if (!begin())
		mainloop();
	
	// 关闭绘图设备
	ege::closegraph();
	return 0;
}

//启始界面
int begin()
{
	//音效
	mciSendString(TEXT("open SWITCH.WAV alias SWITCH"), NULL, 0, NULL);
	char ch;
	int x, y;
	x = 200;
	y = 1;

	while (is_run())
	{
		//清屏
		cleardevice();

		setcolor(EGERGB(0x40, 0xE0, 0xD0));

		//方框
		setfillcolor(EGERGB(0xEE, 0x79, 0x42));
		bar(260, x, 370, 250);

		//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
		setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

		//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
		//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
		setfont(48, 0, "宋体");

		//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
		//要使用特殊格式化字符请用outtextrect
		//设置文字背景填充方式为透明，默认为OPAQUE不透明
		setbkmode(TRANSPARENT);
		outtextxy(240, 100, "贪吃蛇");
		outtextxy(270, 200, "开始");
		outtextxy(270, 250, "退出");

		ch = getch();
		if (ch == 27 || (x == 300 && (ch == 13 || ch == 32)))
		{
			mciSendString(TEXT("close SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("open SWITCH.WAV alias SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITCH"), NULL, 0, NULL);
			Sleep(200);
			return 1;
		}
		else if (x == 200 && (ch == 13 || ch == 32))
		{
			mciSendString(TEXT("close SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("open SWITCH.WAV alias SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITCH"), NULL, 0, NULL);
			return 0;
		}
		else if (ch == 's'&&y == 1)
		{
			y = 2;
			x = 300;
		}
		else if (ch == 'w'&&y == 2)
		{
			y = 1;
			x = 200;
		}

	}
}