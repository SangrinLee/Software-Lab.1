#include "game.h"

int main()
{
    menu();
    return 0;
}

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
    startx = (80 - width) / 2;
    starty = (24 - height) / 2;
    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(2, 30, "Welcome to Snake Run~");
    mvprintw(4, 23, "Please enter to select a choice");
    refresh();
    menu_print(menu_win, highlight);

    while(true)
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
    clrtoeol();
    refresh();

    switch(choice)
    {
	    case 1:
	        start(1);
	        break;
	    case 2:
	        setting();
	        break;
	    case 3:
	    {
	        rankshow();
	        h = getch();
	        if(h == 10)
	            menu();
	    }
	    case 4:
	    {
	        help();
	        h = getch();
	        if(h == 10)
	            menu();
	    }
	    case 5:
	        multi_play();
	        break;
	    case 6:
	        endwin();
	        break;
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

void multi_play()
{
    POS snake1[25], snake2[25], item[3];
    int len1 = 15, len2 = 15;
    int map[30][50] = {0};
    int winning = -1;
    int i, clock = 0;

    initscr();
    keypad(stdscr, TRUE);
    srand(time(NULL));

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_YELLOW);
    init_pair(6, COLOR_RED, COLOR_BLUE);

    attron(COLOR_PAIR(1));
    draw_screen(map);
    attroff(COLOR_PAIR(1));

    for(i = 0; i < len1; i++)
    {
        snake1[i].x = 25+i;
        snake1[i].y = 5;
        attron(COLOR_PAIR(3));
        draw_char(snake1[i].x, snake1[i].y, "#");
        attroff(COLOR_PAIR(3));
    }

    for(i = 0; i < len2; i++)
    {
        snake2[i].x = 25 - i;
        snake2[i].y = 25;
        attron(COLOR_PAIR(5));
        draw_char(snake2[i].x, snake2[i].y, "#");
        attroff(COLOR_PAIR(5));
    }

    item[0].x = rand()%48 + 1;
    item[0].y = rand()%29 + 1;
    item[1].x = rand()%48 + 1;
    item[1].y = rand()%29 + 1;
    item[2].x = rand()%48 + 1;
    item[2].y = rand()%29 + 1;

    while(true)
    {
        winning = check_snakes(snake1, len1, snake2, len2);
        if(winning == 0 || winning == 1 || winning == 2)
        {
            cbreak();
            echo();
            mvprintw(10, 65, "Congrats~");
            refresh();
            usleep(500000);
            switch(winning)
            {
	            case 0:
	                mvprintw(12, 55, "A player and B player draw!");
	                refresh();
	                usleep(500000);
	                break;
	            case 1:
	                mvprintw(12, 55, "A player grabbed winning!");
	                refresh();
	                usleep(500000);
	                break;
	            case 2:
	                mvprintw(12, 55, "B player grabbed winning!");
	                refresh();
	                usleep(500000);
	                break;
            }
            mvprintw(14, 55, "Thank you for playing~");
            refresh();
            usleep(500000);
            mvprintw(16, 55, "Hope you grabbed lots of funs too!!");
            refresh();
            usleep(1000000);
            usleep(1000000);
            menu();
            break;
        }

        if(snake1[0].x == item[0].x && snake1[0].y == item[0].y)
        {
            mvprintw(item[0].y, item[0].x, " ");
            item[0].x = 0;
            item[0].y = 0;
            len1 = len1 - 2;
            mvprintw(snake1[len1+1].y, snake1[len1+1].x, " ");
            mvprintw(snake1[len1].y, snake1[len1].x, " ");
        }

        if(snake1[0].x == item[1].x && snake1[0].y == item[1].y)
        {
            mvprintw(item[1].y, item[1].x, " ");
            item[1].x = 0;
            item[1].y = 0;
            len1 = len1 - 1;
            mvprintw(snake1[len1].y, snake1[len1].x, " ");
        }

        if(snake1[0].x == item[2].x && snake1[0].y == item[2].y)
        {
            mvprintw(item[2].y, item[2].x, " ");
            item[2].x = 0;
            item[2].y = 0;
            len1 = len1 + 1;
        }

        if(snake2[0].x == item[0].x && snake2[0].y == item[0].y)
        {
            mvprintw(item[0].y, item[0].x, " ");
            item[0].x = 0;
            item[0].y = 0;
            len2 = len2 - 2;
            mvprintw(snake2[len2+1].y, snake2[len2+1].x, " ");
            mvprintw(snake2[len2].y, snake2[len2].x, " ");
        }

        if(snake2[1].x == item[1].x && snake2[0].y == item[1].y)
        {
            mvprintw(item[1].y, item[1].x, " ");
            item[1].x = 0;
            item[1].y = 0;
            len2 = len2 - 1;
            mvprintw(snake2[len2].y, snake2[len2].x, " ");
        }

        if(snake2[0].x == item[2].x && snake2[0].y == item[2].y)
        {
            mvprintw(item[2].y, item[2].x, " ");
            item[2].x = 0;
            item[2].y = 0;
            len2 = len2 + 1;
        }

        if((clock%50) == 0)
        {
            mvprintw(item[0].y, item[0].x, " ");
            mvprintw(item[1].y, item[1].x, " ");
            mvprintw(item[2].y, item[2].x, " ");

            item[0].x = rand()%48 + 1;
            item[0].y = rand()%29 + 1;
            item[1].x = rand()%48 + 1;
            item[1].y = rand()%29 + 1;
            item[2].x = rand()%48 + 1;
            item[2].y = rand()%29 + 1;

            move(item[0].y, item[0].x);
            attron(COLOR_PAIR(4));
            addch(ACS_STERLING);
            attroff(COLOR_PAIR(4));
            move(item[1].y, item[1].x);
            addch(ACS_STERLING);
            move(item[2].y, item[2].x);
            addch(ACS_STERLING);
        }
        move_snakes(snake1, len1, snake2, len2);
        usleep(10000);
        clock += 1;
        mvprintw(4, 55, "Time : %d", clock);
    }
    endwin();
}

