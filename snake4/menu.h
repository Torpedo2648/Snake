#pragma once
#ifndef __MENU__
#define __MENU__	

#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include <graphics.h>
#include <iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<sstream>
#include<string.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include<Windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm")
using namespace std;

const int MAXLEN = 1000;
const int WIDTH = 99;
const int HEIGHT = 36;
const int width = 800;
const int height = 600;
enum Direction { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77 };

struct pos	//坐标结构体
{
	int x, y;
	bool operator==(const pos& W) const	//重载判断等号运算符
	{
		return x == W.x && y == W.y;
	}
};

struct player
{
	char username[100] = { 0 };
	char password[100] = { 0 };
	char time[100] = { 0 };
	int score = 0;
	int rank = 0;
};

bool cmp(player a, player b);

void gotoxy(short x, short y);

bool compare(char* A, char* B);

void Registration_login();

void Registration();

void UsersLogin();

void AdminLogin();

void Exit();

void Welcome(char* name);

void Welcome();

void Logout();

void StartGame(char *name);

void Settings(char *name);

void MyInformation(char* name);

void PrintRanking(char* name);

void Description(char* name);

void InquiryInformation();

void ModifyInformation();

void DeleteInformation();

#endif