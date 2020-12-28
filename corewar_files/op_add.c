/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_add.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 15:56:01 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 14:22:38 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation add
**
** Usage:
**  Argument 1: T_REG
**  Argument 2: T_REG
**  Argument 3: T_REG
**
** Add the registry values with the indexes of the first and second argument
** and store the result in the registry with the index of the third argument.
*/

void	op_add(t_env *game, t_cursor *cur)
{
	(void)game;
	if (cur->op.t_arg[0] == T_REG)
		cur->arg[0] = cur->registries[cur->arg[0]];
	if (cur->op.t_arg[1] == T_REG)
		cur->arg[1] = cur->registries[cur->arg[1]];
	cur->registries[cur->arg[2]] = cur->arg[0] + cur->arg[1];
	if (cur->registries[cur->arg[2]] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
}
