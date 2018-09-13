#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#define X 100
#define Y 29 //������Ϊ��ͼ��С
char blocks[X][Y];
int death_or_not = 0; //�Ƿ����� 0Ϊ�� 1Ϊ��
char direction='w'; //�ߵ���ʼ����
char snake_speed = 1; //�ߵ��ٶ�
int snake_x = 10; 
int snake_y = 10; //������Ϊ�ߵĳ�ʼ����
int refresh_frequency = 200; //ˢ��Ƶ�� ��λ����

void draw_blocks(int x, int y, char kind) //���� ���� [x,y,��������]
{
	blocks[x][y] = kind;
}
void draw_line(int x1, int y1, int x2, int y2, char kind)
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 0; i <= (y2 - y1); i++)
				draw_blocks(x1, y1 + i, kind);
		}
		else if (y1 > y2)
		{
			for (i = 0; i <= (y1 - y2); i++)
				draw_blocks(x1, y2 + i, kind);
		}
	}
	else if (y1 == y2) 
	{
		if (x1 < x2)
		{
			for (i=0; i <= (x2 - x1); i++)
				draw_blocks(x1 + i, y1, kind);
		}
		else if (x1 > x2)
		{
			for (i=0; i <= (x1 - x2); i++)
				draw_blocks(x2 + i, y1, kind);
		}
	}
}
void draw_wall() //���� ǽ
{
	draw_line(0, 0, X - 1, 0, 'W');
	draw_line(X - 1, 0, X - 1, Y - 1, 'W');
	draw_line(0, 0, 0, Y - 1, 'W');
	draw_line(0, Y - 1, X - 1, Y - 1, 'W');
}
void monitor_collision(int x1, int y1, int x2, int y2, char kind) //�����ײ [��ʼ����,��ֹ����,�ϰ����ʶ]
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 1; i <= y2 - y1; i++)
			{
				if (blocks[x1][y1 + i] == kind)
					death_or_not = 1;
				else
					;
			}
		}
		else 
		{
			for (i = 1; i <= y1 - y2; i++)
			{
				if (blocks[x1][y2 + i-1] == kind)
					death_or_not = 1;
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
				if (blocks[x1 + i][y1] == kind)
					death_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= x1 - x2; i++)
			{
				if (blocks[x2 + i-1][y1] == kind)
					death_or_not = 1;
				else
					;
			}
		}
		
	}
}
void move_blocks() //�ƶ�����
{
	if (direction == 'w'|| direction == 'W')
	{
		monitor_collision(snake_x,snake_y,snake_x, snake_y - snake_speed,'W');
		snake_y = snake_y - snake_speed;
		draw_blocks(snake_x, snake_y + snake_speed, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
	else if (direction == 's'|| direction == 'S')
	{
		monitor_collision(snake_x, snake_y, snake_x, snake_y + snake_speed, 'W');
		snake_y = snake_y + snake_speed;
		draw_blocks(snake_x, snake_y - snake_speed, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
	else if (direction == 'a'|| direction == 'A')
	{
		monitor_collision(snake_x, snake_y,snake_x - snake_speed, snake_y, 'W');
		snake_x = snake_x - snake_speed;
		draw_blocks(snake_x + snake_speed, snake_y, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
	else if (direction == 'd'|| direction == 'D')
	{
		monitor_collision(snake_x, snake_y, snake_x + snake_speed, snake_y, 'W');
		snake_x = snake_x + snake_speed;
		draw_blocks(snake_x - snake_speed, snake_y, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
}
void monitor_button(void)  //��ⰴ��
{
	char button;
	if (kbhit() == 1) //����
	{
		button = getch();
		if (button == 'w' || button == 'W' || button == 's' || button == 'S' || button == 'a' || button == 'A' || button == 'd' || button == 'D')
			direction = button;
		else
			;
	}
	else //û�а���
	{

	}
}
void initialize(void) //��ʼ�� ���ո�
{
	int x, y;
	for (y = 0; y <=Y-1; y++) //�����
		for (x = 0; x <= X-1; x++) //�����
			draw_blocks(x, y, 32);
}
void redraw(void) //�ػ����з���  
{
	int x, y;
	system("cls");
	for (y=0; y<= Y-1; y++) //������
	{
		for (x=0; x <= X-1; x++) //������
			printf("%c", blocks[x][y]);
		putchar('\n');
	}

}
void clock(int time) //ʱ�� [����(��λ����)]
{
	for (;death_or_not==0;)
	{
		monitor_button();//��ⰴ��
		move_blocks();//�ƶ�����
		printf("%d", death_or_not);//������
		redraw(); //�ػ����з���
		Sleep(time);
	}
}
int main(void)
{
	initialize(); //��ʼ�� ���ո�
	draw_wall(); //���� ǽ 	
	redraw(); //�ػ����з���  
	clock(refresh_frequency); //ʱ��
	return 0;
}
