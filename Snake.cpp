#include <iostream>
#include<cstdio>
#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<cmath>
#include<list>
#include <fstream>
#include<algorithm>
#include <string>
#define PI 3.14159265
const int MAX_NUM = 1000;//最大文件数字数
int rankList[MAX_NUM];//排行榜
const int sizeFont = 18;
const int WIDTH = 1280;			// 屏幕宽1024
const int HEIGHT = 720;			// 屏幕高576
const int MAPW = (WIDTH * 4);	// 地图宽
const int MAPH = (HEIGHT * 4);	// 地图高
int RADIUS = 15;
double directionx = 0;
double directiony = 100;
double Judgex = 0;
double Judgey = 100;
int grassSize=8;
char direction='w';
char Key;
int foodX;
int foodY;
int grassX;
int grassY;
int grass2X;
int grass2Y;
int grass3X;
int grass3Y;
int mineX;
int mineY;
int score = 0;
int Round = 1;//关卡
int growSpeed=50;
int snakeSpeed = 300;
int pd3 = 1;//游戏难度

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
int EndGame(link head, link end);
int FoodReach(link head, link end);
void CreateFood(link head, link end);
void SnakeAdd(link head, link end);
void CreateGrass(link head, link end);
int GrassReach(link head, link end);
void SnakeDelete(link head, link end);
void SnakeDeleteMine(link head, link end);
void CreateMine(link head, link end);
int MineReach(link head, link end);
void CreateGrass2(link head, link end);
int GrassReach2(link head, link end);
void GameSelect();
void GameSetting();
void GameHelp();
void SnakeDelete2(link head, link end);
void CreateGrass3(link head, link end);
void SnakeDelete3(link head, link end);
int GrassReach3(link head, link end);
void Rank();

int main()
{

    srand((unsigned)time(NULL));
    initgraph(WIDTH, HEIGHT);
    Init();
    _getch();
    MainMenu();
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
    int pd1 = 1;
    while(1)
    {
        int i = _getch();
        if (i == 119||i==87) { if (pd1 != 1)pd1--; }
        else if (i == 115||i==83) { if (pd1 != 4)pd1++; }
        else if (i == 13) { break; }
        else{}
        if (pd1 == 1) {
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4, 274, 42, &StartGame2, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 8, 274, 42, &SettingGame1, 0, 0);
        }
        else if (pd1 == 2) { 
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 8, 274, 42, &SettingGame2, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4, 274, 42, &StartGame1, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 274, 42, &HelpGame1, 0, 0);
        }
        else if (pd1 == 3) { 
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 274, 42, &HelpGame2, 0, 0); 
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 8, 274, 42, &SettingGame1, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4 + HEIGHT / 8, 274, 42, &QuitGame1, 0, 0);
        }
        else if (pd1 == 4) {
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4 + HEIGHT / 8, 274, 42, &QuitGame2, 0, 0);
            putimage(WIDTH / 8 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 274, 42, &HelpGame1, 0, 0);
        }
    }
