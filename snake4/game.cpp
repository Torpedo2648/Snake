#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

extern int shorttime, longtime;
extern vector<player> v;

DWORD slowtime, StartTime, EndTime;	//���ٳ���ʱ�䡢��Ϸ��ʼʱ�̡���Ϸ��ʱʱ��
pos Food, Ice, slowdown, cut;

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
		if (flag == 1) cout << "��";
		else if (flag == 2) cout << "��";
	}
	gotoxy(0, HEIGHT);

	if (Node[0].x == Food.x && Node[0].y == Food.y)//�Ե�ʳ��
	{
		length++;
		Node[length - 1].x = tail.x;
		Node[length - 1].y = tail.y;
		PrintFood(snake);
	}

	if (Node[0].x == Ice.x && Node[0].y == Ice.y)//�Ե�����
	{
		Ice.x = 0; Ice.y = 0;
		snake.state = 1;
		int type = rand() % 3;
		if (type == 0) Printice(snake);
		else if (type == 1)Printslowdown(snake);
		else Printcut(snake);
	}
	if (Node[0].x == slowdown.x && Node[0].y == slowdown.y)//�Ե�����
	{
		slowdown.x = 0; slowdown.y = 0;
		slowtime = GetTickCount();
		snake.state = 2;
		int type = rand() % 3;
		if (type == 0)Printice(snake);
		else if (type == 1)Printice(snake);
		else Printcut(snake);
	}
	if (Node[0].x == cut.x && Node[0].y == cut.y)//�Ե�����
	{
		cut.x = 0; cut.y = 0;
		if (snake.length >= 4)
		{
			snake.tail.x = snake.Node[snake.length - 2].x;
			snake.tail.y = snake.Node[snake.length - 2].y;

			gotoxy(snake.Node[snake.length - 1].x, snake.Node[snake.length - 1].y);
			cout << "  ";
			gotoxy(0, HEIGHT);
			snake.length--;
		}
		int type = rand() % 3;
		if (type == 0)Printice(snake);
		else if (type == 1)Printslowdown(snake);
		else Printcut(snake);
	}
}

void Snake::PrintSnake() {
	tail.x = Node[length - 1].x;
	tail.y = Node[length - 1].y;

	//�ƶ��ߵĲ��裺
	//1.�Ƚ�ͷ�����ȫ����ǰһ���ƶ�
	for (int i = length - 1; i > 0; i--)
	{
		Node[i] = Node[i - 1];
	}
	//��ʾsnakemove��ͷ�����������α�
	//2.�ٸı���ͷ�ķ���
	switch (direction)
	{
	case UP: Node[0].y--; break;
	case DOWN: Node[0].y++; break;
	case LEFT:Node[0].x -= 2; break;
	case RIGHT: Node[0].x += 2; break;
	}
	//3.�ƶ���β�����,�ٴ�ӡ
	gotoxy(tail.x, tail.y);
	cout << "  ";
	for (int i = 0; i < length; i++)
	{
		gotoxy(Node[i].x, Node[i].y);
		cout << "��";
	}
	gotoxy(0, HEIGHT);
	if (Node[0].x == Food.x && Node[0].y == Food.y)//�Ե�ʳ��
	{
		length++;
		Node[length - 1].x = tail.x;//�Ե������󳤶�+1,���ַ����Ǵ�β�͵�ͷ���α�ǣ�����ÿ�α����ԭ��β�͵�λ�ø�����β��
		Node[length - 1].y = tail.y;
		PrintFood();
	}
}

void Snake::PrintFood(const Snake& snake)
{
	while (1)
	{
		int i = 0, j = 0, x = 0, y = 0;
		Food.x = rand() % (WIDTH - 2);
		Food.y = rand() % (HEIGHT - 2);
		if (Food.x <= 4 || Food.y <= 2 || Food.x >= WIDTH || Food.y >= HEIGHT || Food.x % 2 == 1) continue;
		if (Food == Ice || Food == slowdown || Food == cut)continue;
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
			cout << "��";
			gotoxy(0, HEIGHT);
			break;
		}
	}
}

