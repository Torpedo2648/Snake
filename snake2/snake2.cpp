#undef UNICODE
#undef _UNICODE
#include <iostream>		
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
//#include <mmsystem.h>
#include<Windows.h>
//#pragma comment (lib,"winmm")
using namespace std;

const int MAXLEN = 1000;
const int WIDTH = 99;
const int HEIGHT = 36;
const int width = 800;
const int height = 600;
struct pos { int x, y; }Food;
enum Direction { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77 };

class Snake
{
private:
	int length;
	pos Node[MAXLEN];	//Node[0]为蛇头
protected:
	Direction direction;
public:
	Snake(pos Pos);
	~Snake();
	void ChangeDirection(char op);
	void PrintSnake(int flag, Snake &snake);
	void PrintFood(const Snake &snake);
	bool IsDead(const Snake &snake);
	bool SpeedUp;
	pos tail = Node[0];
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
		gotoxy(WIDTH+1, i);
		cout << "◆";
	}
	gotoxy(0, HEIGHT);
}

void StartGame()
{
	initgraph(width, height);
	MOUSEMSG msg;

	//mciSendString("open music.mp3 alias huameng", 0, 0, 0);
	//mciSendString("play huameng repeat", 0, 0, 0);
	//loadimage(nullptr, "start_background.jpg", WIDTH, HEIGHT);

	setbkcolor(RGB(0, 128, 160));
	cleardevice();

	settextcolor(WHITE);
	settextstyle(46, 28, "楷体");
	outtextxy(290, 140, "开始游戏");
	setlinecolor(RGB(255, 255, 0));
	rectangle(280, 130, 520, 195);

	settextstyle(24, 12, "楷体");
	settextcolor(RGB(255, 255, 0));
	outtextxy(180, 240, "游 戏 规 则 :");
	outtextxy(260, 270, "玩家一：小红  控制：4个光标键");
	outtextxy(260, 300, "玩家二：小绿  控制：W A S D");
	outtextxy(180, 360, "胜利条件：1.对方触碰边界");
	outtextxy(280, 395, "2.对方触碰己方身体");
	outtextxy(280, 430, "3.吃满果实（100个） >> __ <<");
	outtextxy(270, 480, "注： 头碰头是平局 ！！！");

	settextstyle(46, 28, "楷体");
	while (1)
	{
		msg = GetMouseMsg();
		int x = msg.x;		//rectangle(280,130,520,195);		长 240 宽 65
		int y = msg.y;

		if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65 && msg.mkLButton)
			break;
		else if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65)
		{
			settextcolor(RGB(0, 255, 255));
			outtextxy(290, 140, "开始游戏");
		}
		else
		{
			settextcolor(RED);
			outtextxy(290, 140, "开始游戏");
		}
	}
	closegraph();
	CreateMap();
}

void QuitGame()
{
	exit(0);
}
void Welcome()
{
	gotoxy(WIDTH / 3 + 2, HEIGHT / 3);
	cout << "Welcome to Greedy Snake Battle";
	gotoxy(WIDTH / 3 - 4, HEIGHT * 3 / 5 - 1);
	cout << "Please choose a number ranged from 1 to 3";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 3 / 5 + 2);
	cout << "1.START GAME";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 3 / 5 + 4);
	cout << "2.QUIT GAME";
	gotoxy(0, 0);
A:
	char op = _getch();
	if (op == '1') StartGame();
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
	tail = Node[0] = Pos;
	for (int i = 1; i < length; i++)
	{
		Node[i].x = Node[i - 1].x - 2;
		Node[i].y = Node[i - 1].y;
	}
	direction = RIGHT;
	SpeedUp = false;
}
Snake::~Snake(){}
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

void Snake::PrintSnake(int flag, Snake &snake)
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
		else if(flag == 2) cout << "□";
	}
	gotoxy(0, HEIGHT);

	if (Node[0].x == Food.x && Node[0].y == Food.y)//吃到食物
	{
		length++;
		Node[length - 1].x = tail.x;
		Node[length - 1].y = tail.y;
		PrintFood(snake);
	}
}

void Snake::PrintFood(const Snake &snake)
{
	srand((unsigned)time(NULL));
	while (1)
	{
		int i = 0, j = 0, x = 0, y = 0;
		Food.x = rand() % ((WIDTH - 6) / 2);
		Food.y = rand() % (HEIGHT - 6);
		if (Food.x <= 2 || Food.y <= 1 || Food.x >= WIDTH || Food.y >= HEIGHT || Food.x % 2 == 1) continue;
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
			break;
		}
	}
}

bool Snake::IsDead(const Snake &snake)
{
	if (Node[0].x <= 0 || Node[0].y <= 0 || Node[0].x >= WIDTH || Node[0].y >= HEIGHT)
	{
		cout << Node[0].x << " " << Node[0].y;
		system("pause");
		return 1;//出地图
	}

	for (int i = 1; i < length; i++)//撞到自己
		if (Node[0].x == Node[i].x && Node[0].y == Node[i].y) return 1;
	for (int i = 1; i < snake.length; i++)//撞到对方
		if (Node[0].x == snake.Node[i].x && Node[0].y == snake.Node[i].y) return 1;
	return 0;
}

int main()
{
	system("mode con cols=100 lines=36");
	Welcome();
	DWORD t1 = GetTickCount(),t2 = GetTickCount(), tt1, tt2;//判断是否可以移动

	int x1, y1, x2, y2;
	x1 = WIDTH / 3 - 1, y1 = HEIGHT / 3;
	x2 = WIDTH * 2 / 3, y2 = HEIGHT * 2 / 3;
	pos Pos1 = { x1, y1 }, Pos2 = { x2, y2 };
	Snake snake1(Pos1), snake2(Pos2);	//两条蛇

	snake1.PrintSnake(1, snake2);
	snake2.PrintSnake(2, snake1);
	snake1.PrintFood(snake2);

	while (true)
	{
		if (_kbhit())
		{
			unsigned char op = _getch();
			if (op == 'w' || op == 'W' || op == 'a' || op == 'A' || op == 's' || op == 'S' || op == 'd' || op == 'D')
				snake1.ChangeDirection(op);
			if (op == 72 || op == 75 || op == 77 || op == 80)
				snake2.ChangeDirection(op);
			if (op == ' ') snake1.SpeedUp = !snake1.SpeedUp;
			if(op == '0') snake2.SpeedUp = !snake2.SpeedUp;
		}

		tt1 = GetTickCount();
		if (tt1 - t1 > (snake1.SpeedUp == true ? 100 : 500))		//自移
		{
			snake1.PrintSnake(1, snake2);
			t1 = tt1;
		}
		tt2 = GetTickCount();
		if (tt2 - t2 > (snake2.SpeedUp == true ? 100 : 500))		//自移
		{
			snake2.PrintSnake(2, snake1);
			t2 = tt2;
		}
		if (snake1.IsDead(snake2))
		{
			MessageBox(nullptr, "玩家二获胜", "游戏结束", MB_SYSTEMMODAL);
			system("cls");
			exit(0);
		}
		if (snake2.IsDead(snake1))
		{
			MessageBox(nullptr, "玩家一获胜", "游戏结束", MB_SYSTEMMODAL);
			system("cls");
			exit(0);
		}
	}
	return 0;
}