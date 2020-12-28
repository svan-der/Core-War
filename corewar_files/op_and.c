/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_and.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 20:40:59 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 18:56:18 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation and
**
** Usage:
**  Argument 1: T_REG/T_DIR/T_IND
**  Argument 2: T_REG/T_DIR/T_IND
**  Argument 3: T_REG
**
** Apply the bitwise '&' operator on the first and second argument and
** store the result in the registry with the index of the third
** argument.
*/

void		op_and(t_env *game, t_cursor *cur)
{
	if (cur->op.t_arg[0] == T_REG)
		cur->arg[0] = cur->registries[cur->arg[0]];
	else if (cur->op.t_arg[0] == T_IND)
		cur->arg[0] = get_val(game, cur->pos + (cur->arg[0] % IDX_MOD), \
		DIR_SIZE);
	if (cur->op.t_arg[1] == T_REG)
		cur->arg[1] = cur->registries[cur->arg[1]];
	else if (cur->op.t_arg[1] == T_IND)
		cur->arg[1] = get_val(game, cur->pos + (cur->arg[1] % IDX_MOD), \
		DIR_SIZE);
	cur->registries[cur->arg[2]] = (cur->arg[0] & cur->arg[1]);
	if (cur->registries[cur->arg[2]] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
}