void Snake::PrintFood() {
	while (1)
	{
		int i = 0;
		Food.x = rand() % (WIDTH - 2);
		Food.y = rand() % (HEIGHT - 2);
		if (Food.x <= 4 || Food.y <= 1 || Food.x >= WIDTH || Food.y >= HEIGHT || Food.x % 2 == 1) continue;
		for (i = 0; i < length; i++)
		{
			if (Food.x == Node[i].x && Food.y == Node[i].y) break;//һ�����������������Ͼ�����ˢʳ��λ��
		}
		if (i == length)
		{
			gotoxy(Food.x, Food.y);
			cout << "��";
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
		Ice.x = rand() % (WIDTH - 2);
		Ice.y = rand() % (HEIGHT - 2);
		if (Ice.x <= 4 || Ice.y <= 1 || Ice.x >= WIDTH || Ice.y >= HEIGHT || Ice.x % 2 == 1) continue;
		if (Ice == slowdown || Ice == Food || Ice == cut)continue;
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
			cout << "��";
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
		slowdown.x = rand() % (WIDTH - 2);
		slowdown.y = rand() % (HEIGHT - 2);
		if (slowdown.x <= 4 || slowdown.y <= 1 || slowdown.x >= WIDTH || slowdown.y >= HEIGHT || slowdown.x % 2 == 1) continue;
		if (slowdown == Food || slowdown == Ice || slowdown == cut)continue;
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
			cout << "��";
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
		cut.x = rand() % (WIDTH - 2);
		cut.y = rand() % (HEIGHT - 2);
		if (cut.x <= 4 || cut.y <= 1 || cut.x >= WIDTH || cut.y >= HEIGHT || cut.x % 2 == 1) continue;
		if (cut == Food || cut == Ice || cut == slowdown)continue;
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
			cout << "��";
			gotoxy(0, HEIGHT);
			break;
		}
	}
}
int Snake::IsDead(const Snake& snake)
{
	if (Node[0].x <= 0 || Node[0].y <= 0 || Node[0].x >= WIDTH || Node[0].y >= HEIGHT - 1) return 1;//����ͼ
	for (int i = 1; i < length; i++)//ײ���Լ�
		if (Node[0].x == Node[i].x && Node[0].y == Node[i].y) return 1;
	for (int i = 1; i < snake.length; i++)//ײ���Է�
		if (Node[0].x == snake.Node[i].x && Node[0].y == snake.Node[i].y) return 1;
	if (Node[0] == snake.Node[0]) return 2;
	return 0;
}

int Snake::IsDead() {
	if (Node[0].x <= 0 || Node[0].y <= 0 || Node[0].x >= WIDTH || Node[0].y >= HEIGHT - 1) {
		return 1;//����ͼ
	}
	for (int i = 1; i < length; i++) {
		if (Node[0].x == Node[i].x && Node[0].y == Node[i].y) {
			return 1;
		}
	}//ײ���Լ�

}

void CreateMap()
{
	system("mode con cols=102 lines=38");
	for (int i = 0; i < WIDTH; i += 2)
	{
		gotoxy(i, 0);
		cout << "��";
		gotoxy(i, HEIGHT - 1);
		cout << "��";
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << "��";
		gotoxy(WIDTH + 1, i);
		cout << "��";
	}
	gotoxy(0, HEIGHT);
	StartTime = GetTickCount();
}

