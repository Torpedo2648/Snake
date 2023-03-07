#include"snake.h"

void Welcome()
{
    gotoxy(wide / 3 + 2, high / 3);
    cout << "Welcome to Greedy Snake Battle" ;
    gotoxy(wide / 3 - 4, high * 3 / 5 - 1);
    cout << "Please choose a number ranged from 1 to 3";
    gotoxy(wide / 3 + 10, high * 3 / 5 + 2);
    cout << "1.START GAME";
    gotoxy(wide / 3 + 10, high * 3 / 5 + 4);
    cout << "2.QUIT GAME";
    gotoxy(wide / 3 + 10, high * 3 / 5 + 6);
    cout << "3.EXPLANATION";
    gotoxy(0, high);
}

void Explanation()
{
    gotoxy(wide / 2 - 4, high / 3);
    cout << "游戏规则" << endl;
    cout << "蛇可以有四个方向，按空格键切换速度。撞墙就死，头部撞到自己或者他人的身体就死，头部对撞同归于尽。" <<endl;
    cout <<"游戏时间限制为2分钟，每人三条命，如果在游戏时间内三条命全丢了，则直接算输，否则根据得分判断输赢。" << endl;
    gotoxy(wide / 2 - 4, high / 3 + 8);
    cout << "积分规则" << endl;
    cout << "道具得分加上剩余命数得分，一条命十分。" << endl;
    gotoxy(0, high / 3 + 14);
    system("pause");
}

void StartGame()
{
    CreateMap();
    Snake s, * snake = &s;
    Food f, * food = &f;
    InitSnake(snake);
    PrintSnake(snake);
    PrintFood(snake, food);
    int speedup = 0;
    while (1)
    {
        tailx = snake->x[0];
        taily = snake->y[0];
        if (_kbhit())
        {
            unsigned char op = _getch();
            if (check(ch, op)) ch = op;
            if (op == ' ') speedup = !speedup;
        }
        MoveSnake(ch, snake);
        if (IsDead(snake))
        {
            system("cls");
            gotoxy(wide / 3 + 8, high / 3);
            cout << "很遗憾，你输了！";
            gotoxy(wide / 3 + 8, high * 3 / 5);
            system("pause");
            break;
        }
        if (snake->length == 1000)
        {
            system("cls");
            gotoxy(wide / 3 + 8, high / 3);
            cout << "恭喜你，你赢了！";
            gotoxy(wide / 3 + 8, high * 3 / 5);
            system("pause");
            break;
        }
        PrintSnake(snake);
        if (snake->x[snake->length] == food->x && snake->y[snake->length] == food->y)
        {
            EatFood(snake, food);
            PrintFood(snake, food);
        }
        if (speedup == 0) Sleep(300);
        else if (speedup == 1) Sleep(100);
    }
}

void CreateMap()
{
    for (int i = 0; i < wide; i += 2)
    {
        gotoxy(i, 0);
        cout << "◆";
        gotoxy(i, high - 1);
        cout << "◆";
    }
    for (int i = 0; i < high; i ++)
    {
        gotoxy(0, i);
        cout << "◆";
        gotoxy(wide - 2, i);
        cout << "◆";
    }
    gotoxy(0, high);
}

void gotoxy(short x, short y)
{
    COORD pos = { x, y };
    HANDLE hOut  = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos); 
}

void InitSnake(Snake *snake)
{
    snake->x[0] = wide / 5;
    snake->y[0] = high / 5;
    snake->length = 5;
    for (int i = 1; i <= snake->length; i++)
    {
        snake->x[i] = snake->x[i - 1] + 2;
        snake->y[i] = snake->y[i - 1];
    }
}

void PrintSnake(Snake *snake)
{
    gotoxy(snake->x[0], snake->y[0]);
    cout << "  ";
    for (int i = 1; i <= snake->length; i++)
    {
        gotoxy(snake->x[i], snake->y[i]);
        cout << "■";
    }
    gotoxy(0, high);
}

void MoveSnake(char op, Snake* snake)
{
    for (int i = 1; i <= snake->length; i++)
    {
        snake->x[i - 1] = snake->x[i];
        snake->y[i - 1] = snake->y[i];
    }
    switch (op)
    {
    case 'w': case 'W': case 72:
        snake->y[snake->length]--;
        break;
    case 's' : case 'S': case 80:
        snake->y[snake->length]++;
        break;
     case 'a': case 'A': case 75:
         snake->x[snake->length]-=2;
         break;
     case 'd': case 'D': case 77:
         snake->x[snake->length]+=2;
         break;
    }
}

bool check(unsigned char ch, unsigned char op)
{
    if (op != 's' && op != 'S' && op != 'w' && op != 'W' && op != 'a' && op != 'A' && 
        op != 'd' && op != 'D' && op != 72 && op != 75 && op != 77 && op!= 80) return 0;
    if ((ch == 'a' || ch == 'A') && (op == 'd' || op == 'D')) return 0;
    else if ((ch == 'w' || ch == 'W')&& (op == 's' || op == 'S')) return 0;
    else if ((ch == 'd' || ch == 'D') && (op == 'a' || op == 'A')) return 0;
    else if ((ch == 's' || ch == 'S') && (op == 'w' || op == 'W')) return 0;
    else if (ch == 72 && op == 80 || ch == 80 && op == 72) return 0;
    else if (ch == 75 && op == 77 || ch == 77 && op == 75) return 0;
    return 1;
}

void PrintFood(Snake* snake, Food * food)
{
    srand((unsigned)time(NULL));
    while (1)
    {
        int i = 0;
        food->x = rand() % ((wide - 6) / 2);
        food->y = rand() % (high - 6);
        if (food->x <= 2 || food->y <= 1 || food->x >= wide || food->y >= high || food->x %2 == 0) continue;
        for (i = 0; i <= snake->length; i++)
        {
            if (food->x == snake->x[i] && food->y == snake->y[i]) break;
        }
        if (i == snake->length + 1)
        {
            gotoxy(food->x, food->y);
            cout << "●";
            break;
        }
    }
}

void EatFood(Snake* snake, Food* food)
{
    snake->length++;
    for (int i = snake->length; i > 0; i--)
    {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }
    snake->x[0] = tailx;
    snake->y[0] = taily;
}

bool IsDead(Snake* snake)
{
    if (snake->x[snake->length] <= 0 || snake->x[snake->length] >= wide) return 1;
    if (snake->y[snake->length] <= 0 || snake->y[snake->length] >= high) return 1;
    for (int i = 0; i < snake->length; i++)
    {
        if (snake->x[snake->length] == snake->x[i] && 
            snake->y[snake->length] == snake->y[i]) return 1;
    }
    return 0;
}