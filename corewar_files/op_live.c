/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_live.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 21:48:19 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 14:23:37 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation live
**
** Usage:
**  Argument 1: T_DIR
**
** Whenever the given argument and the value of the first registry are equal,
** the player with that id ,if it's still in the game, is reported alive.
*/

void		op_live(t_env *game, t_cursor *cur)
{
	if (0 < -cur->arg[0] && -cur->arg[0] <= game->champ_count)
		game->champ_last_reported = -cur->arg[0];
	game->live_counter++;
	cur->decay = 0;
	cur->last_live = game->cycles_total;
}
