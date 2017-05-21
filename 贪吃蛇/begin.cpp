#include"head.h"

//启始界面
int begin()
{
	//音效
	mciSendString(TEXT("open data\\Music\\SWITkey.WAV alias SWITkey"), NULL, 0, NULL);//打开本地音频文件
	char key;
	int y, mark;
	y = 200;
	mark = 1;

	while (is_run())
	{
		//清屏
		cleardevice();

		setcolor(EGERGB(0x40, 0xE0, 0xD0));

		//方框
		setfillcolor(EGERGB(0xEE, 0x79, 0x42));
		bar(260, y, 370, 250);

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

		key = getch();
		if (key == 27 || (y == 300 && (key == 13 || key == 32)))
		{
			mciSendString(TEXT("seek SWITkey to 0"), NULL, 0, NULL);//调整播放进度
			mciSendString(TEXT("play SWITkey"), NULL, 0, NULL);//播放音频
			delay_ms(200);//延迟200毫秒
			return 1;
		}
		else if (y == 200 && (key == 13 || key == 32))
		{
			
			mciSendString(TEXT("seek SWITkey to 0"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITkey"), NULL, 0, NULL);
			return 0;
		}
		else if (key == 's'&&mark == 1)
		{
			mark = 2;
			y = 300;
		}
		else if (key == 'w'&&mark == 2)
		{
			mark = 1;
			y = 200;
		}
	}

	mciSendString(TEXT("close SWITkey"), NULL, 0, NULL);
}