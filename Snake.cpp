#include <iostream>
#include<cstdio>
#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<cmath>
#include<list>
#define PI 3.14159265
const int sizeFont = 18;
const int WIDTH = 1280;			// 屏幕宽1024
const int HEIGHT = 720;			// 屏幕高576
const int MAPW = (WIDTH * 4);	// 地图宽
const int MAPH = (HEIGHT * 4);	// 地图高
const int RADIUS = 15;
double directionx = 0;
double directiony = 100;
double Judgex = 0;
double Judgey = 100;
char direction='w';
char Key;
int Round = 1;//关卡
typedef struct SNAKE
{
    int x, y;
    bool isHead;
    struct SNAKE* next;
    struct SNAKE* last;
}snake,*link;
link head, end;
COLORREF BodyBlue = RGB(0, 191, 255);
IMAGE		Map(MAPW, MAPH);
void DrawMap();
void Init();
void MainMenu();
void ModeSelect();
void RoundSelect();
void game();
void DrawBody(int x, int y);
void DrawHead(int x, int y);
void DrawBlank(int x, int y);
void InitNode();
void InitSnake(link head, link end);
void DrawSnake(link head, link end);
void MoveSnake(link head, link end);
void ClearSnake(link head, link end);
void DirectionChange(char InputKey);
void EndGame(link head, link end);

int main()
{
    srand((unsigned)time(NULL));
    initgraph(WIDTH, HEIGHT);
    Init();
    _getch();
    int pd = 0;
    MainMenu();
    game();
    _getch();
    closegraph();
    return 0;
}
void DrawMap()
{
    COLORREF backgroundColor=(50, 2, 50);
    loadimage(&Map, _T("game.png"));
    putimage(0, 0, WIDTH, HEIGHT, &Map, 0, 0);  

}
void Init()
{
    setbkcolor(WHITE);
    IMAGE StartBK(WIDTH,HEIGHT);
    loadimage(&StartBK, _T("开始界面.png"));
    putimage(0, 0, WIDTH, HEIGHT, &StartBK, 0, 0);
    settextstyle(sizeFont*2, sizeFont, L"楷体");
    COLORREF TextColor;
    TextColor = { 0XFFEFD1 };
    settextcolor(TextColor);
    outtextxy(WIDTH / 2-WIDTH/12, HEIGHT / 2+HEIGHT/3, L"按任意键继续");
}
void MainMenu()

{
    
    IMAGE MainMenuBK(WIDTH, HEIGHT);
    loadimage(&MainMenuBK, _T("MainMenuBK.png"));
    putimage(0, 0, WIDTH, HEIGHT, &MainMenuBK, 0, 0);
    IMAGE StartGame1, HelpGame1, QuitGame1,SettingGame1, StartGame2, HelpGame2, QuitGame2, SettingGame2;
    loadimage(&StartGame1, _T("开始游戏1.png"));
    loadimage(&HelpGame1, _T("帮助游戏1.png"));
    loadimage(&QuitGame1, _T("退出游戏1.png"));
    loadimage(&SettingGame1, _T("游戏设置1.png"));
    loadimage(&StartGame2, _T("开始游戏2.png"));
    loadimage(&HelpGame2, _T("帮助游戏2.png"));
    loadimage(&QuitGame2, _T("退出游戏2.png"));
    loadimage(&SettingGame2, _T("游戏设置2.png"));
    putimage(WIDTH/8+WIDTH/4,HEIGHT / 4, 274, 42, &StartGame2, 0, 0);
    putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4+HEIGHT/8, 274, 42, &SettingGame1, 0, 0);
    putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4+HEIGHT/4, 274, 42, &HelpGame1, 0, 0);
    putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4+HEIGHT/4+HEIGHT/8, 274, 42, &QuitGame1, 0, 0);
//开始界面及准备
    int pd = 1;
    while(1)
    {
        int i = _getch();
        if (i == 119||i==87) { if (pd != 1)pd--; }
        else if (i == 115||i==83) { if (pd != 4)pd++; }
        else if (i == 13) { break; }
        else{}
        if (pd == 1) {
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4, 274, 42, &StartGame2, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 8, 274, 42, &SettingGame1, 0, 0);
        }
        else if (pd == 2) { 
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 8, 274, 42, &SettingGame2, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4, 274, 42, &StartGame1, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 274, 42, &HelpGame1, 0, 0);
        }
        else if (pd == 3) { 
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 274, 42, &HelpGame2, 0, 0); 
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 8, 274, 42, &SettingGame1, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4 + HEIGHT / 8, 274, 42, &QuitGame1, 0, 0);
        }
        else if (pd == 4) {
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4 + HEIGHT / 8, 274, 42, &QuitGame2, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 274, 42, &HelpGame1, 0, 0);
        }
    }
//第一层UI界面
    if (pd == 1) { ModeSelect(); return; }
