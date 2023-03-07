#pragma once

#ifndef __SNAKE__
#define __SNAKE__	
#include"menu.h"

class Snake
{
protected:
	Direction direction;
public:
	Snake(pos Pos);
	~Snake();
	void ChangeDirection(char op);
	void PrintSnake(int flag, Snake& snake);
	void PrintSnake();
	void PrintFood(const Snake& snake);
	void PrintFood();
	void Printice(const Snake& snake);	//��������
	void Printslowdown(const Snake& snake);	//���ٵ���
	void Printcut(const Snake& snake);	//���̵���
	int IsDead(const Snake& snake);	//�ж��Ƿ�����
	int IsDead();
	bool SpeedUp;
	int length;
	int state;	//state == 1ָ���� state == 2 ָ���� state == 0ָ�޼���Ч��
	pos Node[MAXLEN];	//Node[0]Ϊ��ͷ
	pos tail;
};

void CreateMap();

void DoubleMode(char* name);

void SingleMode(char* name);

#endif