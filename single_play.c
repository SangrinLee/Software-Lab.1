#include "game.h"
#define MAX 100

void start(int a)
{
	dir = -1;
	int map[30][50] = {0};
	if(a == 1)
		map_easy(map);
	if(a == 2)
		map_normal(map);
	if(a == 3)
		map_hard(map);

	int c, d;
	int count = 0;
	POS snake[MAX], item[3], map2[1500];
	for(c = 0; c < 30; c++)
	{
		for(d = 0; d < 50; d++)
		{
			if(map[c][d] == 1)
			{
				map2[count].x = d;
				map2[count].y = c;
				count++;
			}
		}
	}

	int i, len = 5;
	int score = 0, speed = 100000;
	int clock = 0;
	char name[20];

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	srand(time(NULL));
	start_color();

	init_pair(1, 0, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_WHITE);
	init_pair(4, COLOR_YELLOW, 0);
	attron(COLOR_PAIR(1));
	draw_screen(map);
	attroff(COLOR_PAIR(1));

	for(i = 0; i < len; i++)
	{
		snake[i].x = 15+i;
		snake[i].y = 15;
		attron(COLOR_PAIR(3));
		draw_char(snake[i].x, snake[i].y, "#");
		attroff(COLOR_PAIR(3));
	}

	int con = 0;
	while(true)
	{
		item[0].x = rand()%48 + 1;
		item[0].y = rand()%29 + 1;
		item[1].x = rand()%48 + 1;
		item[1].y = rand()%29 + 1;
		item[2].x = rand()%48 + 1;
		item[2].y = rand()%29 + 1;
		for(i = 0; i < 1500; i++)
		{
			if(item[0].x != map2[i].x || item[0].y != map2[i].y || item[1].x != map2[i].x || item[1].y != map2[i].y || item[2].x != map2[i].x || item[2].y != map2[i].y)
				con = 1;
		}
		if(con == 1)
			break;
	}
	
	draw_char(55, 6, "Score : 0");
	while(true)
	{
		if(check_snake(snake, len, map2) == 0)
		{
			cbreak(); echo(); 

			mvprintw(8, 55, "Your name please?");
			mvscanw(9, 55, "%s", name);
			refresh();
			ranksave(score, name);
			menu();
			break;
		}
		if(snake[0].x == item[0].x && snake[0].y == item[0].y)
		{
			mvprintw(item[0].y, item[0].x, " ");
			item[0].x = 0;
			item[0].y = 0;
			score += 10;
			draw_char(55, 6, "Score : ");
			printw("%2d", score);
			while(speed>10000)
				speed -= 10000;
			if(len < 20)
				len ++;
		}
		if(snake[0].x == item[1].x && snake[0].y == item[1].y)
		{
			mvprintw(item[1].y, item[1].x, " ");
			item[1].x = 0;
			item[1].y = 0;
			score += 5;
			draw_char(55, 6, "Score : ");
			printw("%2d", score);
			while(speed>10000)
				speed -= 10000;
			if(len < 20)
				len++;
		}
		if(snake[0].x == item[2].x && snake[0].y == item[2].y)
		{
			mvprintw(item[2].y, item[2].x, " ");
			item[2].x = 0;
			item[2].y = 0;
			score -= 5;
			draw_char(55, 6, "Score : ");
			printw("%2d", score);
			while(speed>10000)
				speed -= 10000;
			if(len < 20)
				len ++;
		}

		if((clock%50) == 0)
		{
			mvprintw(item[0].y, item[0].x, " ");
			mvprintw(item[1].y, item[1].x, " ");
			mvprintw(item[2].y, item[2].x, " ");
			con = 0;
			while(1)
			{
				item[0].x = rand()%48 + 1;
				item[0].y = rand()%29 + 1;
				item[1].x = rand()%48 + 1;
				item[1].y = rand()%29 + 1;
				item[2].x = rand()%48 + 1;
				item[2].y = rand()%29 + 1;
				for(i = 0; i < 1500; i++)
				{
					if(item[0].x != map2[i].x || item[0].y != map2[i].y || item[1].x != map2[i].x || item[1].y != map2[i].y || item[2].x != map2[i].x || item[2].y != map2[i].y)
						con = 1;
				}
				if(con == 1)
					break;
			}
			move(item[0].y, item[0].x);
			attron(COLOR_PAIR(4));
			addch(ACS_STERLING);
			attroff(COLOR_PAIR(4));

			move(item[1].y, item[1].x);
			addch(ACS_STERLING);

			move(item[2].y, item[2].x);
			addch(ACS_STERLING);
		}
		move_snake(snake, len);
		usleep(speed);

		clock += 1;
		mvprintw(4, 55, "Time : ");
		mvprintw(4, 62, "%d", clock);

	}
	clear();
	draw_char(1, 22, "Game Over\n");
	endwin();
}

void draw_screen(int (*pmap)[50])
{
	int i, j;
	clear();
	for(i = 0; i < 30; i++)
	{
		for(j = 0; j < 50; j++)
		{
			if(pmap[i][j] == 1)
				mvprintw(i, j, " ");
		}
	}

	draw_char(0, 0, "                    SNAKE RUN                     ");
	for(i = 1; i < 30; i ++)
	{
		draw_char(0, i, " ");
		draw_char(49, i, " ");
	}
	draw_char(0, 30, "                    ENJOY GAME                    ");
}

void draw_char(int x, int y, char* s)
{
	move(y, x);
	printw("%s", s);
	refresh();
	curs_set(0);
}

void move_snake(POS* snake, int len)
{
	keypad(stdscr, TRUE);
	if(!halfdelay(1))
	{
		int key;
		do
		{
			key = getch();
		} while(key == 224);

		switch(key)
		{
			case KEY_UP: dir = 0; break;
			case KEY_DOWN: dir = 1; break;
			case KEY_LEFT: dir = 2; break;
			case KEY_RIGHT: dir = 3; break;
		}
	}

	if(dir != -1)
	{
		int i;
		draw_char(snake[len-1].x, snake[len-1].y, " ");
		for(i = len - 1; i > 0; i--)
		{
			snake[i] = snake[i-1];
		}
		attron(COLOR_PAIR(3));
		draw_char(snake[1].x, snake[1].y, "#");
		attroff(COLOR_PAIR(3));
	}

	switch(dir)
	{
		case 0: snake[0].y--; break;
		case 1: snake[0].y++; break;
		case 2: snake[0].x--; break;
		case 3: snake[0].x++; break;
	}
	attron(COLOR_PAIR(2));
	draw_char(snake[0].x, snake[0].y, "@");
	attroff(COLOR_PAIR(2));
}

int check_snake(POS* snake, int len, POS* map2)
{
	int i;
	int j;

	if(snake[0].x == 0 || snake[0].y == 0 || snake[0].x == 49 || snake[0].y == 30)
		return 0;

	for(j = 0; j < 1500; j++)
	{
		if(snake[0].x == map2[j].x && snake[0].y == map2[j].y)
			return 0;
	}
	return 1;
}
