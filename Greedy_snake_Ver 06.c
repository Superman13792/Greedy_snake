#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#define X 29
#define Y 29 //��ͼ��С
int block[X][Y];
int direction = 4; //�ߵķ��� 8546 wsad
int snake_long = 0; //������
int game_continue = 1; //��Ϸ�Ƿ���� 0�� 1��
int refresh_frequency = 500; //����ˢ��Ƶ�� ��λ����

//���º����ɹ�����2 
//-2   -1   0    1
//ʳ�� ǽ�� �հ� ��
int return_random_x(void)
{
	int random, m = 0, n = X;//m<n
	srand((int)time(NULL));
	random = rand() % (n - m + 1) + m;
	return random;
}
int return_random_y(void)
{
	int random, m = 0, n = Y;//m<n
	srand((int)time(NULL));
	random = rand() % (n - m + 1) + m;
	return random;
}
int random_direction(void)
{
	int random, m = 1, n = 4;//m<n
	srand((int)time(NULL));
	random = rand() % (n - m + 1) + m;
	if (random == 1)
		direction = 4;
	else if (random == 2)
		direction = 5;
	else if (random == 3)
		direction = 6;
	else if (random == 4)
		direction = 8;
	else;
	return 2;
}
int create_block(int x, int y,int kind) //��������
{
	block[x][y] = kind;
	return 2;
}
int create_line(int x1, int y1, int x2, int y2, int kind) //��������
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 0; i <= (y2 - y1); i++)
				create_block(x1, y1 + i, kind);
		}
		else if (y1 > y2)
		{
			for (i = 0; i <= (y1 - y2); i++)
				create_block(x1, y2 + i, kind);
		}
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			for (i = 0; i <= (x2 - x1); i++)
				create_block(x1 + i, y1, kind);
		}
		else if (x1 > x2)
		{
			for (i = 0; i <= (x1 - x2); i++)
				create_block(x2 + i, y1, kind);
		}
	}
	return 2;
}
int create_wall(void) //����ǽ
{
	create_line( 0, 0, X - 1, 0, -1);
	create_line( X - 1, 0, X - 1, Y - 1, -1);
	create_line( 0, 0, 0, Y - 1, -1);
	create_line( 0, Y - 1, X - 1, Y - 1, -1);
	return 2;
}
int create_snake(void)
{
	int x , y ;
	recreaterandom:
	x = return_random_x();
	y = return_random_y();
	if (block[x][y] == 0)
	{
		create_block(x, y, 1);
		snake_long = snake_long + 1;
	}
	else goto recreaterandom;
	return 2;
}
int create_food(void) 
{
	int x, y;
	recreaterandom:
	x = return_random_x();
	y = return_random_y();
	if (block[x][y] == 0)
	{
		create_block(x, y, -2);
	}
	else goto recreaterandom;
	return 2;
}
int out_put_information(void)
{
	printf("�ߵķ���:%d ", direction);
	printf("��ĵ÷�:%d ", snake_long-1);
	return 2;
}
int Z_engine_start(void) //�������� ��䷽�� 
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //�����
		for (x = 0; x <= X - 1; x++) //�����
			create_block(x, y, 0);
	return 2;
}
int Z_engine_redraw(void) //�ػ�
{
	int x, y;
	system("cls");
	for (y = 0; y <= Y - 1; y++) //������
	{
		for (x = 0; x <= X - 1; x++) //������
		{
			if (block[x][y] == 0) //�հ�
				printf("%s", "  ");
			else if (block[x][y] == -1) //ǽ
				printf("%s", "��");
			else if (block[x][y] == -2) //ʳ��
				printf("%s", "��");
			else if (block[x][y] >0) //��
				printf("%s", "��");
			else;
		}
		putchar('\n');
	}
	out_put_information();
	return 2;
}
int monitor_button(void) //��ⰴ�� 
{
	char button;
	if (kbhit() == 1) //����
	{
		button = getch();
		if (button == 'w' || button == 'W')
		{
			if (direction == 5);
			else direction = 8;
		}
		else if (button == 's' || button == 'S')
		{
			if (direction == 8);
			else direction = 5;
		}
		else if (button == 'a' || button == 'A')
		{
			if (direction == 6);
			else direction = 4;
		}
		else if (button == 'd' || button == 'D')
		{
			if (direction == 4);
			else direction = 6;
		}
		else;
	}
	else;
	return 2;
}
int snake_long_reset(void)
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //�����
	{
		for (x = 0; x <= X - 1; x++) //�����
		{
			if (block[x][y] > 0) //��⵽��
				block[x][y] = block[x][y] + 1; //kind+1
			else;
		}
	}
	return 2;
}
int game_over(void) //��Ϸ����
{
	game_continue = 0;
	system("color 40");
	printf("   YOU LOST!");
	return 2;
}
int delete_snake_tali(void)
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //�����
	{
		for (x = 0; x <= X - 1; x++) //�����
		{
			if (block[x][y] == snake_long+1)
				block[x][y] = 0;
		}
	}
	return 2;
}
int move_block(void) //�ƶ����� 
{
	int x, y;
	for (y = 0; y <= Y - 1 && game_continue == 1; y++) //��
	{
		for (x = 0; x <= X - 1 && game_continue == 1; x++) //��
		{
			if (block[x][y] == 1) //�ҵ���ͷ
			{
				if (direction == 8)
				{
					if (block[x][y - 1] == -1) //ײ��ǽ
						goto miao;
					else if (block[x][y - 1] == -2) //�Ե�ʳ��
					{
						snake_long_reset();
						create_block(x, y - 1, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x][y - 1] >0) //ײ���Լ�
						goto miao;
					else //��������
					{
						snake_long_reset();
						create_block(x, y - 1, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else if (direction == 5)
				{
					if (block[x][y + 1] == -1) //ײ��ǽ
						goto miao;
					else if (block[x][y + 1] == -2) //�Ե�ʳ��
					{
						snake_long_reset();
						create_block(x, y + 1, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x][y + 1] >0) //ײ���Լ�
						goto miao;
					else //��������
					{
						snake_long_reset();
						create_block(x, y + 1, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else if (direction == 4)
				{
					if (block[x-1][y] == -1) //ײ��ǽ
						goto miao;
					else if (block[x - 1][y] == -2) //�Ե�ʳ��
					{
						snake_long_reset();
						create_block(x - 1, y, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x - 1][y] >0) //ײ���Լ�
						goto miao;
					else
					{
						snake_long_reset();
						create_block(x - 1, y, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else if (direction == 6)
				{
					if (block[x+1][y]== -1) //ײ��ǽ
						goto miao;
					else if (block[x + 1][y] == -2) //�Ե�ʳ��
					{
						snake_long_reset();
						create_block(x+1, y, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x + 1][y] >0) //ײ���Լ�
						goto miao;
					else
					{
						snake_long_reset();
						create_block(x + 1, y, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else;
			}
			else;
		}
	}
	wang:
	return 2;
	miao:
	game_continue = 0;
}
int main(void)
{
	system("mode con cols=58 lines=30");
	system("color 9e");
	system("title=̰���� v7.0 ���߸��汾���������... ����������!!!!");
	Z_engine_start();
	create_wall();
	create_snake();
	create_food();
	random_direction();
	for (; game_continue == 1;)
	{
		Sleep(refresh_frequency);
		monitor_button();
		move_block();
		Z_engine_redraw();
	}
	game_over();
	system("pause >nul");
	return 0;
}