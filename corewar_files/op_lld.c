/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_lld.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 17:12:16 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 14:29:27 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation lld
**
** Usage:
**  Argument 1: T_DIR/T_IND
**  Argument 2: T_REG
**
** Load the first argument into the registry with the index of the second
** argument. Don't truncate the argument in case of T_IND.
*/

void	op_lld(t_env *game, t_cursor *cur)
{
	if (cur->op.t_arg[0] == T_IND)
		cur->arg[0] = get_val(game, cur->pos + cur->arg[0], DIR_SIZE);
	cur->registries[cur->arg[1]] = cur->arg[0];
	if (cur->registries[cur->arg[1]] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
}
