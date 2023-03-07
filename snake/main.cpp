#include"snake.h"

int main()
{
    ch = 80;
    system("mode con cols=100 lines=36");
    Welcome();
    int num;
    cin >> num;
    switch (num)
    {
    case 1:
        system("cls");
        StartGame();
        break;
    case 2:
        exit(0);
        break;
    case 3:
        system("cls");
        Explanation();
        break;
    }
    main();
    return 0;
}