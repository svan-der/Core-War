/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/15 12:11:54 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/15 12:24:12 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	kill_cursor(t_env *game, t_cursor *cur, t_cursor *prev, \
t_cursor *next)
{
	if (prev == NULL)
	{
		if (next == NULL)
			game->cursors = NULL;
		else
			game->cursors = next;
	}
	else
		prev->next = next;
	ft_memdel((void **)&cur);
}

static void	remove_dead_cursors(t_env *game, t_cursor **head)
{
	t_cursor	*next;
	t_cursor	*prev;
	t_cursor	*iter;

	prev = NULL;
	iter = *head;
	while (iter)
	{
		next = iter->next;
		if (iter->decay >= game->cycles_to_die ||
		game->cycles_to_die <= 0)
			kill_cursor(game, iter, prev, next);
		else
			prev = iter;
		iter = next;
	}
}

static void	update_cycles_to_die(t_env *game)
{
	if (game->live_counter >= NBR_LIVE || game->checks_count == MAX_CHECKS)
	{
		game->cycles_to_die -= CYCLE_DELTA;
		game->checks_count = 0;
	}
}

void		check_to_die(t_env *game)
{
	game->checks_count++;
	remove_dead_cursors(game, &game->cursors);
	update_cycles_to_die(game);
	game->cycles_since_check = 0;
	game->live_counter = 0;
}
