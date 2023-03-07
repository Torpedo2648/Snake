#include"menu.h"
#include"game.h"

int shorttime = 120, longtime = 200;
vector<player> v;

void gotoxy(short x, short y)
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

bool compare(char *A, char *B)
{
	if (strlen(A) != strlen(B)) return 0;
	for (int i = 0; A[i] != 0; i++)
	{
		if (A[i] != B[i])
			return 0;
	}
	return 1;
}
bool cmp(player a, player b)
{
	return a.score > b.score;
}

void Registration_login()
{
	system("cls");
	mciSendString(TEXT("open bgm.mp3"), 0, 0, 0);	//播放音乐
	mciSendString(TEXT("play bgm.mp3 repeat"), 0, 0, 0);//重复播放
	CONSOLE_CURSOR_INFO cursor_info = { TRUE, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //隐藏光标
	gotoxy(WIDTH / 3-4, HEIGHT / 4);
	cout << "Please choose a number ranged from 1 to 4";
	gotoxy(WIDTH / 4-4, HEIGHT * 2 / 5+2);
	cout << "1.REGISTRATION    2.USERS_LOGIN    3.ADMIN_LOGIN    4.EXIT";
	gotoxy(0,0);
B:
	char op = _getch();
	if (op == '1') Registration();
	else if (op == '2') UsersLogin();
	else if (op == '3') AdminLogin();
	else if (op == '4') Exit();
	else
	{
		MessageBox(nullptr, "请重新输入！", "输入错误！", MB_OK);
		goto B;
	}
}

void Registration()
{
	system("cls");
	player tmp, tmp2;
	int flag = 0;
	cout << "请输入用户名：";
	cin >> tmp.username;
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp2.username, tmp2.password, &tmp2.score, &tmp2.rank, tmp2.time) != EOF)
	{
		if (compare(tmp2.username, tmp.username))
		{
			flag = 1;
			break;
		}
	}
	fclose(r);
	if (flag == 1)
	{
		cout << "该用户名已被注册" << endl;
		system("pause");
		Registration_login();
	}
	else if (flag == 0)
	{
		cout << "请输入密码：";
		cin >> tmp.password;
		FILE* w = fopen("playerdata.txt", "a+");
		//fprintf(fp, "用户名\t\t用户密码\t\t最高得分\t\t排名\n");
		fprintf(w, "%-8s\t\t%-16s\t%-4d\t%-4d\t%s\n", tmp.username, tmp.password, tmp.score, tmp.rank, tmp.time);
		fclose(w);
		//v.push_back(tmp);
		cout << "注册成功" << endl;
		system("pause");
		Registration_login();
	}
}

void UsersLogin()
{
	system("cls");
	player tmp, tmp2;
	int flag = 0;
	cout << "请输入您的用户名：";
	cin >> tmp.username;
	cout << "请输入您的用户密码：";
	cin >> tmp.password;
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp2.username, tmp2.password, &tmp2.score, &tmp2.rank, tmp2.time) != EOF)
	{
		if (compare(tmp2.username, tmp.username) && compare(tmp2.password, tmp.password))
		{
			flag = 1;
		}
	}
	fclose(r);
	if (flag == 1)
	{
		cout << "登录成功" << endl;
		system("pause");
		Welcome(tmp.username);
	}
	else if (flag == 0)
	{
		cout << "登录失败" << endl;
		system("pause");
		Registration_login();
	}
}
void AdminLogin()
{
	system("cls");
	int flag = 0;
	char adminaccout[100] = { 0 }, accout[100] = { 0 };
	char adminpassword[100] = { 0 }, password[100] = { 0 };
	cout << "请输入管理员账号：";
	cin >> adminaccout;
	cout << "请输入管理员密码：";
	cin >> adminpassword;
	FILE* r = fopen("admindata.txt", "r");
	fscanf(r, "%s\t%s", accout, password);
	if (compare(adminaccout, accout) && compare(adminpassword, password)) flag = 1;
	fclose(r);
	if (flag == 1)
	{
		cout << "登录成功" << endl;
		system("pause");
		Welcome();
	}
	else if (flag == 0)
	{
		cout << "登录失败" << endl;
		system("pause");
		Registration_login();
	}
}

void Welcome(char *name)
{
	system("cls");
	gotoxy(WIDTH / 3 + 2, HEIGHT / 4);
	cout << "Welcome to Greedy Snake Battle";
	gotoxy(WIDTH / 3 - 4, HEIGHT * 2 / 5 - 1);
	cout << "Please choose a number ranged from 1 to 5";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 2);
	cout << "1.START GAME";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 4);
	cout << "2.SETTINGS";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 6);
	cout << "3.DESCRIPTION";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 8);
	cout << "4.MY INFORMATION";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 10);
	cout << "5.RANKING";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 12);
	cout << "6.LOGOUT";
A:
	char op = _getch();
	if (op == '1') StartGame(name);
	else if (op == '2') Settings(name);
	else if (op == '3') Description(name);
	else if (op == '4') MyInformation(name);
	else if (op == '5') PrintRanking(name);
	else if (op == '6') Logout();
	else
	{
		MessageBox(nullptr, "请重新输入！", "输入错误！", MB_OK);
		goto A;
	}
}

void Welcome()
{
	system("cls");
	gotoxy(WIDTH / 3 + 2, HEIGHT / 4);
	cout << "欢迎回来，尊贵的管理员";
	gotoxy(WIDTH / 3 - 4, HEIGHT * 2 / 5 - 1);
	cout << "请选择您要进行的操作，输入一个数字（1~4）";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 2);
	cout << "1.查询用户信息";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 4);
	cout << "2.修改用户信息";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 6);
	cout << "3.删除用户信息";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 8);
	cout << "4.退出登录";
A:
	char op = _getch();
	if (op == '1') InquiryInformation();
	else if (op == '2') ModifyInformation();
	else if (op == '3') DeleteInformation();
	else if (op == '4') Logout();
	else
	{
		MessageBox(nullptr, "请重新输入！", "输入错误！", MB_OK);
		goto A;
	}
}

void Exit()
{
	system("cls");
	exit(0);
}

void StartGame(char *name)
{
	initgraph(width, height);
	MOUSEMSG msg;
	setbkcolor(RGB(30, 30, 30));
	cleardevice();

	settextstyle(46, 28, "楷体");
	settextcolor(RGB(78, 201, 176));
	outtextxy(290, 140, "双人模式");
	outtextxy(290, 340, "单人模式");
	setlinecolor(RGB(181, 206, 168));
	rectangle(280, 130, 520, 195);
	rectangle(280, 330, 520, 395);

	settextstyle(46, 28, "楷体");
	int flag = 0;
	while (1)
	{
		msg = GetMouseMsg();
		int x = msg.x;		//rectangle(280,130,520,195);		长 240 宽 65
		int y = msg.y;

		if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65 && msg.mkLButton)
		{
			flag = 1;//双人模式
			break;
		}
		else if (x - 280 < 240 && x - 280 > 0 && y - 330 > 0 && y - 330 < 65 && msg.mkLButton)
		{
			flag = 2;//单人模式
			break;
		}
		else if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65)
		{
			settextcolor(RGB(78, 201, 176));
			outtextxy(290, 140, "双人模式");
		}
		else if (x - 280 < 240 && x - 280 > 0 && y - 330 > 0 && y - 330 < 65)
		{
			settextcolor(RGB(78, 201, 176));
			outtextxy(290, 340, "单人模式");
		}
		else
		{
			settextcolor(RGB(255, 255, 255));
			outtextxy(290, 140, "双人模式");
			outtextxy(290, 340, "单人模式");
		}
	}
	closegraph();
	if (flag == 1) DoubleMode(name);
	else if (flag == 2) SingleMode(name);
}

void Settings(char *name)
{
	system("cls");
	cout << "请选择难度等级：1.入门\t2.中等\t3.困难" << endl;
	char op = _getch();
	if (op == '1')
	{
		cout << "已成功设置入门模式" << endl;
		shorttime = 120, longtime = 200;
	}
	else if (op == '2')
	{
		cout << "已成功设置中等模式" << endl;
		shorttime = 60, longtime = 120;
	}
	else if (op == '3')
	{
		cout << "已成功设置困难模式" << endl;
		shorttime = 30, longtime = 60;
	}
	else
	{
		cout << "请重新输入！" << endl;
		system("pause");
		Settings(name);
	}
	system("pause");
	Welcome(name);
}

void Logout()
{
	Registration_login();
}

void MyInformation(char *name)
{
	system("cls");
	player tmp;
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
	{
		if (compare(tmp.username, name))
		{
			cout << "您的用户名为：" << tmp.username << endl;
			cout << "您的登录密码为：" << tmp.password << endl;
			cout << "您的历史最高得分为：" << tmp.score << endl;
			cout << "您的历史最高排名为：" << tmp.rank << endl;
			cout << "您的最高得分游戏时间为：" << tmp.time << endl;
			break;
		}
	}
	fclose(r);
	system("pause");
	Welcome(name);
}

void PrintRanking(char *name)
{
	system("cls");
	cout << "用户名\t\t最高得分\t最高排名\t游戏时间" << endl << endl;
	player tmp;
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
	{
		printf("%s\t\t%d\t\t%d\t\t%s\n\n", tmp.username, tmp.score, tmp.rank, tmp.time);
	}
	fclose(r);
	system("pause");
	Welcome(name);
}

void Description(char *name)
{
	system("cls");
	initgraph(width, height);
	settextstyle(20, 10, "楷体");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 40, "双人模式游戏规则：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(150, 70, "玩家一：控制：4个光标键，点按数字键0改变加速状态");
	outtextxy(150, 100, "玩家二：控制：W A S D，点按空格键改变加速状态");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 140, "胜利条件：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(280, 140, "1.对方触碰边界");
	outtextxy(280, 170, "2.对方触碰对方身体");
	outtextxy(280, 200, "3.对方触碰己方身体");
	outtextxy(270, 230, "注： 头碰头是平局 ！！！");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 260, "图案说明：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(140, 290, " 1. ◆代表地图边界，■代表玩家一，□代表玩家二");
	outtextxy(140, 320, " 2. ●代表食物，※代表冰冻，▲代表减速，★代表缩短");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 400, "单人模式游戏规则：");
	settextcolor(RGB(220, 220, 170));
	outtextxy(150, 430, "方向控制：4个光标键，点按空格键改变加速状态");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 480, "按任意键返回");
	system("pause");
	closegraph();
	Welcome(name);
}

void InquiryInformation()
{
	system("cls");
	cout << "请选择操作: \t1.查看全部用户\t2.搜索单个用户\n";	
	char op = _getch();
	system("cls");
	player tmp;
	FILE* r = fopen("playerdata.txt", "r");
	if (op == '1')
	{
		cout << "用户名\t\t\t登录密码\t\t最高得分\t最高排名\t游戏时间" << endl << endl;
		while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
		{
			printf("%-8s\t\t%-16s\t%-4d\t\t%-4d\t\t%s\n\n", tmp.username, tmp.password, tmp.score, tmp.rank, tmp.time);
		}
	}
	else if (op == '2')
	{
		char inquiredname[100] = { 0 };
		cout << "请输入您所需要查询的用户名：";
		cin >> inquiredname;
		cout << "用户名\t\t\t登录密码\t\t最高得分\t最高排名\t游戏时间" << endl << endl;
		int exist =0;
		while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
		{
			if (compare(inquiredname, tmp.username))
			{
				exist = 1;
				printf("%-8s\t\t%-16s\t%-4d\t\t%-4d\t\t%s\n\n", tmp.username, tmp.password, tmp.score, tmp.rank, tmp.time);
			}
		}
		if (!exist) cout << "\n抱歉，查无此人\n" << endl;
	}
	else
	{
		cout << "\n请重新输入！\n" << endl;
		system("pause");
		InquiryInformation();
	}
	fclose(r);
	system("pause");
	Welcome();
}

void ModifyInformation()
{
	system("cls");
	char modifiedname[100] = { 0 };
	player tmp, tmp2;
	cout << "请输入您想修改用户的用户名：";
	cin >> modifiedname;

	int exist = 0;
	while (v.size()) v.pop_back();
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
	{
		if (compare(tmp.username, modifiedname))
		{
			exist = 1;
			cout << "请分别输入修改后的用户名，密码，得分" << endl;
			cin >> tmp2.username >> tmp2.password >> tmp2.score;
			srand((unsigned)time(NULL));
			time_t now = time(NULL);
			tm* tm_t = localtime(&now);
			stringstream ss;
			ss << tm_t->tm_year + 1900 << "-" << tm_t->tm_mon + 1 << "-" << tm_t->tm_mday
				<< "-" << tm_t->tm_hour << ":" << tm_t->tm_min << ":" << tm_t->tm_sec;
			for (int i = 0; i < ss.str().size(); i++)
				tmp2.time[i] = ss.str()[i];
			tmp = tmp2;
		}
		v.push_back(tmp);
	}
	fclose(r);
	if (!exist) cout << "\n抱歉，查无此人\n" << endl;
	else
	{
		sort(v.begin(), v.end(), cmp);
		FILE* w = fopen("playerdata.txt", "w");
		for (int i = 0; i < v.size(); i++)
		{
			v[i].rank = i + 1;
			fprintf(w, "%-8s\t\t%-16s\t%-4d\t\t%-4d\t%s\n", v[i].username, v[i].password, v[i].score, v[i].rank, v[i].time);
		}
		fclose(w);
		cout << "\n修改成功！\n" << endl;
	}
	system("pause");
	Welcome();
}

void DeleteInformation()
{
	system("cls");
	char deletedname[100] = { 0 };
	player tmp;
	cout << "请输入您想删除用户的用户名：";
	cin >>deletedname;
	int exist = 0;
	while (v.size()) v.pop_back();
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
	{
		if (!compare(tmp.username, deletedname)) v.push_back(tmp);
		else exist = 1;
	}
	fclose(r);
	if (!exist) cout << "\n抱歉，查无此人\n" << endl;
	else
	{
		sort(v.begin(), v.end(), cmp);
		FILE* w = fopen("playerdata.txt", "w");
		for (int i = 0; i < v.size(); i++)
		{
			v[i].rank = i + 1;
			fprintf(w, "%-8s\t\t%-16s\t%-4d\t\t%-4d\t%s\n", v[i].username, v[i].password, v[i].score, v[i].rank, v[i].time);
		}
		fclose(w);
		cout << "\n删除成功！\n" << endl;;
	}
	system("pause");
	Welcome();
}