//第二层UI界面
}
void ModeSelect()
{
    IMAGE gameChose(WIDTH, HEIGHT);
    loadimage(&gameChose, _T("gameChose.png"));
    putimage(0, 0, WIDTH, HEIGHT, &gameChose, 0, 0);
    IMAGE RoundMode;
    loadimage(&RoundMode, _T("chose2_1.png"));
    putimage(WIDTH/8 + WIDTH / 4, HEIGHT / 3, 297, 74, &RoundMode, 0, 0);
    while(1)
    {
        if (_getch() == 13) 
        {
            RoundSelect();
            break;
        }
    }
}
void RoundSelect()
{
    IMAGE RoundSelect;
    loadimage(&RoundSelect, _T("MainMenuBK.png"));
    putimage(0, 0, WIDTH, HEIGHT, &RoundSelect, 0, 0);
    IMAGE Level1_1, Level1_2, Level2_1, Level2_2, Level3_1, Level3_2;
    loadimage(&Level1_1, _T("Level1_3.png"));
    loadimage(&Level1_2, _T("Level1_2.png"));
    loadimage(&Level2_1, _T("Level2_3.png"));
    loadimage(&Level2_2, _T("Level2_2.png"));
    loadimage(&Level3_1, _T("Level3_3.png"));
    loadimage(&Level3_2, _T("Level3_2.png"));
    putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4, 102, 103, &Level1_2, 0, 0);
    putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4+ HEIGHT / 4, 102, 103, &Level2_1, 0, 0);
    putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4+ HEIGHT / 2, 102, 103, &Level3_1, 0, 0);
    int pd = 1;
    while(1)
    {
        int i = _getch();
        if (i == 119 || i == 87) { if (pd != 1)pd--; }
        else if (i == 115 || i == 83) { if (pd != 3)pd++; }
        else if (i == 13) { break; }
        else {}
        if (pd == 1) {
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4, 102, 103, &Level1_2, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 102, 103, &Level2_1, 0, 0);
            Round = 1;
        }
        else if (pd == 2) {
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4, 102, 103, &Level1_1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 102, 103, &Level2_2, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 2, 102, 103, &Level3_1, 0, 0);
            Round = 2;
        }
        else if (pd == 3) {
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4, 102, 103, &Level1_1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 102, 103, &Level2_1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 2, 102, 103, &Level3_2, 0, 0);
            Round = 3;
        }
    }

}
void DrawBody(int x, int y)
{
    setfillcolor(BodyBlue);
    solidcircle(x, y, RADIUS);
}
void DrawHead(int x, int y)
{
    setfillcolor(BodyBlue);
    solidcircle(x, y, RADIUS);
    setfillcolor(WHITE);
    solidcircle(x - 7, y - 4, 6); solidcircle(x + 7, y - 4, 6);
    setfillcolor(BLACK);
    solidcircle(x - 7, y - 4, 3); solidcircle(x + 7, y - 4, 3);
}
void DrawBlank(int x, int y)
{
    setfillcolor(WHITE);
    solidcircle(x, y, RADIUS);
} 
void game()
{      
    DrawMap(); 
    InitNode();
    InitSnake(head,end);
    DrawSnake(head, end);
    while(1)
    {
        Sleep(10);
        ClearSnake(head, end);
        MoveSnake(head, end);
        if (_kbhit())
            Key = _getch();
        DirectionChange(Key);
        EndGame(head, end);

        DrawSnake(head, end);       
    }
    _getch();
}
void InitNode()
{
    head = (link)malloc(sizeof(snake));
    end = (link)malloc(sizeof(snake));
    head->last = NULL;
    head->next = end;
    end->last = head;
    end->next = NULL;
}
void InitSnake(link head,link end)
{
    link body1 = (link)malloc(sizeof(snake));
    head->next = body1; body1->next = end;
    end->last = body1; body1->last = head;
    body1->x = 320; body1->y = 360; body1->isHead = 1;

}
void DrawSnake(link head, link end)
{
    link p = head->next;
    while(p!=end)
    {
        if (p->isHead)DrawHead(p->x, p->y);
        else DrawBody(p->x, p->y);
        p = p->next;
    }
}
void MoveSnake(link head,link end)
{
    link p = head->next;
    while (p != end)
    {
        if(direction=='w')p->y -= 1;
        else if (direction == 's')p->y += 1;
        else if (direction == 'a')p->x -= 1;
        else if (direction == 'd')p->x += 1;
        p = p->next;
    }
}
void ClearSnake(link head, link end)
{
    link p = head->next;
    while (p != end)
    {
        DrawBlank(p->x, p->y);
        p = p->next;
    }
}
void DirectionChange(char InputKey)
{
/*    if (InputKey == 'w') { Judgex = 0; Judgey = 100; }
    else if (InputKey == 's') { Judgex = 0; Judgey = -100; }
    else if (InputKey == 'a') { Judgex = -100; Judgey = 0; }
    else if (InputKey == 'd') { Judgex = 100; Judgey = 0; }    
    double degree = (directionx * Judgex + directiony * Judgey) / (sqrt(directionx * directionx + directiony * directiony) * sqrt(Judgex * Judgex + Judgey * Judgey));
    double sindegree = 1 - degree * degree;
    if(degree>-1/2)
    {
        degree = fabs(degree);
        if (InputKey == 'w') { if (directionx >= 0) { directionx += degree * 10; directiony -= sindegree * 10; } else { directionx -= degree * 10; directiony -= sindegree * 10; } }
        if (InputKey == 's') { if (directionx >= 0) { directionx += degree * 10; directiony += sindegree * 10; } else { directionx -= degree * 10; directiony += sindegree * 10; } }
        if (InputKey == 'a') { if (directiony >= 0) { directionx += degree * 10; directiony += sindegree * 10; } else { directionx -= degree * 10; directiony += sindegree * 10; } }
    }
    */
    if (InputKey == 'w') { if (direction != 's')direction = 'w'; }
    else if (InputKey == 's') { if (direction != 'w')direction = 's'; }
    else if (InputKey == 'a') { if (direction != 'd')direction = 'a'; }
    else if (InputKey == 'd') { if (direction != 'a')direction = 'd'; }
}
void EndGame(link head, link end)
{
    link p = head->next;
    if (p->x < RADIUS || p->y < RADIUS || p->x>930 || p->y>720 - RADIUS) { _getch(); }
}