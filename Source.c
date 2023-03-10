#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define UP 72  // Up Arrow 
#define DOWN 80 // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77  // Right Arrow 
#define ESC 27  // Escape Key
#define COLS 75
#define ROWS 25
#define SIZE 20
#define APPLE '$'

typedef struct
{
	int pos_x;
	int pos_y;
}Segment;

void printMenu();
int getKey();
void getGame();
void snakebody(int x, int y, int snakeSize, Segment snake[], int appleX, int appleY);
void run();
void snakeprint(int size, Segment snake[], int x, int y);
void losecheck(int x, int y, int size, Segment snake[]);
void gameOver();
void putFruit(int* fruitX, int* fruitY, Segment snake[]);
void gotoxy(int y, int x);


void main()
{
	run();
}

void printMenu() //Print size menu
{
	int i;
	for (i = 0; i < 55; i++)
	{
		printf("%c", '*');
	}
	printf("\n");
	printf("* Pick Your Level, to exit press 0\n");
	printf("* 0 -Exit \n");
	printf("* 1 - Basic Level \n");
	printf("* 2 - Intermidiate LEvel \n");
	printf("* 3 - Advanced Level \n");

	for (i = 0; i < 55; i++)
	{
		printf("%c", '*');
	}
	printf("\n");
}

void printBoard()
{
	system("cls");
	int i, j;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void initalSnake(Segment snake[], int size, int x, int y)
{
	// snake[size-1] - head

	snake[size - 1].pos_x = x;
	snake[size - 1].pos_y = y;

	for (int i = size - 2; i >= 0; i--)
	{
		snake[i].pos_x = (snake[i + 1].pos_x) - 1;
		snake[i].pos_y = snake[i + 1].pos_y;
	}
}

void moveSnake(Segment snake[], int x, int y, int size, char c)
{
	snake[size - 1].pos_x = x;
	snake[size - 1].pos_y = y;

	switch (c)
	{
	case RIGHT:
		for (int i = size - 2; i >= 0; i--)
		{
			snake[i].pos_x = (snake[i - 1].pos_x) + 1;
			snake[i].pos_y = snake[i - 1].pos_y;
		}
		break;
	case DOWN:
		for (int i = size - 2; i >= 0; i--)
		{
			snake[i].pos_x = snake[i - 1].pos_x;
			snake[i].pos_y = (snake[i - 1].pos_y) + 1;
		}
		break;
	case LEFT:
		for (int i = size - 2; i >= 0; i--)
		{
			snake[i].pos_x = (snake[i - 1].pos_x) - 1;
			snake[i].pos_y = snake[i - 1].pos_y;
		}
		break;
	case UP:
		for (int i = size - 2; i >= 0; i--)
		{
			snake[i].pos_x = snake[i - 1].pos_x;
			snake[i].pos_y = (snake[i - 1].pos_y) - 1;
		}
		break;
	}
}

void getGame()
{
	int size = 10;
	char c;
	int x = 40, y = 12;
	int appleX, appleY;
	Segment snake[20];
	initalSnake(snake, size, x, y);

	c = RIGHT;

	while (c != ESC)
	{
		Sleep(500);

		
		putFruit(&appleX, &appleY, snake);

		if (_kbhit())
			c = getKey();
snakeprint(size, snake, x, y);
		switch (c)
		{
		case RIGHT:
			x++;
			moveSnake(snake, x, y, size, c);
			break;
		case DOWN:
			y++;
			moveSnake(snake, x, y, size, c);
			break;
		case LEFT:
			x--;
			moveSnake(snake, x, y, size, c);
			break;
		case UP:
			y--;
			moveSnake(snake, x, y, size, c);
			break;
		}

		losecheck(x, y, size, snake);
	}
}

void gotoxy(int y, int x) {
	printf("\x1b[%d;%df", x + 1, y + 1);
}

int getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}


void snakeprint(int size, Segment snake[], int x, int y) {
	for (int i = 0; i < size; i++)
	{
		Sleep(500);

		gotoxy(snake[i].pos_x, snake[i].pos_y);
		printf("@");
	}
}

void run()
{
	int level = 0, play = 0;
	printMenu();
	while (!play)
	{
		scanf("%d", &level);
		switch (level)
		{
		case 0:
			printf("Good bye.\n");
			break;
		case 1:
		{
			printBoard();
			getGame();
			play = 1;
			break;
		}
		default:
			//printf("Invalid input \n\n"); // if the size you choose is not in the print menu
			printMenu();
			break;

		}
	}
}

int isEqualSeg(Segment a, Segment b)
{
	return (a.pos_x == b.pos_x && a.pos_y == b.pos_y);
}

void losecheck(int x, int y, int size, Segment snake[])
{
	int i;
	if (y == ROWS - 1 || x == COLS - 1)
	{
		gameOver();
		system("pause");
	}
	if (y == 0 || x == 0)
	{
		gameOver();
		system("pause");
	}
	else {
		Segment snake_head = snake[0];

		for (int i = 1; i < size; i++)
		{
			// head == body
			if (isEqualSeg(snake[i], snake_head))
			{
				gameOver();
				system("pause");
			}
		}
	}
}

void gameOver()
{
	system("cls");
	printf("##################################\n");
	printf("\t   Game over\n");
	printf("##################################\n");
}

void putFruit(int* fruitX, int* fruitY, Segment snake[])
{
	srand(time(NULL));
	int size = 10;
	int appleX = rand() % COLS;
	int appleY = rand() % ROWS;

	if (appleX > 0 && appleY > 0 && appleX < COLS - 1 && appleY < ROWS - 1)
	{
		gotoxy(appleX, appleY);
		printf("$");
	}

	*fruitX = appleX;
	*fruitY = appleY;
}