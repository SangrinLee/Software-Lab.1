#ifndef GAME_H
#define GAME_H
#include <ncurses.h>

typedef struct
{
	int x;
	int y;
} POS;

static int dir = -1;
static int maplevel = 3;

void menu();
void menu_print(WINDOW *menu_win, int highlight);
void start(int a);
void draw_screen(int (*pmap)[50]);
void draw_char(int x, int y, char* s);
void move_snake(POS* snake, int len);
int check_snake(POS* snake, int len, POS* map2);

#endif
