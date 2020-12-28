/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ld.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:59:38 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 18:56:03 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation ld
**
** Usage:
**  Argument 1: T_DIR/T_IND
**  Argument 2: T_REG
**
** Load the first argument into the registry with the index of the second
** argument. If the argument contained no value, set carry to 0.
*/

void		op_ld(t_env *game, t_cursor *cur)
{
	if (cur->op.t_arg[0] == T_IND)
		cur->arg[0] = get_val(game, cur->pos + (cur->arg[0] % IDX_MOD), \
		DIR_SIZE);
	cur->registries[cur->arg[1]] = cur->arg[0];
	if (cur->registries[cur->arg[1]] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
}
