#include <iostream>
#include<cstdio>
#include<graphics.h>
#include<conio.h>
#include<cstdlib>
#include<windows.h>

const int sizeFont = 18;
const int WIDTH = 1280;			// 屏幕宽1024
const int HEIGHT = 720;			// 屏幕高576
const int MAPW = (WIDTH * 4);	// 地图宽
const int MAPH = (HEIGHT * 4);	// 地图高

int Round = 1;//关卡

IMAGE		Map(MAPW, MAPH);
class Snake
{
public:
    IMAGE BODY, HEAD,BLANK;
    int speed=500;
    struct node
    {
        int x;
        int y;
        struct node* next;
        struct node* previous;
        IMAGE UNIT;
    };
    struct node* head;
    struct node* tail;  
    Snake()
    {
        loadimage(&BLANK, _T("BLANK.png"));
        loadimage(&BODY, _T("SnakeUnit.png"));
        loadimage(&HEAD, _T("SnakeHead.png"));
    }
    void Setspeed(int temp) { speed = temp; }
    void InitNode()
    {
        if(head!=NULL)
        {
            tail = tail->next;
            for(;tail!=NULL;tail=tail->next)
            {
                free(tail->previous);
                tail->previous = NULL;
            }
        }
 //       struct node* head = NULL;
 //       struct node* tail = NULL;
 //       head = (struct node*)malloc(sizeof(struct node));
 //       tail = (struct node*)malloc(sizeof(struct node));
        struct node* head = new node;
        struct node* tail = new node;
        head->next = NULL;
        head->previous = tail;
        tail->next = head;
        tail->previous = NULL;
        head->UNIT = HEAD;
        tail->UNIT = BODY;
        head->x = WIDTH / 3; head->y = HEIGHT / 2;
        tail->x = head->x; tail->y = head->y+55;
        struct node* temp = new node;
        temp->x = 300; temp->y = 300;
        while (1) {
            if(head->y%100==0)
            {
                struct node* p4 = new node;
                head->next = p4; p4->previous = head; p4->next = NULL;
                p4->x = head->x; p4->y = head->y - 55; p4->UNIT = HEAD;
                head->UNIT = BODY; head = p4;
            }
            if(head->y%200==0)
            {
                head = head->previous; head->UNIT = HEAD;
                delete head->next; head->next = NULL;
            }
            struct node* p2 = head;
            while (p2->previous != NULL)p2 = p2->previous;
            struct node* p1 = head;
            while(p1->previous!=NULL)
            {
                putimage(p1->x, p1->y, 130, 130, &(p1->UNIT), 0, 0);
                p1 = p1->previous;
            }putimage(p1->x, p1->y, 130, 130, &(p1->UNIT), 0, 0);
            Sleep(20);
            putimage(temp->x, temp->y, 130, 130, &BLANK, 0, 0);
            temp->x = p1->x; temp->y = p1->y;
            struct node* p3 = head;
            for(;p3->previous!=NULL;p3=p3->previous)
            {
                p3->y -= 1;
            }p3->y -= 1;
        }
    }
    void NewNode()
    {
        struct node* p1 = (struct node*)malloc(sizeof(struct node));
        p1->next = head; p1->previous = head->previous->previous; head->previous = p1;
        p1->x = tail->x; p1->y = tail->y; p1->UNIT = BODY;
    }
    void DeleteNode()
    {
        struct node* p1=head;
        while (p1->previous != NULL) { p1 = p1->previous; }
        delete p1;
    }
 /*   void PrintSnake()
    {
        struct node *p2 = tail;
//        loadimage(&BLANK, _T("BLANK.png"));
//        loadimage(&BODY, _T("SnakeUnit.png"));
//        loadimage(&HEAD, _T("SnakeHead.png"));

        putimage(p2->x, p2->y, 130, 130, &BLANK, 0, 0);
        struct node *p1 = head;
        for(;p1->previous!=NULL;p1=p1->previous)
        {
            putimage(p1->x, p1->y, 130, 130, &(p1->UNIT), 0, 0);
        }
    }
*/
    void MoveTest()
    {
        Sleep(speed);
        head->x += 50;
    }
};
void DrawMap();
void Init();
void MainMenu();
void ModeSelect();
void RoundSelect();
void game();
Snake::node tail;
int main()
{

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
void game()
{   
    Snake Colwaer;
    DrawMap();
    Colwaer.InitNode();
}