void DoubleMode(char *name)
{
	system("cls");
	CreateMap();
	srand((unsigned)time(NULL));
	int x1, y1, x2, y2;
	x1 = WIDTH / 3 - 1, y1 = HEIGHT / 3;
	x2 = WIDTH * 2 / 3, y2 = HEIGHT * 2 / 3;
	pos Pos1 = { x1, y1 }, Pos2 = { x2, y2 };
	Snake snake1(Pos1), snake2(Pos2);		//������
	snake1.PrintSnake(1, snake2);
	snake2.PrintSnake(2, snake1);
	snake1.PrintFood(snake2);
	int type = rand() % 3;
	if (type == 0) snake1.Printice(snake2);
	else if (type == 1)snake1.Printslowdown(snake2);
	else snake1.Printcut(snake2);

	DWORD t1 = GetTickCount(), t2 = GetTickCount(), tt1, tt2;	//�ж��Ƿ�����ƶ�
	while (true)
	{
		DWORD EndTime = GetTickCount();
		gotoxy(WIDTH / 2 - 6, HEIGHT);
		cout << "��Ϸʱ�䣨�룩��" << (EndTime - StartTime) / 1000;
		gotoxy(1, HEIGHT);
		cout << "���һ�÷֣�" << snake1.length * 100;
		gotoxy(WIDTH - 14, HEIGHT);
		cout << "��Ҷ��÷֣�" << snake2.length * 100;
		gotoxy(0, HEIGHT);
		if (_kbhit())
		{
			char op = _getch();
			if (op == 'w' || op == 'W' || op == 'a' || op == 'A' || op == 's' || op == 'S' || op == 'd' || op == 'D')
				snake1.ChangeDirection(op);
			if (op == 72 || op == 75 || op == 77 || op == 80)
				snake2.ChangeDirection(op);
			if (op == ' ') snake1.SpeedUp = !snake1.SpeedUp;	//�ı����״̬
			if (op == '0') snake2.SpeedUp = !snake2.SpeedUp;
		}

		tt1 = GetTickCount();
		//�����ٶ��·ֱ�Ĵ�ӡ���ʱ��
		if (snake1.state == 0 && tt1 - t1 > (snake1.SpeedUp == true ? shorttime : longtime)) {
			//��ӡ��
			snake1.PrintSnake(1, snake2);
			//����ʱ��
			t1 = tt1;
		}
		//�жϱ����� ��������ʱ��Ϊ1.5�룬 1.5����ӡ������
		else if (snake1.state == 1 && tt1 - t1 > 1500) {
			//��ӡ��
			snake1.PrintSnake(1, snake2);
			//����ʱ��
			t1 = tt1;
			//�ָ�����״̬
			snake1.state = 0;
		}
		//�жϼ��٣� ���پ�ÿ��0.3���ӡ�����ߣ� �ҳ���ʱ�䲻����1.5��
		//slowtime ÿ�γԵ����پͻ�ȡ��ǰʱ��
		else if (snake1.state == 2 && tt1 - t1 > 300) {
			//��ӡ��
			snake1.PrintSnake(1, snake2);
			if (tt1 - slowtime > 1500) {
				snake1.state = 0;
			}
			//����ʱ��
			t1 = tt1;
		}

		tt2 = GetTickCount();
		//�����ٶ��·ֱ�Ĵ�ӡ���ʱ��
		if (snake2.state == 0 && (tt2 - t2 > (snake2.SpeedUp == true ? shorttime : longtime))) {
			//��ӡ��
			snake2.PrintSnake(2, snake1);
			//����ʱ��
			t2 = tt2;
		}
		//�жϱ����� ��������ʱ��Ϊ1.5�룬 1.5����ӡ������
		else if (snake2.state == 1 && tt2 - t2 > 1500) {
			//��ӡ��
			snake2.PrintSnake(2, snake1);
			//����ʱ��
			t2 = tt2;
			//�ָ�����״̬
			snake2.state = 0;
		}
		//�жϼ��٣� ���پ�ÿ��0.3���ӡ�����ߣ� �ҳ���ʱ�䲻����1.5��
		//slowtime ÿ�γԵ����پͻ�ȡ��ǰʱ��
		else if (snake2.state == 2 && tt2 - t2 > 300) {
			//��ӡ��
			snake2.PrintSnake(2, snake1);
			if (tt2 - slowtime > 1500) {
				snake2.state = 0;
			}
			//����ʱ��
			t2 = tt2;
		}
		//�жϼ���ʱ�� ����1.5��ͻָ�����״̬
		//if (tt2 - slowtime > 1500 && snake2.state == 2) snake2.state = 0;

		if (snake1.IsDead(snake2) == 1)
		{
			MessageBox(nullptr, "��Ҷ���ʤ", "��Ϸ����", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
		if (snake2.IsDead(snake1) == 1)
		{
			MessageBox(nullptr, "���һ��ʤ", "��Ϸ����", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
		if (snake1.IsDead(snake2) == 2)
		{
			MessageBox(nullptr, "ƽ��", "��Ϸ����", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
	}
	Welcome(name);
}

void SingleMode(char* name)
{
	system("cls");
	CreateMap();
	srand((unsigned)time(NULL));
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	stringstream ss;
	ss << tm_t->tm_year + 1900 << "-" << tm_t->tm_mon + 1 << "-" << tm_t->tm_mday
		<< "-" << tm_t->tm_hour << ":" << tm_t->tm_min << ":" << tm_t->tm_sec;
	int x = WIDTH / 3 - 1, y = HEIGHT / 3;
	Snake snake({ x, y });
	snake.PrintFood();
	DWORD t0 = GetTickCount(), tt0;
	while (1) 
	{
		DWORD EndTime = GetTickCount();

		gotoxy(WIDTH / 2 - 6, HEIGHT);
		cout << "��Ϸʱ�䣨�룩��" << (EndTime - StartTime) / 1000;
		gotoxy(1, HEIGHT);
		cout << "�÷֣�" << snake.length * 100;
		gotoxy(0, height);
		if (_kbhit())
		{
			char op = _getch();
			if (op == 72 || op == 75 || op == 77 || op == 80)
				snake.ChangeDirection(op);
			if (op == ' ') snake.SpeedUp = !snake.SpeedUp;	//�ı����״̬
		}
		tt0 = GetTickCount();
		//�����ٶ��·ֱ�Ĵ�ӡ���ʱ��
		if (snake.state == 0 && tt0 - t0 > (snake.SpeedUp == true ? shorttime : longtime)) {
			//��ӡ��
			snake.PrintSnake();
			//����ʱ��
			t0 = tt0;
		}
		if (snake.IsDead() == 1)
		{
			int mark = 0;
			player tmp;
			while (v.size()) v.pop_back();
			FILE* r = fopen("playerdata.txt", "r");
			while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
			{
				if (compare(tmp.username, name) && snake.length * 100 > tmp.score)
				{
					mark = 1;
					tmp.score = snake.length * 100;
					for (int i = 0; i < ss.str().size(); i++)
					{
						tmp.time[i] = ss.str()[i];
					}
				}
				v.push_back(tmp);
			}
			fclose(r);
			sort(v.begin(), v.end(), cmp);
			FILE* w = fopen("playerdata.txt", "w");
			for (int i = 0; i < v.size(); i++)
			{
				v[i].rank = i + 1;
				fprintf(w, "%-8s\t\t%-16s\t%-4d\t\t%-4d\t%s\n", v[i].username, v[i].password, v[i].score, v[i].rank, v[i].time);
			}
			fclose(w);
			if(mark == 1) MessageBox(nullptr, "��ϲ��������������ʷ��¼��", "��Ϸ����", MB_SYSTEMMODAL);
			else MessageBox(nullptr, "���ź�����δ����������ʷ��¼", "��Ϸ����", MB_SYSTEMMODAL);
			system("cls");
			break;
		}
	}
	Welcome(name);
}