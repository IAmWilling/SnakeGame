/*
	graphics ͼ�ν����
	mmstream.h  windows�����ý���йصĴ�����ӿ�	�������Ҫ���ϱ�������
	#pragma comment(lib,"winmm.lib")  ������Ķ�ý��ͷ�ļ����ʹ��
	ctime ��Ҫ����������� time(0)
	cstdlib ��Ҫ�����������rand()
	conio   ���ڻ�ȡ����ASCII ���� _getch ��ȡ���̰��� _kbhit() ����Ƿ���ĳ�������򷵻�0
*/
#include <graphics.h>		//ͼ�ο�
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
	//��ʼ���������
	srand((unsigned int)time(NULL));
	//��ʼ�������һ�����ؾ���,����ʹ������ϵȥ��ʾ��
	InitSnake();
	/*
		�ı䷽��.����֮��
		����֮ǰ�����ڼ����ƶ��ͻ�ͼ
	*/
	 char buffer[100];
	while (1)
	{
		while (!_kbhit())		//����Ƿ���ĳ���� û�а��¾ͷ���0
		{
			if (food.flag==0)
			{
				CoorFood();
			}
		
			cleardevice();		//����ػ�
			if (isCrash())		//�����ײ��
			{
				
				NUM = 0;	//��ʾײǽ ÿ���ƶ��Ĳ���10 ���0 ������
				
			}
			if (NUM != 0)		//
			{
				rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
				settextstyle(30, 0, TEXT("΢���ź�"));
				outtextxy(WINDOW_WIDTH + ((WINDOW_WIDTH + 200) - WINDOW_WIDTH) / 2 - 30, 50, TEXT("̰����"));
				settextstyle(25, 0, TEXT("΢���ź�"));
				settextcolor(YELLOW);
				outtextxy(WINDOW_WIDTH + ((WINDOW_WIDTH + 200) - WINDOW_WIDTH) / 2 - 60, 80, TEXT("����:"));
				settextstyle(60, 0, TEXT("΢���ź�"));
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
		ChangeSnakeCh();	//���º�ִ�з���ı亯��
		
	}
	settextstyle(65, 0, TEXT("����"));
	outtextxy((WINDOW_WIDTH + 200) / 2 - 120, WINDOW_HEIGHT / 2 - 50, TEXT("�����!"));
	settextstyle(33, 0, TEXT("����"));
	settextcolor(YELLOW);
	outtextxy((WINDOW_WIDTH + 200) / 2 - 120, WINDOW_HEIGHT / 2 + 20, TEXT("����:"));
	outtextxy((WINDOW_WIDTH + 200) / 2 , WINDOW_HEIGHT / 2 + 20, LPCTSTR(buffer));

	//settextcolor(RED);
	//settextstyle(50,0,L"΢���ź�");		//��������ķ��:1.��С(��,�� =0 -> Ĭ��ƥ������ĸ�) 2.����

	//outtextxy(200, 240, L"Hello World");		//�ڴ����и���ָ������������ı�
	//rectangle(0,0,10,10);		//���(0,0), �յ�(10,10)���ƾ���
	//circle(320,240,100);		//����Բ�� Բ��x,Բ��y,�뾶r
	while (1);
	return 0;
}
//��ʼ����
void InitSnake()
{
	//��ʼ������
	initgraph(WINDOW_WIDTH + 200, WINDOW_HEIGHT);	//����һ��ͼ�ν���(��,��)
	setbkcolor(BLUE);		//���ñ�����ɫ����
	cleardevice();		//ʹ�����úõı�����ɫ(Ĭ��Ϊ��ɫ)ˢ����Ļ
	//��ʼ������
	//PlaySound();	//ֻ�ܲ���wav��ʽ������
	//��(open)���׸���������������(alias)
	mciSendString(TEXT("open PP.mp3 alias BGM"), 0, 0, 0);	//��ײ���������������ַ�����Ϣ
	//��֮��play����
	mciSendString(TEXT("play BGM"), 0, 0, 0);
	//��ʼ����
	snake.n = 3;		//��ʼ����ǰ����1
	snake.ch = right;		//��ʼ����������
	snake.szb[3].x = 50;		//��ǰ������X����
	snake.szb[3].y = 0;		//��ǰ������Y����
	snake.szb[2].x = 40;
	snake.szb[2].y = 0;
	snake.szb[1].x = 30;
	snake.szb[1].y = 0;
	snake.szb[0].x = 20;
	snake.szb[0].y = 0;
}
//������ n��
void DrawSnake(int size)		//size ��С,num��ʼ�����ٽ�
{
	
	//snake.szb[0].x + 10, snake.szb[0].y + 10 ��ʾ���Ƴ���10,���10��һ�������߽�
	//fillrectangle(snake.szb[0].x, snake.szb[0].y, snake.szb[0].x + size, snake.szb[0].y + size);
	for (int i =0; i  < snake.n ; i++)
	{
		if (i == 0)
		{
			setfillcolor(YELLOW);		//�����ɫ
		}
		else {
			setfillcolor(RED);		//�����ɫ
		}
		fillrectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + size, snake.szb[i].y + size);
	}
}
//�ߵ��ƶ�
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
	case up:	//����������
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
//�õ�ʳ�������
void CoorFood()
{
	food.fzb.x = (rand() % WINDOW_WIDTH / 10) * 10; // 0 1 2 3 4 .. 639
	food.fzb.y = (rand() % WINDOW_HEIGHT / 10) * 10;	// 0 1 2 3 ... 479;
	//�ߵ�������10 20 30 40 �й��ɵ� 10�ı���
	food.flag = 1;	//û�гԵ� 1 �������
}
void DrawFood()
{
	setfillcolor(GREEN);
	//����Բ��ʳ��
	
	fillroundrect(food.fzb.x, food.fzb.y, food.fzb.x + 10, food.fzb.y + 10,10,10);
}
void EatFood()
{
	//ֻҪʳ�����ͷ�غ� ����Ե�
	if (snake.szb[0].x == food.fzb.x && snake.szb[0].y == food.fzb.y)
	{
		snake.n++;
		FenShu++;
		food.flag = 0;
	}
}
bool isCrash()	//�Ƿ���ײ 
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
//˵��,�÷ֽ�������

