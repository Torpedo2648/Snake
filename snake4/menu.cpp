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
	mciSendString(TEXT("open bgm.mp3"), 0, 0, 0);	//��������
	mciSendString(TEXT("play bgm.mp3 repeat"), 0, 0, 0);//�ظ�����
	CONSOLE_CURSOR_INFO cursor_info = { TRUE, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //���ع��
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
		MessageBox(nullptr, "���������룡", "�������", MB_OK);
		goto B;
	}
}

void Registration()
{
	system("cls");
	player tmp, tmp2;
	int flag = 0;
	cout << "�������û�����";
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
		cout << "���û����ѱ�ע��" << endl;
		system("pause");
		Registration_login();
	}
	else if (flag == 0)
	{
		cout << "���������룺";
		cin >> tmp.password;
		FILE* w = fopen("playerdata.txt", "a+");
		//fprintf(fp, "�û���\t\t�û�����\t\t��ߵ÷�\t\t����\n");
		fprintf(w, "%-8s\t\t%-16s\t%-4d\t%-4d\t%s\n", tmp.username, tmp.password, tmp.score, tmp.rank, tmp.time);
		fclose(w);
		//v.push_back(tmp);
		cout << "ע��ɹ�" << endl;
		system("pause");
		Registration_login();
	}
}

void UsersLogin()
{
	system("cls");
	player tmp, tmp2;
	int flag = 0;
	cout << "�����������û�����";
	cin >> tmp.username;
	cout << "�����������û����룺";
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
		cout << "��¼�ɹ�" << endl;
		system("pause");
		Welcome(tmp.username);
	}
	else if (flag == 0)
	{
		cout << "��¼ʧ��" << endl;
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
	cout << "���������Ա�˺ţ�";
	cin >> adminaccout;
	cout << "���������Ա���룺";
	cin >> adminpassword;
	FILE* r = fopen("admindata.txt", "r");
	fscanf(r, "%s\t%s", accout, password);
	if (compare(adminaccout, accout) && compare(adminpassword, password)) flag = 1;
	fclose(r);
	if (flag == 1)
	{
		cout << "��¼�ɹ�" << endl;
		system("pause");
		Welcome();
	}
	else if (flag == 0)
	{
		cout << "��¼ʧ��" << endl;
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
		MessageBox(nullptr, "���������룡", "�������", MB_OK);
		goto A;
	}
}

void Welcome()
{
	system("cls");
	gotoxy(WIDTH / 3 + 2, HEIGHT / 4);
	cout << "��ӭ���������Ĺ���Ա";
	gotoxy(WIDTH / 3 - 4, HEIGHT * 2 / 5 - 1);
	cout << "��ѡ����Ҫ���еĲ���������һ�����֣�1~4��";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 2);
	cout << "1.��ѯ�û���Ϣ";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 4);
	cout << "2.�޸��û���Ϣ";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 6);
	cout << "3.ɾ���û���Ϣ";
	gotoxy(WIDTH / 3 + 10, HEIGHT * 2 / 5 + 8);
	cout << "4.�˳���¼";
A:
	char op = _getch();
	if (op == '1') InquiryInformation();
	else if (op == '2') ModifyInformation();
	else if (op == '3') DeleteInformation();
	else if (op == '4') Logout();
	else
	{
		MessageBox(nullptr, "���������룡", "�������", MB_OK);
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

	settextstyle(46, 28, "����");
	settextcolor(RGB(78, 201, 176));
	outtextxy(290, 140, "˫��ģʽ");
	outtextxy(290, 340, "����ģʽ");
	setlinecolor(RGB(181, 206, 168));
	rectangle(280, 130, 520, 195);
	rectangle(280, 330, 520, 395);

	settextstyle(46, 28, "����");
	int flag = 0;
	while (1)
	{
		msg = GetMouseMsg();
		int x = msg.x;		//rectangle(280,130,520,195);		�� 240 �� 65
		int y = msg.y;

		if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65 && msg.mkLButton)
		{
			flag = 1;//˫��ģʽ
			break;
		}
		else if (x - 280 < 240 && x - 280 > 0 && y - 330 > 0 && y - 330 < 65 && msg.mkLButton)
		{
			flag = 2;//����ģʽ
			break;
		}
		else if (x - 280 < 240 && x - 280 > 0 && y - 130 > 0 && y - 130 < 65)
		{
			settextcolor(RGB(78, 201, 176));
			outtextxy(290, 140, "˫��ģʽ");
		}
		else if (x - 280 < 240 && x - 280 > 0 && y - 330 > 0 && y - 330 < 65)
		{
			settextcolor(RGB(78, 201, 176));
			outtextxy(290, 340, "����ģʽ");
		}
		else
		{
			settextcolor(RGB(255, 255, 255));
			outtextxy(290, 140, "˫��ģʽ");
			outtextxy(290, 340, "����ģʽ");
		}
	}
	closegraph();
	if (flag == 1) DoubleMode(name);
	else if (flag == 2) SingleMode(name);
}

void Settings(char *name)
{
	system("cls");
	cout << "��ѡ���Ѷȵȼ���1.����\t2.�е�\t3.����" << endl;
	char op = _getch();
	if (op == '1')
	{
		cout << "�ѳɹ���������ģʽ" << endl;
		shorttime = 120, longtime = 200;
	}
	else if (op == '2')
	{
		cout << "�ѳɹ������е�ģʽ" << endl;
		shorttime = 60, longtime = 120;
	}
	else if (op == '3')
	{
		cout << "�ѳɹ���������ģʽ" << endl;
		shorttime = 30, longtime = 60;
	}
	else
	{
		cout << "���������룡" << endl;
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
			cout << "�����û���Ϊ��" << tmp.username << endl;
			cout << "���ĵ�¼����Ϊ��" << tmp.password << endl;
			cout << "������ʷ��ߵ÷�Ϊ��" << tmp.score << endl;
			cout << "������ʷ�������Ϊ��" << tmp.rank << endl;
			cout << "������ߵ÷���Ϸʱ��Ϊ��" << tmp.time << endl;
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
	cout << "�û���\t\t��ߵ÷�\t�������\t��Ϸʱ��" << endl << endl;
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
	settextstyle(20, 10, "����");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 40, "˫��ģʽ��Ϸ����");
	settextcolor(RGB(220, 220, 170));
	outtextxy(150, 70, "���һ�����ƣ�4���������㰴���ּ�0�ı����״̬");
	outtextxy(150, 100, "��Ҷ������ƣ�W A S D���㰴�ո���ı����״̬");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 140, "ʤ��������");
	settextcolor(RGB(220, 220, 170));
	outtextxy(280, 140, "1.�Է������߽�");
	outtextxy(280, 170, "2.�Է������Է�����");
	outtextxy(280, 200, "3.�Է�������������");
	outtextxy(270, 230, "ע�� ͷ��ͷ��ƽ�� ������");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 260, "ͼ��˵����");
	settextcolor(RGB(220, 220, 170));
	outtextxy(140, 290, " 1. �������ͼ�߽磬���������һ����������Ҷ�");
	outtextxy(140, 320, " 2. �����ʳ��������������������٣����������");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 400, "����ģʽ��Ϸ����");
	settextcolor(RGB(220, 220, 170));
	outtextxy(150, 430, "������ƣ�4���������㰴�ո���ı����״̬");
	settextcolor(RGB(214, 157, 133));
	outtextxy(150, 480, "�����������");
	system("pause");
	closegraph();
	Welcome(name);
}

void InquiryInformation()
{
	system("cls");
	cout << "��ѡ�����: \t1.�鿴ȫ���û�\t2.���������û�\n";	
	char op = _getch();
	system("cls");
	player tmp;
	FILE* r = fopen("playerdata.txt", "r");
	if (op == '1')
	{
		cout << "�û���\t\t\t��¼����\t\t��ߵ÷�\t�������\t��Ϸʱ��" << endl << endl;
		while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
		{
			printf("%-8s\t\t%-16s\t%-4d\t\t%-4d\t\t%s\n\n", tmp.username, tmp.password, tmp.score, tmp.rank, tmp.time);
		}
	}
	else if (op == '2')
	{
		char inquiredname[100] = { 0 };
		cout << "������������Ҫ��ѯ���û�����";
		cin >> inquiredname;
		cout << "�û���\t\t\t��¼����\t\t��ߵ÷�\t�������\t��Ϸʱ��" << endl << endl;
		int exist =0;
		while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
		{
			if (compare(inquiredname, tmp.username))
			{
				exist = 1;
				printf("%-8s\t\t%-16s\t%-4d\t\t%-4d\t\t%s\n\n", tmp.username, tmp.password, tmp.score, tmp.rank, tmp.time);
			}
		}
		if (!exist) cout << "\n��Ǹ�����޴���\n" << endl;
	}
	else
	{
		cout << "\n���������룡\n" << endl;
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
	cout << "�����������޸��û����û�����";
	cin >> modifiedname;

	int exist = 0;
	while (v.size()) v.pop_back();
	FILE* r = fopen("playerdata.txt", "r");
	while (fscanf(r, "%s\t\t%s\t%d\t\t%d\t%s\n", tmp.username, tmp.password, &tmp.score, &tmp.rank, tmp.time) != EOF)
	{
		if (compare(tmp.username, modifiedname))
		{
			exist = 1;
			cout << "��ֱ������޸ĺ���û��������룬�÷�" << endl;
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
	if (!exist) cout << "\n��Ǹ�����޴���\n" << endl;
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
		cout << "\n�޸ĳɹ���\n" << endl;
	}
	system("pause");
	Welcome();
}

void DeleteInformation()
{
	system("cls");
	char deletedname[100] = { 0 };
	player tmp;
	cout << "����������ɾ���û����û�����";
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
	if (!exist) cout << "\n��Ǹ�����޴���\n" << endl;
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
		cout << "\nɾ���ɹ���\n" << endl;;
	}
	system("pause");
	Welcome();
}
