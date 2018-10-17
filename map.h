#ifndef GAME_H
#define GAME_H
#include <ncurses.h>

static int dir = -1;

typedef struct
{
	int x;
	int y;
} POS;

void map_easy(int (*map)[50]);
void map_normal(int (*map)[50]);
void map_hard(int (*map)[50]);

#endif