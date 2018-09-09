#pragma once
#ifndef SNAKE_H_
#define SNAKE_H_
#define SNAKELENGTH 500
//����ö�ٷ��� ASCII
int NUM = 10;
int FenShu = 0;
enum Ch
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
};

//����
struct Coor {		// x y ����ṹ��
	int x;
	int y;
};
//��
struct Snake {		//�߽ṹ
	int n;	//��ǰ�Ľ���
	Coor szb[SNAKELENGTH];	//������ ��󳤶���500
	Ch ch;	//�ߵķ���
}snake;		//�ṹ�����

			
//ʳ��
struct Food
{
	Coor fzb;	//ʳ������� ֻ��һ��
	int flag;		//�Ƿ񱻳Եı�־
}food;


void InitSnake();
void DrawSnake(int size);
void MoveSnake();
void ChangeSnakeCh();
void CoorFood();		//�õ�ʳ������
void DrawFood();			//����ʳ��
void EatFood();		//�Ե�ʳ��
bool isCrash();	//�Ƿ���ײ

#endif // !SNAKE_H_

