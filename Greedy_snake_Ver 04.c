#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#define X 29
#define Y 29
struct blo
{
	char pattern[3];
	int x;
	int y;
	int xm;
	int ym;
	int collision;
}block[X][Y];
int collision_or_not = 0; //�Ƿ���ײ 0Ϊ�� 1Ϊ��
int eat_food_or_not = 0; //�Ƿ�Ե�ʳ�� 0Ϊû�� 1Ϊ��
int direction = 6; //���� 8546 ��������
int engine_status = -1; //����״̬ -1��1
int snake_long=0; //�ߵĳ���
int xxx, yyy; //��ͷ����
int sss; //��ͷ����
char background[3] = "��";
char snake_pattern[3] = "��";
//�������к����ɹ�����2 ����

int create_block(char pattern[3], int x, int y, int xm, int ym, int collision) //�������� [ͼ��,x,y,x�ƶ�����,y�ƶ�����,�ϰ����ʶ]
{
	block[x][y].pattern[0] = pattern[0];
	block[x][y].pattern[1] = pattern[1];
	block[x][y].pattern[2] = pattern[2];
	block[x][y].x = x;
	block[x][y].y = y;
	block[x][y].xm = xm;
	block[x][y].ym = ym;
	block[x][y].collision = collision;
	return 2;
}
int create_line(char pattern[3], int x1, int y1, int x2, int y2, int xm, int ym, int collision) //�������� 
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 0; i <= (y2 - y1); i++)
				create_block(pattern, x1, y1 + i, xm, ym, collision);
		}
		else if (y1 > y2)
		{
			for (i = 0; i <= (y1 - y2); i++)
				create_block(pattern, x1, y2 + i, xm, ym, collision);
		}
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			for (i = 0; i <= (x2 - x1); i++)
				create_block(pattern, x1 + i, y1, xm, ym, collision);
		}
		else if (x1 > x2)
		{
			for (i = 0; i <= (x1 - x2); i++)
				create_block(pattern, x2 + i, y1, xm, ym, collision);
		}
	}
	return 2;
}
int creat_snake_head(void)
{
	create_block("��", 9, 9, (snake_long = snake_long + 1), 0, 1);
	return 2;
}
int creat_snake_tail(void)
{
	create_block("��", 8, 9, (snake_long = snake_long + 1), 0, 1);
	return 2;
}
int create_wall(void) //����ǽ 
{
	create_line("��", 0, 0, X - 1, 0, 0, 0, 1);
	create_line("��", X - 1, 0, X - 1, Y - 1, 0, 0, 1);
	create_line("��", 0, 0, 0, Y - 1, 0, 0, 1);
	create_line("��", 0, Y - 1, X - 1, Y - 1, 0, 0, 1);
	return 2;
}
int Z_engine_start(void) //�������� ��䷽�� 
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //�����
		for (x = 0; x <= X - 1; x++) //�����
			create_block("��", x, y, 0, 0, 0);
	return 2;
}
int Z_engine_redraw(void) //�ػ� 
{
	int x, y;
	system("cls");
	for (y = 0; y <= Y - 1; y++) //������
	{
		for (x = 0; x <= X - 1; x++) //������
			printf("%s", block[x][y].pattern);
		putchar('\n');
	}
	printf("direction:%d  ", direction);
	printf("collision_or_not:%d  ", collision_or_not);
	printf("engine_status:%d  ", engine_status);
	printf("��ͷ����:%d  %d  ", xxx,yyy);
	printf("��ͷ����: %d", sss);
	return 2;
}
int monitor_collision(int x1, int y1, int x2, int y2, int collision) //�����ײ [��ʼ����,��ֹ����,�ϰ����ʶ]
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 1; i <= y2 - y1; i++)
			{
				if (block[x1][y1 + i].collision == collision)
					collision_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= y1 - y2; i++)
			{
				if (block[x1][y2 + i - 1].collision == collision)
					collision_or_not = 1;
				else
					;
			}
		}
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			for (i = 1; i <= x2 - x1; i++)
			{
				if (block[x1 + i][y1].collision == collision)
					collision_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= x1 - x2; i++)
			{
				if (block[x2 + i - 1][y1].collision== collision)
					collision_or_not = 1;
				else
					;
			}
		}

	}
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
int move_block(void)
{
	engine_status = engine_status*(-1);
	int x, y;
	for (y = 0; y <= Y - 1 && collision_or_not == 0; y++) //��
	{
		for (x = 0; x <= X - 1 && collision_or_not == 0; x++) //��
		{
			if (block[x][y].xm == engine_status) //��ͷ
			{
				if (direction == 8)
				{
					//monitor_collision(x, y, x,y - 1,1);
					block[x][y - 1].collision = block[x][y].collision;
					block[x][y - 1].xm = -1 * block[x][y].xm;
					block[x][y].xm = 0;
					block[x][y - 1].pattern[0] = block[x][y].pattern[0];
					block[x][y - 1].pattern[1] = block[x][y].pattern[1];
					block[x][y - 1].pattern[2] = block[x][y].pattern[2];
				}
				else if (direction == 5)
				{
					//monitor_collision(x, y, x,y + 1,1);
					block[x][y + 1].collision = block[x][y].collision;
					block[x][y + 1].xm = -1 * block[x][y].xm;
					block[x][y].xm = 0;
					block[x][y + 1].pattern[0] = block[x][y].pattern[0];
					block[x][y + 1].pattern[1] = block[x][y].pattern[1];
					block[x][y + 1].pattern[2] = block[x][y].pattern[2];
				}
				else if (direction == 4)
				{
					//monitor_collision(x, y, x-1, y, 1);
					block[x - 1][y].collision = block[x][y].collision;
					block[x - 1][y].xm = -1 * block[x][y].xm;
					block[x][y].xm = 0;
					block[x - 1][y].pattern[0] = block[x][y].pattern[0];
					block[x - 1][y].pattern[1] = block[x][y].pattern[1];
					block[x - 1][y].pattern[2] = block[x][y].pattern[2];
				}
				else if (direction == 6)
				{
					//monitor_collision(x, y, x + 1, y, 1);
					//block[x + 1][y].collision = block[x][y].collision; //�ƽ���ײ����
					block[x + 1][y].xm = (-1) * engine_status; //�ƽ���ͷ����
					//block[x][y].xm = 0; //ɾ����ͷ����
					sss = block[x + 1][y].xm;
					xxx = x + 1, yyy = y;
					block[x + 1][y].pattern[0] = snake_pattern[0]; //�ƽ���ͷ����
					block[x + 1][y].pattern[1] = snake_pattern[1];
					block[x + 1][y].pattern[2] = snake_pattern[2];
					printf("\a");
				}
				else;
			}
			else if (block[x][y].xm !=0 && block[x][y].xm != 1&& block[x][y].xm != -1) //��β
			{
				if (eat_food_or_not == 0) //û�Ե�ʳ��ɾ����β
				{
					/*block[x + 1][y].collision = 0;
					block[x + 1][y].xm = 0;
					block[x][y].pattern[0] = background[0];
					block[x][y].pattern[1] = background[1];
					block[x][y].pattern[2] = background[2];*/
				}
				else //�Ե�ʳ�ﲻɾ����β
				{
					/*block[x + 1][y].collision = 0;
					block[x + 1][y].xm = 0;
					block[x][y].pattern[0] = background[0];
					block[x][y].pattern[1] = background[1];
					block[x][y].pattern[2] = background[2];*/
				}
			}
			else;
		}
	}
	return 2;
}
int main(void)
{
	for (; collision_or_not == 0;)
	{
		Sleep(1000);
		Z_engine_start();
		create_wall();
		creat_snake_head();
		//creat_snake_tail();
		monitor_button();
		
		move_block();

		Z_engine_redraw();
	}
	return 0;
}