#undef UNICODE
#undef _UNICODE
#include <graphics.h>
#include <iostream>		
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include<Windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm")
using namespace std;

DWORD slowtime, StartTime, EndTime;	//减速持续时间、游戏开始时刻、游戏此时时刻

struct pos	//坐标结构体
{
	int x, y;
	bool operator==(const pos& W) const	//重载判断等号运算符
	{
		return x == W.x && y == W.y;
	}
}Food, Ice, slowdown, cut;	//用这个结构体创建几个对象

const int MAXLEN = 1000;
const int WIDTH = 99;
const int HEIGHT = 36;
const int width = 800;
const int height = 600;
enum Direction { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77 };

class Snake
{
protected:
	Direction direction;
public:
	Snake(pos Pos);
	~Snake();
	void ChangeDirection(char op);
	void PrintSnake(int flag, Snake& snake);
	void PrintFood(const Snake& snake);
	void Printice(const Snake& snake);	//冰冻道具
	void Printslowdown(const Snake& snake);	//减速道具
	void Printcut(const Snake& snake);	//缩短道具
	int IsDead(const Snake& snake);	//判断是否死亡
	bool SpeedUp;
	int length;
	int state;	//state == 1指冰冻 state == 2 指减速 state == 0指无减益效果
	pos Node[MAXLEN];	//Node[0]为蛇头
	pos tail;
};

void gotoxy(short x, short y)
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void CreateMap()
{
	system("mode con cols=102 lines=38");
	for (int i = 0; i < WIDTH; i += 2)
	{
		gotoxy(i, 0);
		cout << "◆";
		gotoxy(i, HEIGHT - 1);
		cout << "◆";
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << "◆";
		gotoxy(WIDTH + 1, i);
		cout << "◆";
	}
	gotoxy(0, HEIGHT);
	StartTime = GetTickCount();
}

void InitGame()
{
	initgraph(width, height);
	MOUSEMSG msg;
	setbkcolor(RGB(30, 30, 30));
	cleardevice();

	settextstyle(46, 28, "楷体");
	settextcolor(RGB(78, 201, 176));
	outtextxy(290, 140, "开始游戏");
	setlinecolor(RGB(181, 206, 168));
	rectangle(280, 130, 520, 195);

	settextstyle(24, 12, "楷体");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 240, "游戏规则：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(260, 270, "玩家一：玩家一  控制：4个光标键");
	outtextxy(260, 300, "玩家二：玩家二  控制：W A S D");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 340, "胜利条件：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(280, 340,  "1.对方触碰边界");
	outtextxy(280, 370, "2.对方触碰对方身体");
	outtextxy(280, 400, "3.对方触碰己方身体");
	outtextxy(270, 430, "注： 头碰头是平局 ！！！");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 460, "图案说明：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(140, 490, " 1. ◆代表地图边界，■代表玩家一，□代表玩家二");
	outtextxy(140, 520, " 2. ●代表食物，※代表冰冻，▲代表减速，★代表缩短");


	settextstyle(46, 28, "楷体");
	while (1)
	{
		msg = GetMouseMsg();
		int x = msg.x;		//rectangle(280,130,520,195);		长 240 宽 65
		int y = msg.y;

		if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65 && msg.mkLButton) break;
		else if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65)
		{
			settextcolor(RGB(78, 201, 176)); 
			outtextxy(290, 140, "开始游戏");
		}
		else
		{
			settextcolor(RGB(255, 255, 255));
			outtextxy(290, 140, "开始游戏");
		}
	}
	closegraph();
	CreateMap();
}

void QuitGame()
{
	system("cls");
	exit(0);
}
void Welcome()
{
	mciSendString(TEXT("open bgm.mp3"), 0, 0, 0);	//播放音乐
	mciSendString(TEXT("play bgm.mp3 repeat"), 0, 0, 0);//重复播放
	gotoxy(WIDTH / 3 + 2, HEIGHT / 3);
	cout << "Welcome to Greedy Snake Battle";
	gotoxy(WIDTH / 3 - 4, HEIGHT * 3 / 5 - 1);
	cout << "Please choose a number ranged from 1 or 2";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 3 / 5 + 2);
	cout << "1.START GAME";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 3 / 5 + 4);
	cout << "2.QUIT GAME";
	gotoxy(0, 0);
