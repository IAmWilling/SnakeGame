/*
	graphics 图形界面库
	mmstream.h  windows中与多媒体有关的大多数接口	如果你想要加上背景音乐
	#pragma comment(lib,"winmm.lib")  与上面的多媒体头文件配合使用
	ctime 主要掷随机数种子 time(0)
	cstdlib 主要用随机数函数rand()
	conio   用于获取按键ASCII 比如 _getch 获取键盘按键 _kbhit() 检测是否按下某个键无则返回0
*/
#include <graphics.h>		//图形库
#include <iostream>
#include "snake.h"
#include<mmsystem.h>

#include <ctime>
#include <cstdlib>
#include <conio.h>
#pragma comment(lib,"winmm.lib")
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main()
{
	//初始化随机种子
	srand((unsigned int)time(NULL));
	//初始化后会有一个像素矩阵,可以使用坐标系去表示它
	InitSnake();
	/*
		改变方向.按键之后
		按键之前程序在继续移动和绘图
	*/
	 char buffer[100];
	while (1)
	{
		while (!_kbhit())		//检测是否按下某个键 没有按下就返回0
		{
			if (food.flag==0)
			{
				CoorFood();
			}
		
			cleardevice();		//清除重绘
			if (isCrash())		//如果碰撞了
			{
				
				NUM = 0;	//表示撞墙 每次移动的步伐10 变成0 不走了
				
			}
			if (NUM != 0)		//
			{
				rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
				settextstyle(30, 0, TEXT("微软雅黑"));
				outtextxy(WINDOW_WIDTH + ((WINDOW_WIDTH + 200) - WINDOW_WIDTH) / 2 - 30, 50, TEXT("贪吃蛇"));
				settextstyle(25, 0, TEXT("微软雅黑"));
				settextcolor(YELLOW);
				outtextxy(WINDOW_WIDTH + ((WINDOW_WIDTH + 200) - WINDOW_WIDTH) / 2 - 60, 80, TEXT("分数:"));
				settextstyle(60, 0, TEXT("微软雅黑"));
				settextcolor(WHITE);
				_itoa_s(FenShu, buffer, _countof(buffer), 10);
				outtextxy(WINDOW_WIDTH + ((WINDOW_WIDTH + 200) - WINDOW_WIDTH) / 2 - 60, 120, LPCTSTR(buffer));
				MoveSnake();
				DrawFood();
				DrawSnake(10);
				EatFood();
				Sleep(100);
			}
			else {
				break;
			}
		}
		if (NUM == 0)
		{
			break;
		}
		ChangeSnakeCh();	//按下后执行方向改变函数
		
	}
	settextstyle(65, 0, TEXT("仿宋"));
	outtextxy((WINDOW_WIDTH + 200) / 2 - 120, WINDOW_HEIGHT / 2 - 50, TEXT("你挂了!"));
	settextstyle(33, 0, TEXT("仿宋"));
	settextcolor(YELLOW);
	outtextxy((WINDOW_WIDTH + 200) / 2 - 120, WINDOW_HEIGHT / 2 + 20, TEXT("分数:"));
	outtextxy((WINDOW_WIDTH + 200) / 2 , WINDOW_HEIGHT / 2 + 20, LPCTSTR(buffer));

	//settextcolor(RED);
	//settextstyle(50,0,L"微软雅黑");		//设置字体的风格:1.大小(高,宽 =0 -> 默认匹配字体的高) 2.字体

	//outtextxy(200, 240, L"Hello World");		//在窗口中根据指定的坐标输出文本
	//rectangle(0,0,10,10);		//起点(0,0), 终点(10,10)绘制矩形
	//circle(320,240,100);		//绘制圆形 圆心x,圆心y,半径r
	while (1);
	return 0;
}
//初始化蛇
void InitSnake()
{
	//初始化窗口
	initgraph(WINDOW_WIDTH + 200, WINDOW_HEIGHT);	//创建一个图形界面(宽,高)
	setbkcolor(BLUE);		//设置背景颜色函数
	cleardevice();		//使用设置好的背景颜色(默认为黑色)刷新屏幕
	//初始化音乐
	//PlaySound();	//只能播放wav格式的音乐
	//打开(open)这首歌曲给它重新命名(alias)
	mciSendString(TEXT("open PP.mp3 alias BGM"), 0, 0, 0);	//向底层的声卡驱动发送字符串消息
	//打开之后play调用
	mciSendString(TEXT("play BGM"), 0, 0, 0);
	//初始化蛇
	snake.n = 3;		//初始化当前节数1
	snake.ch = right;		//初始化方向向右
	snake.szb[3].x = 50;		//当前节数的X坐标
	snake.szb[3].y = 0;		//当前节数的Y坐标
	snake.szb[2].x = 40;
	snake.szb[2].y = 0;
	snake.szb[1].x = 30;
	snake.szb[1].y = 0;
	snake.szb[0].x = 20;
	snake.szb[0].y = 0;
}
//绘制蛇 n节
void DrawSnake(int size)		//size 大小,num初始化多少节
{
	
	//snake.szb[0].x + 10, snake.szb[0].y + 10 表示绘制长度10,宽度10的一个矩形蛇节
	//fillrectangle(snake.szb[0].x, snake.szb[0].y, snake.szb[0].x + size, snake.szb[0].y + size);
	for (int i =0; i  < snake.n ; i++)
	{
		if (i == 0)
		{
			setfillcolor(YELLOW);		//填充颜色
		}
		else {
			setfillcolor(RED);		//填充颜色
		}
		fillrectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + size, snake.szb[i].y + size);
	}
}
//蛇的移动
void MoveSnake()
{
	
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}
	
	switch (snake.ch)
	{
	case up:
		snake.szb[0].y -= NUM;
		break;
	case down:
		snake.szb[0].y += NUM;
		break;
	case right:
		snake.szb[0].x += NUM;
		break;
	case left:
		snake.szb[0].x -= NUM;
		break;
	}
}
void ChangeSnakeCh()
{
	int move = _getch();
	switch (move)
	{
	case up:	//不能向下走
		if(snake.ch!=down)
			snake.ch = up;
		break;
	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case right:
		if (snake.ch != left)
			snake.ch = right;
		break;
	case left:
		if (snake.ch != right)
			snake.ch = left;
		break;
	}


}
//得到食物的坐标
void CoorFood()
{
	food.fzb.x = (rand() % WINDOW_WIDTH / 10) * 10; // 0 1 2 3 4 .. 639
	food.fzb.y = (rand() % WINDOW_HEIGHT / 10) * 10;	// 0 1 2 3 ... 479;
	//蛇的坐标是10 20 30 40 有规律的 10的倍数
	food.flag = 1;	//没有吃掉 1 随机出现
}
void DrawFood()
{
	setfillcolor(GREEN);
	//绘制圆形食物
	
	fillroundrect(food.fzb.x, food.fzb.y, food.fzb.x + 10, food.fzb.y + 10,10,10);
}
void EatFood()
{
	//只要食物和蛇头重合 代表吃掉
	if (snake.szb[0].x == food.fzb.x && snake.szb[0].y == food.fzb.y)
	{
		snake.n++;
		FenShu++;
		food.flag = 0;
	}
}
bool isCrash()	//是否碰撞 
{
	// snake.szb[0].x >= WINDOW_WIDTH || snake.szb[0].y >= WINDOW_HEIGHT || snake.szb[0].y <= 0
	if (snake.szb[0].x < 0 || snake.szb[0].x >= WINDOW_WIDTH || snake.szb[0].y >= WINDOW_HEIGHT || snake.szb[0].y < 0)
	{
		return true;
	}
	if (FenShu > 1)
	{
		for (int i = 1; i < snake.n; i++)
		{
			if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y)
			{
				return true;
			}
		}
	}

	return false;
}
//说明,得分界面区域

