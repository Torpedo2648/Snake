#ifndef __SNAKE__
#define __SNAKE__

#include<iostream>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#define framex 2
#define framey 2
#define wide 98
#define high 34
using namespace std;

static int tailx, taily;
static unsigned char ch = 80;

struct Snake
{
    int x[2000];
    int y[2000];
    int length;
};
struct Food
{
    int x, y;
};

void Welcome();
void Explanation();
void StartGame();
void CreateMap();
void gotoxy(short x, short y);
void InitSnake(Snake* snake);
void PrintSnake(Snake* snake);
void MoveSnake(char op, Snake* snake);
bool check(unsigned char ch, unsigned char op);
void PrintFood(Snake* snake, Food* food);
void EatFood(Snake* snake, Food* food);
bool IsDead(Snake* snake);

#endif