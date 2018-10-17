#ifndef GAME_H
#define GAME_H
#include <ncurses.h>

typedef struct
{
	int x, y;
} POS;

void menu();
void menu_print(WINDOW *menu_win, int highlight);
void multi_play();
void move_snakes(POS* snake1, int len1, POS* snake2, int len2);
int check_snakes(POS* snake1, int len1, POS* snake2, int len2);

#endif