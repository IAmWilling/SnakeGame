#pragma once
#ifndef SNAKE_H_
#define SNAKE_H_
#define SNAKELENGTH 500
//利用枚举方向 ASCII
int NUM = 10;
int FenShu = 0;
enum Ch
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
};

//坐标
struct Coor {		// x y 坐标结构体
	int x;
	int y;
};
//蛇
struct Snake {		//蛇结构
	int n;	//当前的节数
	Coor szb[SNAKELENGTH];	//蛇坐标 最大长度是500
	Ch ch;	//蛇的方向
}snake;		//结构体变量

			
//食物
struct Food
{
	Coor fzb;	//食物的坐标 只有一个
	int flag;		//是否被吃的标志
}food;


void InitSnake();
void DrawSnake(int size);
void MoveSnake();
void ChangeSnakeCh();
void CoorFood();		//得到食物坐标
void DrawFood();			//绘制食物
void EatFood();		//吃掉食物
bool isCrash();	//是否碰撞

#endif // !SNAKE_H_