A:
	char op = _getch();
	if (op == '1') InitGame();
	else if (op == '2') QuitGame();
	else
	{
		MessageBox(nullptr, "请重新输入！", "输入错误！", MB_OK);
		goto A;
	}
}
Snake::Snake(pos Pos)
{
	length = 5;
	Node[0] = Pos;
	tail = Pos;
	state = 0;
	for (int i = 1; i < length; i++)
	{
		Node[i].x = Node[i - 1].x - 2;
		Node[i].y = Node[i - 1].y;
	}
	direction = RIGHT;
	SpeedUp = false;
}
Snake::~Snake() {}
void Snake::ChangeDirection(char op)
{
	switch (op)
	{
	case 'w': case 'W': case 72:
		if (direction == DOWN) break;
		else direction = UP;
		break;
	case 's': case 'S': case 80:
		if (direction == UP) break;
		direction = DOWN;
		break;
	case 'a': case 'A': case 75:
		if (direction == RIGHT) break;
		direction = LEFT;
		break;
	case 'd': case 'D': case 77:
		if (direction == LEFT) break;
		direction = RIGHT;
		break;
	default:
		break;
	}
}

void Snake::PrintSnake(int flag, Snake& snake)
{
	tail.x = Node[length - 1].x;
	tail.y = Node[length - 1].y;

	for (int i = length - 1; i > 0; i--)
	{
		Node[i] = Node[i - 1];
	}
	switch (direction)
	{
	case UP: Node[0].y--; break;
	case DOWN: Node[0].y++; break;
	case LEFT:Node[0].x -= 2; break;
	case RIGHT: Node[0].x += 2; break;
	}

	gotoxy(tail.x, tail.y);
	cout << "  ";
	for (int i = 0; i < length; i++)
	{
		gotoxy(Node[i].x, Node[i].y);
		if (flag == 1) cout << "■";
		else if (flag == 2) cout << "□";
	}
	gotoxy(0, HEIGHT);

	if (Node[0].x == Food.x && Node[0].y == Food.y)//吃到食物
	{
		length++;
		Node[length - 1].x = tail.x;
		Node[length - 1].y = tail.y;
		PrintFood(snake);
	}

	if (Node[0].x == Ice.x && Node[0].y == Ice.y)//吃到冰冻
	{
		Ice.x = 0; Ice.y = 0;
		snake.state = 1;
		int type = rand() % 3;
		if (type == 0) Printice(snake);
		else if (type == 1)Printslowdown(snake);
		else Printcut(snake);
	}
	if (Node[0].x == slowdown.x && Node[0].y == slowdown.y)//吃到减速
	{
		slowdown.x = 0; slowdown.y = 0;
		slowtime = GetTickCount();
		snake.state = 2;
		int type = rand() % 3;
		if (type == 0)Printice(snake);
		else if (type == 1)Printice(snake);
		else Printcut(snake);
	}
	if (Node[0].x == cut.x && Node[0].y == cut.y)//吃到缩短
	{
		cut.x = 0; cut.y = 0;
		if (snake.length >= 4)
		{
			snake.tail.x = snake.Node[snake.length - 2].x;
			snake.tail.y = snake.Node[snake.length - 2].y;

			gotoxy(snake.Node[snake.length - 1].x, snake.Node[snake.length - 1].y);
			cout << "  ";
			gotoxy(0, HEIGHT);
			snake.length --;
		}
		int type = rand() % 3;
		if (type == 0)Printice(snake);
		else if (type == 1)Printslowdown(snake);
		else Printcut(snake);
	}
}

