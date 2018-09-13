#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define X 29
#define Y 29 //��ͼ��С

int block[X][Y];
int direction = 4;			 //�ߵķ��� 8546 wsad
int snake_long = 0;			 //������
int game_continue = 1;		 //��Ϸ�Ƿ���� 0�� 1��
int refresh_frequency = 500; //����ˢ��Ƶ�� ��λ����
char other_information[30] = "��Ϸ��ʼ,ף������.";

//���º����ɹ�����2
//-2   -1   0    1
//ʳ�� ǽ�� �հ� ��

int return_random(int x, int y) //x < y
{
	int random;
	random = rand() % (y - x + 1) + x;
	return random;
}

int random_direction(void)
{
	int random = return_random(1, 4);
	if (random == 1)
		direction = 4;
	else if (random == 2)
		direction = 5;
	else if (random == 3)
		direction = 6;
	else if (random == 4)
		direction = 8;
	return 2;
}

int create_block(int x, int y, int kind) //��������
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
	create_line(0, 0, X - 1, 0, -1);
	create_line(X - 1, 0, X - 1, Y - 1, -1);
	create_line(0, 0, 0, Y - 1, -1);
	create_line(0, Y - 1, X - 1, Y - 1, -1);
	return 2;
}

int create_snake(void)
{
	int x = return_random(0, X), y = return_random(0, Y);
	if (block[x][y] == 0)
	{
		create_block(x, y, 1);
		snake_long = snake_long + 1;
	}
	else
		create_snake();
	return 2;
}

int create_food(void)
{
	int x = return_random(0, X), y = return_random(0, Y);
	if (block[x][y] == 0)
	{
		create_block(x, y, -2);
	}
	else
		create_food();
	return 2;
}

int level_up(void)
{
	if (snake_long >= 60)
	{
		strcpy(other_information, "������������!!!.");
		create_food();
		refresh_frequency = 20;
	}
	else if (snake_long >= 40)
	{
		strcpy(other_information, "��ģʽ����!!!");
		create_food();
		refresh_frequency = 50;
	}
	else if (snake_long >= 30)
	{
		strcpy(other_information, "Խ��Խ���˰�!");
		create_food();
		refresh_frequency = 100;
	}
	else if (snake_long >= 25)
	{
		strcpy(other_information, "����û�취.");
		create_food();
		refresh_frequency = 200;
	}
	else if (snake_long >= 20)
	{
		strcpy(other_information, "Ƶ�����е�����.");
		create_food();
		refresh_frequency = 300;
	}
	else if (snake_long >= 15)
	{
		strcpy(other_information, "�ٶ�Ҳ����!");
		create_food();
		refresh_frequency = 350;
	}
	else if (snake_long >= 10)
	{
		strcpy(other_information, "ʳ�����!");
		create_food();
		refresh_frequency = 400;
	}
	else if (snake_long >= 5)
	{
		strcpy(other_information, "��Ϸ������!");
		create_food();
		refresh_frequency = 450;
	}
	return 2;
}

int out_put_information(void)
{
	printf("�ߵķ���:%d ", direction);
	printf("��ĵ÷�:%d ", snake_long - 1);
	printf("��Ϸ�ٶ�:%d ", refresh_frequency);
	printf("%s", other_information);
	return 2;
}

int Z_engine_start(void) //�������� ��䷽��
{
	int x, y;
	for (y = 0; y <= Y - 1; y++)	 //�����
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
			else if (block[x][y] > 0) //��
				printf("%s", "��");
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
			if (direction != 5)
				direction = 8;
		}
		else if (button == 's' || button == 'S')
		{
			if (direction != 8)
				direction = 5;
		}
		else if (button == 'a' || button == 'A')
		{
			if (direction != 6)
				direction = 4;
		}
		else if (button == 'd' || button == 'D')
		{
			if (direction != 4)
				direction = 6;
		}
	}
	return 2;
}

int snake_long_reset(void)
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //�����
	{
		for (x = 0; x <= X - 1; x++) //�����
		{
			if (block[x][y] > 0)			   //��⵽��
				block[x][y] = block[x][y] + 1; //kind+1
		}
	}
	return 2;
}

int game_over(void) //��Ϸ����
{
	game_continue = 0;
	system("color 40");
	strcpy(other_information, "YOU LOST!");
	return 2;
}

int delete_snake_tali(void)
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //�����
	{
		for (x = 0; x <= X - 1; x++) //�����
		{
			if (block[x][y] == snake_long + 1)
				block[x][y] = 0;
		}
	}
	return 2;
}

int move_block(void) //�ƶ�����
{
	int x, y;
	level_up();
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
					else if (block[x][y - 1] > 0) //ײ���Լ�
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
					else if (block[x][y + 1] > 0) //ײ���Լ�
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
					if (block[x - 1][y] == -1) //ײ��ǽ
						goto miao;
					else if (block[x - 1][y] == -2) //�Ե�ʳ��
					{
						snake_long_reset();
						create_block(x - 1, y, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x - 1][y] > 0) //ײ���Լ�
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
					if (block[x + 1][y] == -1) //ײ��ǽ
						goto miao;
					else if (block[x + 1][y] == -2) //�Ե�ʳ��
					{
						snake_long_reset();
						create_block(x + 1, y, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x + 1][y] > 0) //ײ���Լ�
						goto miao;
					else
					{
						snake_long_reset();
						create_block(x + 1, y, 1);
						delete_snake_tali();
						goto wang;
					}
				}
			}
		}
	}
wang:
	return 2;
miao:
	game_continue = 0;
	return 2;
}

int main(void)
{
	srand((unsigned int)time(NULL));
	system("mode con cols=58 lines=30");
	system("color 9f");
	system("title=̰���� v7.0");
	Z_engine_start();
	create_wall();
	create_snake();
	create_food();
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
	Z_engine_redraw();
	system("pause >nul");
	return 0;
}