void move_snakes(POS* snake1, int len1, POS* snake2, int len2)
{
    keypad(stdscr, TRUE);
    static int dir = -1;
    static int dir2 = -1;
    if(!halfdelay(1))
    {
        char key;
        do
        {
            key = getch();
        } while(key == 224);

        switch(key)
        {
	        case 'w' :
	            dir = 0;
	            break;
	        case 's' :
	            dir = 1;
	            break;
	        case 'a' :
	            dir = 2;
	            break;
	        case 'd' :
	            dir = 3;
	            break;
	        case 'i' :
	            dir2 = 0;
	            break;
	        case 'k' :
	            dir2 = 1;
	            break;
	        case 'j' :
	            dir2 = 2;
	            break;
	        case 'l' :
	            dir2 = 3;
	            break;
        }
    }

    if(dir != -1 || dir2 != -1)
    {
        int i;
        draw_char(snake1[len1-1].x, snake1[len1-1].y, " ");
        draw_char(snake2[len2-1].x, snake2[len2-1].y, " ");

        for(i = len1 - 1; i > 0; i--)
            snake1[i] = snake1[i-1];
        for(i = len2 - 1; i > 0; i--)
            snake2[i] = snake2[i-1];

        attron(COLOR_PAIR(3));
        draw_char(snake1[1].x, snake1[1].y, "#");
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(5));
        draw_char(snake2[1].x, snake2[1].y, "#");
        attroff(COLOR_PAIR(5));
    }

    switch(dir)
    {
	    case 0:
	        snake1[0].y--;
	        break;
	    case 1:
	        snake1[0].y++;
	        break;
	    case 2:
	        snake1[0].x--;
	        break;
	    case 3:
	        snake1[0].x++;
	        break;
    }
    switch(dir2)
    {
	    case 0:
	        snake2[0].y--;
	        break;
	    case 1:
	        snake2[0].y++;
	        break;
	    case 2:
	        snake2[0].x--;
	        break;
	    case 3:
	        snake2[0].x++;
	        break;
    }

    attron(COLOR_PAIR(2));
    draw_char(snake1[0].x, snake1[0].y, "@");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(6));
    draw_char(snake2[0].x, snake2[0].y, "@");
    attroff(COLOR_PAIR(6));
}

int check_snakes(POS* snake1, int len1, POS* snake2, int len2)
{
    int i, j;

    if(snake1[0].x == 0 || snake1[0].y == 0 || snake1[0].x == 49 || snake1[0].y == 30)
        return 2;

    if(snake2[0].x == 0 || snake2[0].y == 0 || snake2[0].x == 49 || snake2[0].y == 30)
        return 1;

    if(snake1[0].x == snake2[0].x && snake1[0].y == snake2[0].y)
        return 0;

    for(i = 1; i < len1; i++)
        if(snake1[0].x == snake2[i].x && snake1[0].y == snake2[i].y)
            return 1;

    for(j = 1; j < len2; j++)
        if(snake2[0].x == snake1[j].x && snake2[0].y == snake1[j].y)
            return 2;

    return -1;
}
