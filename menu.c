#include "game.h"

void menu()
{
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c, h;
	int startx, starty;

	initscr();
	clear();
	noecho();
	cbreak();

	startx = (80 - width) / 2;
	starty = (24 - height) / 2;
	menu_win = newwin(height, width, starty, startx);

	keypad(menu_win, TRUE);
	mvprintw(2, 30, "Welcome to Snake Run~");
	mvprintw(4, 23, "Please enter to select a choice");
	refresh();
	menu_print(menu_win, highlight);

	while(1)
	{
		c = wgetch(menu_win);
		switch(c)
		{
			case KEY_UP:
			if(highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
			case KEY_DOWN:
			if(highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
			case 10:
			choice = highlight;
			break;
			default :
			break;
		}
		menu_print(menu_win, highlight);
		if(choice != 0)
			break;
	}
	
	mvprintw(5, 30, "< You chose choice %d >", choice);
	clrtoeol();
	refresh();

	switch(choice)
	{
		case 1: start(1); break; 
		case 2:	setting(); break;
		case 3: 
		{
			rankshow();
			h = getch();
			if(h == 10)
				menu();
		}
		case 4: help(); break;
		case 5: start2(); break;
		case 6: endwin(); break;
	}
	endwin();
}

void menu_print(WINDOW *menu_win, int highlight)
{
	int x, y, i;
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{
		if(highlight == i + 1)
		{
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
	curs_set(0);
}
