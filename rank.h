#ifndef GAME_H
#define GAME_H
#include <ncurses.h>

static int dir = -1;
static int dir2 = -1;

typedef struct
{
	int x;
	int y;
} POS;

typedef struct
{
	char name[20];
	int rank;
	int score;
} DATA;

void ranksave(int score, char name[]);
void rankinit();
void rankshow();

#endif