#include"head.h"

void face(int length, int max);
void pause();

//死亡界面：1：撞墙；2：自食；3：新纪录
void death1(int length, int max);

void death2(int length, int max);

void death3(int length, int max);

//随机数
int myrand(int m)
{
	// randomf() 返回一个 0 到 1 之间的随机浮点数
	int i;
	i = (int)(randomf() * m) * 10 + 4;
	return i;
}

int myrand_num(int m)
{
	// randomf() 返回一个 0 到 1 之间的随机浮点数
	int i;
	i = (int)(randomf() * m);
	return i;
}


void mainloop()
{
	//音效
	//读取音频文件
	mciSendString(TEXT("open shengzhang.wav alias shengzhang"), NULL, 0, NULL);
	mciSendString(TEXT("open zhishi.wav alias zhishi"), NULL, 0, NULL);
	mciSendString(TEXT("open zhuangqiang.WAV alias zhuangqiang"), NULL, 0, NULL);
	mciSendString(TEXT("open shengli.mp3 alias shengli"), NULL, 0, NULL);

	FILE *fp;
	char key = 0, lmax[5];
	int  length, mid_direction[2], num1, num2, accelerate, max, speed, speed_max, *pt;
	int last_direction;
	int i, n, j, book[5], s_x[7] = { 260,250,240,230,220,210,200 };

	//读取最高记录
	fp = fopen("data\\Save\\length_max.txt", "r");
	if (fp == NULL)
		max = 3;//若打开失败则初始最高纪录为3
	else
	{
		fscanf(fp, "%d", &max);
		fclose(fp);
	}


	length = 3;//蛇长

	//使num1在0，1来回跳跃
	num1 = 0;
	num2 = -1;

	speed_max = 280;//最大速度
	accelerate = 0;//加速度


	//初始化方向
	dir direction[5] = { {0},{-10,0},{0,10},{10,0},{0,-10} };
	//声明食物
	food food;
	food.z = 0;

	//初始化蛇
	snak node, *head, *tail, *p, *t;
	head = NULL;
	for (i = 0; i < length; i++)
	{
		p = (snak *)malloc(sizeof(snak));
		p->direction = 3;
		p->x = s_x[i] + 4;
		p->y = 254;
		p->next = NULL;
		p->prev = NULL;
		if (head == NULL)
			head = p;
		else
		{
			tail->next = p;
			p->prev = tail;
		}
		tail = p;
	}
	
	for (; is_run(); delay_fps(60))
	{
		if (accelerate != 0)
			delay_ms(300 - speed_max);
		else
			delay_ms(300 - length);

		accelerate = 0;
		key = NULL;

		// todo: 逻辑更新

		//随机生成食物
		if (food.z == 0)
		{
			while (true)
			{
				i = 0;
				food.x = myrand(50);
				food.y = myrand(50);
				t = head;
				while (t != NULL)
				{
					if (t->x == food.x&&t->y == food.y)
						i = 1;
					t = t->next;
				}
				if (i == 0)
					break;
			}
			food.z = 1;
		}
		
		

		//人机交互
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			case 'w':
				if (head->direction == 4)
					accelerate = 1;
				if (head->direction != 2)
				{
					last_direction = head->direction;
					head->direction = 4;
				}
				break;
			case 's':
				if (head->direction == 2)
					accelerate = 1;
				if (head->direction != 4)
				{
					last_direction = head->direction;
					head->direction = 2;
					
				}
				break;
			case 'a':
				if (head->direction == 1)
					accelerate = 1;
				if (head->direction != 3)
				{
					last_direction = head->direction;
					head->direction = 1;
					
				}
				break;
			case 'd':
				if (head->direction == 3)
					accelerate = 1;
				if (head->direction != 1)
				{
					last_direction = head->direction;
					head->direction = 3;
					
				}
				break;
			case 32:
				pause();
				getch();
				key = NULL;
				break;
			default:
				break;
			}
		}

		/*int n = 0;
		t = head;
		while (t != NULL)
		{
			t->x += direction[t->direction].x;
			t->y += direction[t->direction].y;
			if (t->prev != NULL)
			{
				if (t->prev->direction != t->direction&&n==0)
				{
					last_direction =t->direction;
					t->direction = t->prev->direction;
					n = 1;
				}
				else if(t->prev->direction == t->direction)
					n = 0;
			}
			t = t->next;
		}*/
	
		t = head;
		t->x += direction[t->direction].x;
		t->y += direction[t->direction].y;
		mid_direction[num1] = t->direction;
		t = t->next;
		while (t != NULL)
		{
			num2 *= -1;
			num1 += num2;
			if (t->next != NULL)
			{
				t->x += direction[t->direction].x;
				t->y += direction[t->direction].y;
				mid_direction[num1] = t->direction;
				num2 *= -1;
				num1 += num2;
				t->direction = mid_direction[num1];
				num2 *= -1;
				num1 += num2;
				t = t->next;
			}
			else
			{
				num2 *= -1;
				num1 += num2;
				t->x += direction[t->direction].x;
				t->y += direction[t->direction].y;
				t->direction = mid_direction[num1];
				t = t->next;
			}
		}


		//蛇尾生长
		if (head->x == food.x&&head->y == food.y)
		{
			p = (snak *)malloc(sizeof(snak));
			p->direction = tail->direction;
			if (tail->direction == 1)
			{
				p->x = tail->x + 10;
				p->y = tail->y;
			}
			else if (tail->direction == 2)
			{
				p->x = tail->x;
				p->y = tail->y - 10;
			}
			else if (tail->direction == 3)
			{
				p->x = tail->x - 10;
				p->y = tail->y;
			}
			else if (tail->direction == 4)
			{
				p->x = tail->x;
				p->y = tail->y + 10;
			}
			p->next = NULL;
			p->prev = NULL;
			tail->next = p;
			p->prev = tail;
			tail = p;
			food.z = 0;
			length++;
			
			mciSendString(TEXT("seek shengzhang to 0"), NULL, 0, NULL);//使音乐被播放时从头开始
			mciSendString(TEXT("play shengzhang"), NULL, 0, NULL);//播放音乐
		}

		//自食死亡
		t = head;
		t = t->next;
		while (t != NULL)
		{

			if (head->x == t->x && head->y == t->y)
				head->x = 999;
			t = t->next;
		}

		//出界死亡
		if (head->x < 4 || head->x + 10>504 || head->y < 3 || head->y + 10>505)
		{
			if (max < length)
			{
				
				mciSendString(TEXT("seek shengli to 0"), NULL, 0, NULL);
				mciSendString(TEXT("play shengli"), NULL, 0, NULL);
				max = length;
				death3(length, max);
			}
			else if (head->x == 999)
			{
				
				mciSendString(TEXT("seek zhishi to 0"), NULL, 0, NULL);
				mciSendString(TEXT("play zhishi"), NULL, 0, NULL);
				death2(length, max);
			}
			else
			{
				mciSendString(TEXT("seek zhuangqiang to 0"), NULL, 0, NULL);
				mciSendString(TEXT("play zhuangqiang"), NULL, 0, NULL);
				death1(length, max);
			}
			delay_ms(2000);
			getkey();

			//存档
			fp = fopen("data\\Save\\length_max.txt", "w");
			fprintf(fp, "%d", max);
			fclose(fp);

			
			mciSendString(TEXT("seek SWITkey to 0"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITkey"), NULL, 0, NULL);
			break;
		}

		//ESC强制退出
		if (key == 27)
		{
			fp = fopen("length_max.txt", "w");
			fprintf(fp, "%d", max);
			fclose(fp);

			break;
		}


		// todo: 图形更新
		//清屏，重新在新的位置绘图图像
		cleardevice();
		//打印主界面
		face(length, max);
		//打印食物
		setfillcolor(WHITE);
		bar(food.x, food.y, food.x + 11, food.y + 11);
		//打印蛇
		t = head;
		while (t != NULL)
		{
			setfillcolor(EGERGB(0x00, 0xBF, 0xFF));
			bar(t->x, t->y, t->x + 11, t->y + 11);
			t = t->next;
		}
	}

	//关闭音频文件
	mciSendString(TEXT("close SWITkey"), NULL, 0, NULL);
	mciSendString(TEXT("close zhuangqiang"), NULL, 0, NULL);
	mciSendString(TEXT("close zhishi"), NULL, 0, NULL);
	mciSendString(TEXT("close shengli"), NULL, 0, NULL);
	mciSendString(TEXT("close shengzhang"), NULL, 0, NULL);
}

