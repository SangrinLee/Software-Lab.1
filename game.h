#ifndef GAME_H
#define GAME_H
#include <ncurses.h>

#define width 30
#define height 10
#define width2 30
#define height2 10

static char *choices[] = {"1. Start",
                   "2. Setting",
                   "3. Ranking",
                   "4. Helping",
                   "5. P vs P",
                   "6. Exit",
                  };

static char *choices2[] = {"Easy mode",
                    "Normal mode",
                    "Hard mode",
                    "Back to menu"
                   };

static int n_choices = 6;
static int n_choices2 = 4;

static int dir = -1;
static int dir2 = -1;
static int maplevel = 3;

typedef struct
{
	int x, y;
} POS;

typedef struct
{
	char name[20];
	int rank;
	int score;
} DATA;

void menu();
void menu_print(WINDOW *menu_win, int highlight);
void start(int a);
void draw_screen(int (*pmap)[50]);
void draw_char(int x, int y, char* s);
void move_snake(POS* snake, int len);
int check_snake(POS* snake, int len, POS* map2);
void setting();
void setting_print(WINDOW *menu_win, int highlight);
void ranksave(int score, char name[]);
void rankinit();
void rankshow();
void help();
void map_easy(int (*map)[50]);
void map_normal(int (*map)[50]);
void map_hard(int (*map)[50]);
void start2();
void move_snakes(POS* snake1, int len1, POS* snake2, int len2);
int check_snakes(POS* snake1, int len1, POS* snake2, int len2);

#endif