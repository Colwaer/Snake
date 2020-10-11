#include <iostream>
#include<cstdio>
#include<graphics.h>
#include<conio.h>

const int sizeFont = 18;

const int WIDTH = 1280;			// 屏幕宽1024
const int HEIGHT = 720;			// 屏幕高576
const int MAPW = (WIDTH * 4);	// 地图宽
const int MAPH = (HEIGHT * 4);	// 地图高

IMAGE		Map(MAPW, MAPH);

void DrawMap(int x1, int y1, int x2, int y2);
void Init();

int main()
{
    initgraph(WIDTH, HEIGHT);
    Init();
    _getch();

    _getch();
    closegraph();
    return 0;
}
void DrawMap(int x1,int y1,int x2,int y2)
{
    COLORREF backgroundColor=(50, 2, 50);
    loadimage(&Map, _T("game.png"));
    setbkcolor(LIGHTBLUE);
    putimage(0, 0, WIDTH, HEIGHT, &Map, 0, 0);  
}
void Init()
{
    setbkcolor(WHITE);
    IMAGE StartBK(WIDTH,HEIGHT);
    loadimage(&StartBK, _T("开始界面.png"));
    putimage(0, 0, WIDTH, HEIGHT, &StartBK, 0, 0);
    settextstyle(sizeFont*2, sizeFont, L"楷体");
    settextcolor(0xFFB6C1);
    outtextxy(WIDTH / 2-100, HEIGHT / 2+250, L"按任意键继续");
}
void MainMenu()
{

}