//===============================
//程序名称：贪吃蛇
//制作人：杨新瑞
//创建时间：2016.12.22
//上次修改时间：2017.2.11 20:53
//总制作天数：5
//
//更新日志：
//1.1：
//2017.5.18
//	优化记录储存读取代码，使用fprint(),fscanf()来读取存储数据
//	优化音乐播放代码,使用seek来初始化音频函数
//	添加必要注释
//
//1.2:
//2017.5.21
//	更新核心算法
//	改贪吃蛇链表为双向链表
//	将素材文件整理分类
//
//===============================
#include"head.h"

//窗口尺寸
#define Win_L 654
#define Win_H 509

int main(void)
{
	char ch;

	ege::setinitmode(ege::INIT_ANIMATION/*+ ege::INIT_WITHLOGO*/);
	// 图形初始化
	ege::initgraph(Win_L, Win_H);
	// 随机数初始化，如果需要使用随机数的话
	ege::randomize();
	// 程序主循环
	
	while (true)
	{
		if (begin())
			break;
		mainloop();
	}
	
	// 关闭绘图设备
	ege::closegraph();
	return 0;
}