void Snake::PrintFood(const Snake& snake)
{
	while (1)
	{
		int i = 0, j = 0, x = 0, y = 0;
		Food.x = rand() % (WIDTH-2);
		Food.y = rand() % (HEIGHT-2);
		if (Food.x <= 2 || Food.y <= 1 || Food.x >= WIDTH || Food.y >= HEIGHT || Food.x % 2 == 1) continue;
		if (Food == Ice || Food == slowdown||Food==cut)continue;
		for (i = 0; i < length; i++)
		{
			if (Food.x == Node[i].x && Food.y == Node[i].y) break;
		}
		for (j = 0; j < snake.length; j++)
		{
			if (Food.x == snake.Node[j].x && Food.y == snake.Node[j].y) break;
		}
		if (i == length && j == snake.length)
		{
			gotoxy(Food.x, Food.y);
			cout << "●";
			gotoxy(0, HEIGHT);
			break;
		}
	}
}
void Snake::Printice(const Snake& snake)
{
	while (1)
	{
		int i = 0, j = 0, x = 0, y = 0;
		Ice.x = rand() % (WIDTH-2);
		Ice.y = rand() % (HEIGHT-2);
		if (Ice.x <= 2 || Ice.y <= 1 || Ice.x >= WIDTH || Ice.y >= HEIGHT || Ice.x % 2 == 1) continue;
		if (Ice == slowdown || Ice == Food||Ice==cut)continue;
		for (i = 0; i < length; i++)
		{
			if (Ice.x == Node[i].x && Ice.y == Node[i].y) break;
		}
		for (j = 0; j < snake.length; j++)
		{
			if (Ice.x == snake.Node[j].x && Ice.y == snake.Node[j].y) break;
		}
		if (i == length && j == snake.length)
		{
			gotoxy(Ice.x, Ice.y);
			cout << "※";
			gotoxy(0, HEIGHT);
			break; 
		}
	}
}
void Snake::Printslowdown(const Snake& snake)
{
	while (1)
	{
		int i = 0, j = 0, x = 0, y = 0;
		slowdown.x = rand() % (WIDTH-2);
		slowdown.y = rand() % (HEIGHT-2);
		if (slowdown.x <= 2 || slowdown.y <= 1 || slowdown.x >= WIDTH || slowdown.y >= HEIGHT || slowdown.x % 2 == 1) continue;
		if (slowdown == Food || slowdown == Ice||slowdown==cut)continue;
		for (i = 0; i < length; i++)
		{
			if (slowdown.x == Node[i].x && slowdown.y == Node[i].y) break;
		}
		for (j = 0; j < snake.length; j++)
		{
			if (slowdown.x == snake.Node[j].x && slowdown.y == snake.Node[j].y) break;
		}
		if (i == length && j == snake.length)
		{
			gotoxy(slowdown.x, slowdown.y);
			cout << "▲";
			gotoxy(0, HEIGHT);
			break;
		}
	}
}

void Snake::Printcut(const Snake& snake)
{
	while (1)
	{
		int i = 0, j = 0, x = 0, y = 0;
		cut.x = rand() % (WIDTH-2);
		cut.y = rand() % (HEIGHT-2);
		if (cut.x <= 2 || cut.y <= 1 || cut.x >= WIDTH || cut.y >= HEIGHT || cut.x % 2 == 1) continue;
		if (cut == Food || cut == Ice||cut==slowdown)continue;
		for (i = 0; i < length; i++)
		{
			if (cut.x == Node[i].x && cut.y == Node[i].y) break;
		}
		for (j = 0; j < snake.length; j++)
		{
			if (cut.x == snake.Node[j].x && cut.y == snake.Node[j].y) break;
		}
		if (i == length && j == snake.length)
		{
			gotoxy(cut.x, cut.y);
			cout << "★";
			gotoxy(0, HEIGHT);
			break;
		}
	}
}
int Snake::IsDead(const Snake& snake)
{
	if (Node[0].x <= 0 || Node[0].y <= 0 || Node[0].x >= WIDTH || Node[0].y >= HEIGHT - 1) return 1;//出地图
	for (int i = 1; i < length; i++)//撞到自己
		if (Node[0].x == Node[i].x && Node[0].y == Node[i].y) return 1;
	for (int i = 1; i < snake.length; i++)//撞到对方
		if (Node[0].x == snake.Node[i].x && Node[0].y == snake.Node[i].y) return 1;
	if (Node[0] == snake.Node[0]) return 2;
	return 0;
}

