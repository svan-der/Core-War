/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 15:25:38 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/09/08 20:07:34 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int					print_cursors_info(t_env *game, WINDOW *win, int y)
{
	t_cursor		*tmp;

	mvwprintw(win, y, 2, "Cursors Info");
	y += 1;
	tmp = game->cursors;
	while (tmp)
	{
		y += 1;
		mvwprintw(win, y, 2, "Player ID : %d", tmp->id);
		y += 1;
		mvwprintw(win, y, 2, "Cursor Position : %d", tmp->pos);
		y += 1;
		mvwprintw(win, y, 2, "Cursor Last Live : %d", tmp->last_live);
		y += 1;
		mvwprintw(win, y, 2, "Cursor Wait Cycles : %d", tmp->wait_cycles);
		y += 1;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int					print_info(t_env *game, WINDOW *win)
{
	int				y;

	y = 1;
	mvwprintw(win, y, 2, "Cycles : %d", game->cycles_counter);
	y += 1;
	mvwprintw(win, y, 2, "Live Counter : %d", game->live_counter);
	y += 1;
	mvwprintw(win, y, 2, "Cycles to Die : %d", game->cycles_to_die);
	y += 1;
	mvwprintw(win, y, 2, "Checks Count : %d", game->checks_count);
	y += 1;
	mvwprintw(win, y, 2, "Player Last Live : %d", game->champ_last_reported);
	y += 1;
	mvwprintw(win, y, 2, "-------------------------");
	y += 1;
	mvwprintw(win, y, 2, "Cycles Delta : %d", CYCLE_DELTA);
	y += 1;
	mvwprintw(win, y, 2, "-------------------------");
	y += 1;
	print_cursors_info(game, win, y);
	wrefresh(game->vis->info_win);
	return (SUCCESS);
}

static void			create_win_code(WINDOW **win)
{
	int				height;
	int				width;
	int				start_y;
	int				start_x;

	height = (MEM_SIZE / 64) + 2;
	width = (64 * 3) + 3;
	start_y = 0;
	start_x = 0;
	*win = newwin(height, width, start_y, start_x);
}

static void			create_win_info(WINDOW **win)
{
	int				height;
	int				width;
	int				start_y;
	int				start_x;

	height = (MEM_SIZE / 64) + 2;
	width = 40;
	start_y = 0;
	start_x = (64 * 3) + 3;
	*win = newwin(height, width, start_y, start_x);
}

void				visualizer(t_env *game)
{
	game->vis = (t_vis *)ft_memalloc(sizeof(t_vis));
	initscr();
	noecho();
	curs_set(TRUE);
	refresh();
	create_win_code(&game->vis->code_win);
	box(game->vis->code_win, 0, 0);
	print_arena_ncurses(game, game->vis->code_win);
	create_win_info(&game->vis->info_win);
	box(game->vis->info_win, 0, 0);
	print_info(game, game->vis->info_win);
}