//开始游戏
    if (pd1 == 1) { ModeSelect(); }
    if (pd1 == 2) { GameSetting(); }
    if (pd1 == 3) { GameHelp(); }
    if (pd1 == 4) { exit(0); }
}
void GameSetting()
{
    IMAGE SettingGame,SettingDifficulty, levelHigh1, levelHigh2, levelLow1, levelLow2, levelNormal1,levelNormal2;
    loadimage(&SettingGame, _T("set.png"));
    loadimage(&SettingDifficulty, _T("levelSet.png"));
    loadimage(&levelHigh1, _T("levelHigh1.png")); loadimage(&levelHigh2, _T("levelHigh2.png"));
    loadimage(&levelLow1, _T("levelLow1.png")); loadimage(&levelLow2, _T("levelLow2.png"));
    loadimage(&levelNormal1, _T("levelNormal1.png")); loadimage(&levelNormal2, _T("levelNormal2.png"));
    putimage(0, 0, WIDTH, HEIGHT, &SettingGame, 0, 0);
    putimage(WIDTH / 4, HEIGHT / 4, 264, 40, &SettingDifficulty, 0, 0);
    putimage(WIDTH / 5 + WIDTH / 10, HEIGHT / 4+ HEIGHT / 5, 87, 87, &levelLow1, 0, 0);
    putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelNormal1, 0, 0);
    putimage(WIDTH / 5 + WIDTH / 4+WIDTH/7, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelHigh1, 0, 0);
    if(pd3==1)putimage(WIDTH / 5 + WIDTH / 10, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelLow2, 0, 0);
    else if (pd3 == 2)putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelNormal2, 0, 0);
    else if (pd3 == 3)putimage(WIDTH / 5 + WIDTH / 4 + WIDTH / 7, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelHigh2, 0, 0);
    while (1)
    {
        int i = _getch();
        if (i == 65 || i == 97) { if (pd3 != 1)pd3--; }
        else if (i == 68 || i == 100) { if (pd3 != 3)pd3++; }
        else if (i == 13||i==27) { break; }
        else {}
        if (pd3 == 1) {
            putimage(WIDTH / 5 + WIDTH / 10, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelLow2, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelNormal1, 0, 0);
            snakeSpeed = 300; growSpeed = 50;
        }
        else if (pd3 == 2) {
            putimage(WIDTH / 5 + WIDTH / 10, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelLow1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelNormal2, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4 + WIDTH / 7, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelHigh1, 0, 0);
            snakeSpeed = 100; growSpeed = 15;
        }
        else if (pd3 == 3) {
            putimage(WIDTH / 5 + WIDTH / 10, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelLow1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelNormal1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4 + WIDTH / 7, HEIGHT / 4 + HEIGHT / 5, 87, 87, &levelHigh2, 0, 0);
            snakeSpeed = 50; growSpeed = 8;
        }
    }
    MainMenu();
}
void GameHelp()
{
    IMAGE HelpGame;
    loadimage(&HelpGame, _T("snakeRisk.png"));
    putimage(0, 0, WIDTH, HEIGHT, &HelpGame, 0, 0);
    char Key;
    while (1)
    {
        Key = _getch();
        if (Key == 13)
        {
            //-----------------------------------
            MainMenu();
        }
        else if (Key == 27)
        {
            MainMenu();
        }
    }
}
void GameSelect()
{
    
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
        char a=_getch();
        if (a == 13) 
        {
            RoundSelect();
            break;
        }else if(a==27)
        {
            MainMenu();
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
    int pd2 = 1;
    while(1)
    {
        
        int i = _getch();
        if (i == 119 || i == 87) { if (pd2 != 1)pd2--; }
        else if (i == 115 || i == 83) { if (pd2 != 3)pd2++; }
        else if (i == 13) { pd2 = 1; grassSize = 8; game(); }
        else if (i == 27) { pd2=1; ModeSelect(); }
        else{}
        if (pd2 == 1) {
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4, 102, 103, &Level1_2, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 102, 103, &Level2_1, 0, 0);
            Round = 1;
        }
        else if (pd2 == 2) {
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4, 102, 103, &Level1_1, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 4, 102, 103, &Level2_2, 0, 0);
            putimage(WIDTH / 5 + WIDTH / 4, HEIGHT / 4 + HEIGHT / 2, 102, 103, &Level3_1, 0, 0);
            Round = 2;
        }
        else if (pd2 == 3) {
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
    solidcircle(x - 7, y -1, 6); solidcircle(x + 7, y -1, 6);
    setfillcolor(BLACK);
    solidcircle(x - 7, y -1, 3); solidcircle(x + 7, y -1, 3);
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
    CreateFood(head, end);
    CreateGrass(head, end);
    if(Round>1)CreateGrass2(head, end);
    if(Round>2)CreateGrass3(head, end);
    CreateMine(head, end);
    outtextxy(1000, 360, L"分数：");
    while(1)
    {
        Sleep(snakeSpeed);
        ClearSnake(head, end);
        MoveSnake(head, end);
        if (_kbhit())
            Key = _getch();
        DirectionChange(Key);
        
        if (EndGame(head, end)) break;
        if(FoodReach(head,end))
        {
            SnakeAdd(head, end);
            score++;
        }
        if(GrassReach(head,end))
        {
            SnakeDelete(head, end); CreateGrass(head, end);
            score--;
            if (score < 0)break;
        }
        if (Round > 1) 
        {
            if (GrassReach2(head, end))
            {
                SnakeDelete2(head, end); CreateGrass2(head, end);
                score--;
                if (score < 0)break;
            }
        }
        if (Round > 2)
        {
            if (GrassReach3(head, end))
            {
                SnakeDelete3(head, end); CreateGrass3(head, end);
                score--;
                if (score < 0)break;
            }
        }
        if (rand() % growSpeed == 1) 
        {
            grassSize++; 
            setfillcolor(GREEN);
            solidcircle(grassX, grassY, grassSize);
            if(Round>1)solidcircle(grass2X, grass2Y, grassSize);
            if(Round>2)solidcircle(grass3X, grass3Y, grassSize);
        }
        if(MineReach(head,end))
        {
            if (score == 0)break;
            int i = score + 1;
            score /= 2;
            i /= 2;
            for(;i>0;i--)
            {
                SnakeDeleteMine(head, end);
            }
            CreateMine(head, end);
        }
        DrawSnake(head, end);
        char num[10];
        sprintf_s(num, "%d", score);
        outtextxy(1100,360,*num);
        
    }
    
    IMAGE GameOver;
    loadimage(&GameOver, _T("gameover.png"));
    putimage(0, 0, WIDTH, HEIGHT, &GameOver, 0, 0);
    Rank();
    _getch();

    MainMenu();
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
    link q=end;
    while(q->last!=head)
    {
        q->x = q->last->x;
        q->y = q->last->y;
        q = q->last;
    }
        if(direction=='w')p->y -= RADIUS;
        else if (direction == 's')p->y += RADIUS;
        else if (direction == 'a')p->x -= RADIUS;
        else if (direction == 'd')p->x += RADIUS;
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
int EndGame(link head, link end)
{
    link p = head->next;
    double distance;
    if (p->x < RADIUS || p->y < RADIUS || p->x>925 || p->y>720 - RADIUS) { return 1; }
    p = p->next;
    while(p!=end)
    {        
        distance = fabs(head->next->x - p->x) * fabs(head->next->x - p->x) + fabs(head->next->y - p->y) * fabs(head->next->y - p->y);
        if (distance < (double)RADIUS*2) { return 1; }
        p = p->next;
    }
    return 0;
}
void CreateFood(link head,link end)
{
    link p = head;
    do
    {
        foodY = rand() % 500 + 50;
        foodX = rand() % 500 + 50;
    } while (FoodReach(head, end));
    setfillcolor(LIGHTRED);
    solidcircle(foodX, foodY, RADIUS/2);
}
int FoodReach(link head, link end)
{
    link p = head->next;
    double distance;
    while (p != end)
    {
        distance = fabs(p->x - foodX) * fabs(p->x - foodX) + fabs(p->y - foodY) * fabs(p->y - foodY);
        if (distance < (double)RADIUS * (double)RADIUS+165) { return 1; }
        p = p->next;
    }
    return 0;
}
void SnakeAdd(link head,link end)
{
    link body, p;
    body = (link)malloc(sizeof(snake));
    body->isHead = 0;
    p = end->last;
    p->next = body; body->next = end;
    end->last = body; body->last = p;
    body->x = foodX; body->y = foodY;
    setfillcolor(WHITE);
    solidcircle(foodX, foodY, RADIUS / 2);
    CreateFood(head, end);
}
void CreateGrass(link head,link end)
{
    srand((unsigned)time(NULL));
    link p = head;
    do
    {
        grassX = rand() % 820 + 50;
        grassY = rand() % 640 + 50;
    } while (GrassReach(head, end));
    setfillcolor(GREEN);
    solidcircle(grassX, grassY, grassSize);
}
void CreateGrass2(link head, link end)
{
    link p = head;
    do
    {
        grass2X = rand() % 820 + 50;
        grass2Y = rand() % 640 + 50;
    } while (GrassReach2(head, end));
    setfillcolor(GREEN);
    solidcircle(grass2X, grass2Y, grassSize);
}
void CreateGrass3(link head, link end)
{
    link p = head;
    do
    {
        grass3X = rand() % 820 + 50;
        grass3Y = rand() % 640 + 50;
    } while (GrassReach2(head, end));
    setfillcolor(GREEN);
    solidcircle(grass3X, grass3Y, grassSize);
}
void SnakeDelete(link head,link end)
{
    link p = end->last->last, q = end->last;
    p->next = end;
    end->last = p;
    DrawBlank(q->x, q->y);
    setfillcolor(WHITE);
    solidcircle(grassX, grassY, grassSize);
    free(q);
}
void SnakeDelete2(link head, link end)
{
    link p = end->last->last, q = end->last;
    p->next = end;
    end->last = p;
    DrawBlank(q->x, q->y);
    setfillcolor(WHITE);
    solidcircle(grass2X, grass2Y, grassSize);
    free(q);
}
void SnakeDelete3(link head, link end)
{
    link p = end->last->last, q = end->last;
    p->next = end;
    end->last = p;
    DrawBlank(q->x, q->y);
    setfillcolor(WHITE);
    solidcircle(grass3X, grass3Y, grassSize);
    free(q);
}
int GrassReach(link head, link end)
{
    link p = head->next;
    double distance;
    while (p != end)
    {
        distance = fabs(p->x - grassX) * fabs(p->x - grassX) + fabs(p->y - grassY) * fabs(p->y - grassY);
        distance = sqrt(distance);
        if (distance <(double)RADIUS+1 + grassSize) { return 1; }
        p = p->next;
    }
    return 0;
}
int GrassReach2(link head, link end)
{
    link p = head->next;
    double distance;
    while (p != end)
    {
        distance = fabs(p->x - grass2X) * fabs(p->x - grass2X) + fabs(p->y - grass2Y) * fabs(p->y - grass2Y);
        distance = sqrt(distance);
        if (distance <(double)RADIUS+1 + grassSize) { return 1; }
        p = p->next;
    }
    return 0;
}
int GrassReach3(link head, link end)
{
    link p = head->next;
    double distance;
    while (p != end)
    {
        distance = fabs(p->x - grass3X) * fabs(p->x - grass3X) + fabs(p->y - grass3Y) * fabs(p->y - grass3Y);
        distance = sqrt(distance);
        if (distance < (double)RADIUS + 1 + grassSize) { return 1; }
        p = p->next;
    }
    return 0;
}
void CreateMine(link head, link end)
{
    link p = head;
    do
    {
        mineY = rand() % 500 + 50;
        mineX = rand() % 500 + 50;
    } while (FoodReach(head, end));
    setfillcolor(BLACK);
    solidcircle(mineX, mineY, RADIUS / 2);
}
int MineReach(link head, link end)
{
    link p = head->next;
    double distance;
    while (p != end)
    {
        distance = fabs(p->x - mineX) * fabs(p->x - mineX) + fabs(p->y - mineY) * fabs(p->y - mineY);
        if (distance < (double)RADIUS * (double)RADIUS + 165) { return 1; }
        p = p->next;
    }
    return 0;
}
void SnakeDeleteMine(link head, link end)
{
    try {
        link p = end->last->last, q = end->last;
        p->next = end;

        end->last = p;
        DrawBlank(q->x, q->y);
        setfillcolor(WHITE);
        solidcircle(mineX, mineY, RADIUS / 2);
        free(q);
    }
    catch (double) { MainMenu(); }
}
void Rank()
{
    using namespace std;
    int total=0;
    ofstream fout("rank.txt", ios::out);
    int x;
    for (int i = 0; i < 6; i++) { fout << rankList[i]; fout << ' '; }
    if (score > rankList[6])rankList[6] = score;
    sort(rankList, rankList + 6);
    ifstream fin("rank.txt", ios::in);
    for (int i = 0; i < 6; i++) { fin >> rankList[i]; }
    outtextxy(640, 200, *rankList);
    fout.close();
}