void face(int length, int max)
{
	// 设置填充颜色，一般为图形内部颜色
	setcolor(EGERGB(0, 0xFF, 0));
	setfillcolor(EGERGB(0xFF, 0x0, 0x80));

	//界面边框
	bar(0, 0, 654, 4);
	bar(505, 0, 509, 509);
	bar(0, 0, 4, 509);
	bar(0, 505, 654, 509);
	bar(651, 0, 654, 509);

	//文字颜色
	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(24, 0, "宋体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	outtextxy(545, 20, "贪吃蛇");
	setfont(22, 0, "宋体");
	char str[20];
	sprintf(str, "长度:%d", length);//将引号中的内容写入str字符串
	outtextxy(550, 60, str);
	sprintf(str, "历史记录:%d", max);
	outtextxy(515, 100, str);

}
void death1(int length, int max)
{
	//清屏
	cleardevice();

	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(48, 0, "宋体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	outtextxy(160, 100, "不撞南墙不回头！");
	setfont(32, 0, "宋体");
	char str1[20], str2[20];
	sprintf(str1, "最终长度:%d", length);
	outtextxy(220, 170, str1);
	sprintf(str2, "历史记录:%d", max);
	outtextxy(220, 220, str2);
}
void death2(int length, int max)
{
	int i;
	//清屏
	cleardevice();

	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(48, 0, "宋体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	i = myrand_num(2);
	switch (i)
	{
	case 1:
		outtextxy(75, 100, ">_<大哥，那个不是豆子!");
		break;
	default:
		outtextxy(120, 100, "天呐，你吃了自己！");
		break;
	}


	setfont(32, 0, "宋体");
	char str[20];
	sprintf(str, "最终长度:%d", length);
	outtextxy(220, 170, str);
	sprintf(str, "历史记录:%d", max);
	outtextxy(220, 220, str);
}
void death3(int length, int max)
{
	//清屏
	cleardevice();

	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(48, 0, "宋体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	outtextxy(120, 120, "恭喜你创造了新纪录！");
	setfont(40, 0, "宋体");
	char str[20];
	sprintf(str, "最高记录:%d", max);
	outtextxy(220, 200, str);
}

//暂停
void pause()
{
	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(48, 0, "宋体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	outtextxy(210, 120, "暂停");
	setfont(35, 0, "宋体");
	outtextxy(160, 180, "按任意键继续");
}
