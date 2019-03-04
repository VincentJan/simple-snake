#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

char b[100][41];
int flag = 1;
int number = 5;
int locnum = 0;
int timer = 100;
int score = 0;

struct location {
	int sta;
	int x1;
	int y1;
	int flag;
};

struct bodys {
	int statu;
	int x2;
	int y2;
};

struct bodys body[1000];
struct location loc[10000];

void init();
void refresh();
void move();
void play();
void food();
void eatfood();

int main()
{
	printf("简易的贪吃蛇，方向键控制，按任意键开始。\n");
	getchar();
	init();
	play();
	system("cls");
	printf("You die!\n""Your score is: %d\n", score);
	getchar();
	return 0;
}

void init()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
	system("mode con cols=100 lines=42");
	for (int y = 0; y <= 40; y++)
	{
		for (int x = 0; x <= 99; x++)
		{
			b[x][y] = ' ';
			if (x == 0 || x == 99 || y == 0 || y == 40)
			{
				b[x][y] = '#';
			}
			printf("%c", b[x][y]);
		}
		printf("\n");
	}
	for (int a = 0; a < number; a++)
	{
		body[a].statu = 1;
		body[a].x2 = 40 - a * 2;
		body[a].y2 = 20;
		if (a == 0)
		{
			b[body[a].x2][body[a].y2] = '@';
		}
		else
		{
			b[body[a].x2][body[a].y2] = '0';
		}
	}	
	for (int b = 0; b < 10000; b++)
	{
		loc[b].flag = 0;
	}
	body[0].statu = 1;
}

void refresh()
{
	int f = 0;
	system("cls");
	for (int y = 0; y <= 40; y++)
	{
		for (int x = 0; x <= 99; x++)
		{
			printf("%c", b[x][y]);
		}
		printf("\n");
	}
}

void move(int bo) 
{
	switch(body[bo].statu)
	{
	case 1: 
		if (b[body[bo].x2 + 2][body[bo].y2] != ' ' && b[body[bo].x2 + 2][body[bo].y2] != '$')
		{
			flag = 0;
			break;
		}   //判定死亡
		b[body[bo].x2 + 2][body[bo].y2] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		body[bo].x2++;
		body[bo].x2++;
		if (b[body[bo].x2 + 2][body[bo].y2] == '$')
		{
			eatfood();
		}
		break;
	case 2:
		if (b[body[bo].x2][body[bo].y2 +1] != ' ' && b[body[bo].x2][body[bo].y2 + 1] != '$')
		{
			flag = 0;
			break;
		}
		b[body[bo].x2][body[bo].y2 + 1] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		body[bo].y2++;
		if (b[body[bo].x2][body[bo].y2 + 1] == '$')
		{
			eatfood();
		}
		break;
	case 3:
		if (b[body[bo].x2 - 2][body[bo].y2] != ' ' && b[body[bo].x2 - 2][body[bo].y2] != '$')
		{
			flag = 0;
			break;
		}
		b[body[bo].x2 - 2][body[bo].y2] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		body[bo].x2--;
		body[bo].x2--;
		if (b[body[bo].x2 - 2][body[bo].y2] == '$')
		{
			eatfood();
		}
		break;
	case 4:
		if (b[body[bo].x2][body[bo].y2 -1] != ' ' && b[body[bo].x2][body[bo].y2 - 1] != '$')
		{
			flag = 0;
			break;
		}
		b[body[bo].x2][body[bo].y2 - 1] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		body[bo].y2--;
		if (b[body[bo].x2][body[bo].y2 - 1] == '$')
		{
			eatfood();
		}
		break;
	}
}

void play()
{
	while (flag)
	{
		if (GetAsyncKeyState(VK_UP) && body[0].statu != 2)
		{
			body[0].statu = 4;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		else if (GetAsyncKeyState(VK_DOWN) && body[0].statu != 4)
		{
			body[0].statu = 2;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		else if (GetAsyncKeyState(VK_LEFT) && body[0].statu != 1)
		{
			body[0].statu = 3;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && body[0].statu != 3)
		{
			body[0].statu = 1;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		refresh();
		for (int a = 1; a < number; a++)
		{
			for (int b = 0; b < 10000; b++)
			{
				if (loc[b].flag)
				{
					if (loc[b].x1 == body[a].x2 && loc[b].y1 == body[a].y2)
					{
						body[a].statu = loc[b].sta;
						if (a == number - 1)
						{
							loc[b].flag = 0;
						}
					}
				}
			}
		}
		Sleep(200);
		for (int m = 0; m < number; m++)
		{
			move(m);
		}
		if (timer == 100)
		{
			food();
			timer = 0;
		}
		else
		{
			timer++;
		}
	}
}

void food()
{
	srand(time(NULL));
	int flag = 1;
	for (int y = 0; y <= 40; y++)
	{
		for (int x = 0; x <= 99; x++)
		{
			if (b[x][y] == '$')
			{
				b[x][y] = ' ';
			}
		}
	}
	while (flag)
	{
		int x3 = (rand() % 98) + 1;
		int y3 = (rand() % 39) + 1;
		if ((b[x3][y3] == ' ' || b[x3][y3] == '$') && x3%2 == 0)
		{
			b[x3][y3] = '$';
			flag = 0;
		}
	}
}

void eatfood()
{
	switch (body[number - 1].statu)
	{
	case 1:
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2 - 2;
		body[number].y2 = body[number - 1].y2;
		b[body[number].x2][body[number].y2] = '0';
		number++;
		break;
	case 2:
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2;
		body[number].y2 = body[number - 1].y2 - 1;
		b[body[number].x2][body[number].y2] = '0';
		number++;
		break;
	case 3:
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2 + 2;
		body[number].y2 = body[number - 1].y2;
		b[body[number].x2][body[number].y2] = '0';
		number++;
		break;
	case 4:
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2;
		body[number].y2 = body[number - 1].y2 + 1;
		b[body[number].x2][body[number].y2] = '0';
		number++;
		break;
	}
	food();
	score++;
}
