/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_arena_ncurses.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:15:43 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:22:19 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void			create_pairs(void)
{
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
}

static int			setup_print_arena_ncurses(t_pan_wrap *wrap,
												t_env *game,
												WINDOW *win)
{
	wrap->tmp_arena = game->arena;
	wrap->i = 0;
	wrap->x = 2;
	wrap->y = 1;
	if (!has_colors())
	{
		printw("Colors are not supported!");
		getch();
		return (ERROR);
	}
	start_color();
	create_pairs();
	wmove(win, wrap->y, wrap->x);
	erase();
	return (SUCCESS);
}

/*
** Printing the arena code with ncurses
*/

static void			if_not_zero_print_arena_ncurses(t_pan_wrap *wrap,
													WINDOW *win)
{
	wattron(win, COLOR_PAIR(wrap->tmp_arena->color[wrap->i]));
	refresh();
	wprintw(win, "%02x ", wrap->c);
	wrefresh(win);
	wattroff(win, COLOR_PAIR(wrap->tmp_arena->color[wrap->i]));
}

int					print_arena_ncurses(t_env *game, WINDOW *win)
{
	t_pan_wrap		wrap;

	if (setup_print_arena_ncurses(&wrap, game, win) == ERROR)
		return (ERROR);
	wrap.i = 0;
	while (wrap.i < MEM_SIZE)
	{
		wrap.c = wrap.tmp_arena->code[wrap.i];
		if (wrap.i % 64 == 0 && wrap.i != 0)
		{
			wrap.y += 1;
			wrap.x = 2;
			wmove(win, wrap.y, wrap.x);
		}
		if (wrap.tmp_arena->color[wrap.i] != '0')
		{
			if_not_zero_print_arena_ncurses(&wrap, win);
		}
		else
			wprintw(win, "%02x ", wrap.c);
		wrap.x += 1;
		wrap.i += 1;
	}
	wrefresh(game->vis->code_win);
	return (SUCCESS);
}