int main()
{
	system("mode con cols=100 lines=36");
	Welcome();
	srand((unsigned)time(NULL));
	int x1, y1, x2, y2;
	x1 = WIDTH / 3 - 1, y1 = HEIGHT / 3;
	x2 = WIDTH * 2 / 3, y2 = HEIGHT * 2 / 3;
	pos Pos1 = { x1, y1 }, Pos2 = { x2, y2 };
	Snake snake1(Pos1), snake2(Pos2);		//两条蛇
	snake1.PrintSnake(1, snake2);
	snake2.PrintSnake(2, snake1);
	snake1.PrintFood(snake2);
	int type = rand() % 3;
	if (type == 0) snake1.Printice(snake2);
	else if (type == 1)snake1.Printslowdown(snake2);
	else snake1.Printcut(snake2);

	DWORD t1 = GetTickCount(), t2 = GetTickCount(), tt1, tt2;	//判断是否可以移动
	while (true)
	{
		DWORD EndTime = GetTickCount();
		gotoxy(WIDTH / 2 - 6, HEIGHT);
		cout << "游戏时间（秒）：" << (EndTime - StartTime) / 1000;
		gotoxy(1, HEIGHT);
		cout << "玩家一得分：" << snake1.length * 100;
		gotoxy(WIDTH - 14, HEIGHT);
		cout << "玩家二得分：" << snake2.length * 100;
		gotoxy(0, HEIGHT);
		if (_kbhit())
		{
			char op = _getch();
			if (op == 'w' || op == 'W' || op == 'a' || op == 'A' || op == 's' || op == 'S' || op == 'd' || op == 'D')
				snake1.ChangeDirection(op);
			if (op == 72 || op == 75 || op == 77 || op == 80)
				snake2.ChangeDirection(op);
			if (op == ' ') snake1.SpeedUp = !snake1.SpeedUp;	//改变加速状态
			if (op == '0') snake2.SpeedUp = !snake2.SpeedUp;
		}

		tt1 = GetTickCount();
		//两种速度下分别的打印间隔时间
		if (snake1.state == 0 && tt1 - t1 > (snake1.SpeedUp == true ? 60 : 120)){
			//打印蛇
			snake1.PrintSnake(1, snake2);
			//更新时间
			t1 = tt1;
		}
		//判断冰冻， 冰冻持续时间为1.5秒， 1.5秒后打印这条蛇
		else if (snake1.state == 1 && tt1 - t1 > 1500) {
			//打印蛇
			snake1.PrintSnake(1, snake2);
			//更新时间
			t1 = tt1;
			//恢复正常状态
			snake1.state = 0;
		}
		//判断减速， 减速就每隔0.3秒打印这条蛇， 且持续时间不超过1.5秒
		//slowtime 每次吃到减速就获取当前时间
		else if (snake1.state == 2 && tt1 - t1 > 300) {
			//打印蛇
			snake1.PrintSnake(1, snake2);
			if (tt1 - slowtime > 1500) {
				snake1.state = 0;
			}
			//更新时间
			t1 = tt1;
		}


		tt2 = GetTickCount();
		//两种速度下分别的打印间隔时间
		if (snake2.state == 0 && (tt2 - t2 > (snake2.SpeedUp == true ? 60 : 120))){
			//打印蛇
			snake2.PrintSnake(2, snake1);
			//更新时间
			t2 = tt2;
		}
		//判断冰冻， 冰冻持续时间为1.5秒， 1.5秒后打印这条蛇
		else if (snake2.state == 1 && tt2 - t2 > 1500) {
			//打印蛇
			snake2.PrintSnake(2, snake1);
			//更新时间
			t2 = tt2;
			//恢复正常状态
			snake2.state = 0;
		}
			//判断减速， 减速就每隔0.3秒打印这条蛇， 且持续时间不超过1.5秒
			//slowtime 每次吃到减速就获取当前时间
		else if (snake2.state == 2 && tt2 - t2 >  300){
			//打印蛇
			snake2.PrintSnake(2, snake1);
			if (tt2 - slowtime > 1500) {
				snake2.state = 0;
			}
			//更新时间
			t2 = tt2;
		}
		//判断减速时间 大于1.5秒就恢复正常状态
		//if (tt2 - slowtime > 1500 && snake2.state == 2) snake2.state = 0;

		if (snake1.IsDead(snake2) == 1)
		{
			MessageBox(nullptr, "玩家二获胜", "游戏结束", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
		if (snake2.IsDead(snake1) == 1)
		{
			MessageBox(nullptr, "玩家一获胜", "游戏结束", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
		if (snake1.IsDead(snake2) == 2)
		{
			MessageBox(nullptr, "平局", "游戏结束", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
	}
	main();
	return 0;
}