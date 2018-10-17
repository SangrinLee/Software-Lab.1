#include "game.h"

void help()
{
	clear();
	mvprintw(5, 15, "<Help>");
	mvprintw(6, 15, "This is simple game called Snake Run!");
	mvprintw(7, 15, "##### Single Player Game #####");
	mvprintw(8, 15, "You may want to take the items indicating $");
	mvprintw(9, 15, "which is how you score");
	mvprintw(10, 15, "Each item has different color");
	mvprintw(11, 15, "Some item take your score so watch out");
	mvprintw(12, 15, "You need to avoid all obstacle");
	mvprintw(13, 15, "Simple right?");

	mvprintw(15, 15, "##### Multi Player Game #####");
	mvprintw(16, 15, "Whoever grabs one's tail or body");
	mvprintw(17, 15, "is the winner!");
	mvprintw(18, 15, "But watch out the obstables");
	mvprintw(19, 15, "Now let's get started! Enjoy!");
	refresh();
	usleep(500000);
}

void setting()
{
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    int startx2, starty2;

    initscr();
    clear();
    noecho();
    cbreak();

    startx2 = (80 - width2) / 2;
    starty2 = (24 - height2) / 2;
    menu_win = newwin(height2, width2, starty2, startx2);

    keypad(menu_win, TRUE);
    mvprintw(2, 30, "Welcome to Snake Run~");
    mvprintw(4, 23, "Please enter to select a choice");
    refresh();
    setting_print(menu_win, highlight);

    while(1)
    {
        c = wgetch(menu_win);
        switch(c)
        {
	        case KEY_UP:
	            if(highlight == 1)
	                highlight = n_choices2;
	            else
	                --highlight;
	            break;
	        case KEY_DOWN:
	            if(highlight == n_choices2)
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
        setting_print(menu_win, highlight);
        if(choice != 0)
            break;
    }

    mvprintw(5, 30, "< You chose choice %d >", choice);
    clrtoeol();
    refresh();
    
    switch(choice)
    {
	    case 1:
	        start(1);
	        break;
	    case 2:
	        start(2);
	        break;
	    case 3:
	        start(3);
	        break;
	    case 4:
	        menu();
	        break;
    }
}

void setting_print(WINDOW *menu_win, int highlight)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices2; ++i)
    {
        if(highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices2[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices2[i]);
        ++y;
    }
    wrefresh(menu_win);
    curs_set(0);
}