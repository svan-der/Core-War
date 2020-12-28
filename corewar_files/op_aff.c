/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_aff.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 20:35:58 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/05 19:44:07 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation aff
**
** Usage:
**  Argument 1: T_REG
**
** Get the value from the registry with the index of the first argument and
** print it to the standard output. By default the aff functionality is
** turned off. User has to enter the '-a' flag before running corewar.
*/

void	op_aff(t_env *game, t_cursor *cur)
{
	(void)game;
	if (cur->op.t_arg[0] == T_REG)
		cur->arg[0] = cur->registries[cur->arg[0]];
	if (game->flag_a == TRUE)
		ft_printf("Aff: %c\n", (char)cur->arg[0]);
}
