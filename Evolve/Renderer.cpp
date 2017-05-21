#include "Renderer.h"

int main()
{
	int c, mouse_x = 0, mouse_y = 0;
	int py = 0, px = 0;
	WINDOW *map_win, *map_pad, *menu_win;
	//MEVENT event;

	/* Initialize curses */
	initscr();
	resize_term(50, 200);

	menu_win = newwin(1, 200, 0, 0);
	map_win = newwin(HEIGHT, WIDTH, MI_TOP, MI_LEFT);
	map_pad = newpad(MAP_HEIGHT, MAP_WIDTH);

	raw(); noecho(); curs_set(0); nonl(); nodelay(stdscr, 1); keypad(stdscr, 1);

	mouse_set(BUTTON1_CLICKED);

	//box(map_win, 0, 0);
	mvaddch(MI_TOP - 1, MI_LEFT - 1, ACS_ULCORNER);
	mvaddch(MI_TOP - 1, MI_LEFT + WIDTH, ACS_URCORNER);
	mvaddch(MI_TOP + HEIGHT, MI_LEFT - 1, ACS_LLCORNER);
	mvaddch(MI_TOP + HEIGHT, MI_LEFT + WIDTH, ACS_LRCORNER);
	mvhline(MI_TOP - 1, MI_LEFT, ACS_HLINE, WIDTH);
	mvhline(MI_TOP + HEIGHT, MI_LEFT, ACS_HLINE, WIDTH);
	mvvline(MI_TOP, MI_LEFT - 1, ACS_VLINE, HEIGHT);
	mvvline(MI_TOP, MI_LEFT + WIDTH, ACS_VLINE, HEIGHT);

	box(menu_win, 0, 0);
	attron(A_REVERSE);
	mvwprintw(menu_win, 0, 1, "EXIT");
	wnoutrefresh(stdscr);
	wnoutrefresh(menu_win);
	pnoutrefresh(map_pad, py, px, MI_TOP, MI_LEFT, MI_TOP + HEIGHT - 1, MI_LEFT + WIDTH - 1);
	doupdate();
	attroff(A_REVERSE);

	/* Get all the mouse events */

	while (1)
	{
		c = wgetch(stdscr);
		switch (c)
		{
		case KEY_MOUSE:
			request_mouse_pos();
			if (getmouse() == BUTTON1_CLICKED)
			{
				wmouse_position(menu_win, &mouse_y, &mouse_x);
				if (mouse_x < 5 && mouse_y == 0)
				{
					goto end;
				}
				wmouse_position(map_win, &mouse_y, &mouse_x);
				if (mouse_x > -1 && mouse_y > -1)
				{
					mvwprintw(map_pad, mouse_y + py, mouse_x + px, "X");
					mvwprintw(stdscr, 35, 29, "%4d, %4d", mouse_y + py, mouse_x + px);
				}
			}
			break;
		case KEY_UP:
			if (py > 0)
				py--;
			break;
		case KEY_DOWN:
			if (py + HEIGHT < MAP_HEIGHT)
				py++;
			break;
		case KEY_LEFT:
			if (px > 0)
				px--;
			break;
		case KEY_RIGHT:
			if (px + WIDTH < MAP_WIDTH)
				px++;
			break;
		}
		wnoutrefresh(stdscr);
		wnoutrefresh(menu_win);
		pnoutrefresh(map_pad, py, px, MI_TOP, MI_LEFT, MI_TOP + HEIGHT - 1, MI_LEFT + WIDTH - 1);
		doupdate();
	}
end:
	endwin();
	return 0;
}