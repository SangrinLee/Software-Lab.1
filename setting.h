#ifndef GAME_H
#define GAME_H
#include <ncurses.h>

typedef struct
{
	int x, y;
} POS;

void help();
void setting();
void setting_print(WINDOW *menu_win, int highlight);

#endif
