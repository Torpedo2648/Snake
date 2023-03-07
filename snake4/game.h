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
	void Printice(const Snake& snake);	//冰冻道具
	void Printslowdown(const Snake& snake);	//减速道具
	void Printcut(const Snake& snake);	//缩短道具
	int IsDead(const Snake& snake);	//判断是否死亡
	int IsDead();
	bool SpeedUp;
	int length;
	int state;	//state == 1指冰冻 state == 2 指减速 state == 0指无减益效果
	pos Node[MAXLEN];	//Node[0]为蛇头
	pos tail;
};

void CreateMap();

void DoubleMode(char* name);

void SingleMode(char* name);

#endif