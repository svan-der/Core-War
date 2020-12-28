/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:14:29 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/15 13:17:08 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	init_oper_array(t_oper *op_arr)
{
	op_arr[0] = NULL;
	op_arr[1] = op_live;
	op_arr[2] = op_ld;
	op_arr[3] = op_st;
	op_arr[4] = op_add;
	op_arr[5] = op_sub;
	op_arr[6] = op_and;
	op_arr[7] = op_or;
	op_arr[8] = op_xor;
	op_arr[9] = op_zjmp;
	op_arr[10] = op_ldi;
	op_arr[11] = op_sti;
	op_arr[12] = op_fork;
	op_arr[13] = op_lld;
	op_arr[14] = op_lldi;
	op_arr[15] = op_lfork;
	op_arr[16] = op_aff;
}

static void	init_game(t_env *game)
{
	t_cursor	*iter;

	iter = game->cursors;
	while (iter)
	{
		iter->last_live = 0;
		iter->decay = 0;
		iter->wait_cycles = 0;
		iter = iter->next;
	}
	game->cursors_count = game->champ_count;
	game->cycles_counter = 0;
	game->cycles_total = 0;
	game->live_counter = 0;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->checks_count = 0;
	game->cycles_since_check = 0;
	game->champ_last_reported = game->cursors->id;
}

void		execute_loop(t_env *game, t_oper *op_array)
{
	t_cursor	*iter;

	game->cycles_since_check++;
	game->cycles_total++;
	iter = game->cursors;
	while (iter != NULL)
	{
		iter->decay++;
		if (iter->wait_cycles == 0)
			set_op(game, iter);
		if (iter->wait_cycles > 0)
			iter->wait_cycles--;
		if (iter->wait_cycles == 0)
			check_op(game, iter, op_array);
		iter = iter->next;
	}
	if (game->cycles_since_check == game->cycles_to_die
	|| game->cycles_to_die < 1)
		check_to_die(game);
}

void		game_loop(t_env *game)
{
	t_oper		op_array[17];

	init_game(game);
	init_oper_array(op_array);
	while (game->cursors != NULL
	&& (game->flag_dump == -1 || (game->flag_dump > game->cycles_total)))
		execute_loop(game, op_array);
}
