/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ldi.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 22:33:08 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 20:56:55 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation ldi
**
** Usage:
**  Argument 1: T_REG/T_DIR/T_IND
**  Argument 2: T_REG/T_DIR
**  Argument 3: T_REG
**
** Read four bytes at the address: 'cursor position + first argument +
** second argument % IDX_MOD' and store the result in the registry with the
** index of the third argument.
*/

void		op_ldi(t_env *game, t_cursor *cur)
{
	if (cur->op.t_arg[0] == T_REG)
		cur->arg[0] = cur->registries[cur->arg[0]];
	else if (cur->op.t_arg[0] == T_IND)
		cur->arg[0] = get_val(game, cur->pos + (cur->arg[0] % IDX_MOD), \
		DIR_SIZE);
	if (cur->op.t_arg[1] == T_REG)
		cur->arg[1] = cur->registries[cur->arg[1]];
	cur->registries[cur->arg[2]] = get_val(game, cur->pos + \
	((cur->arg[0] + cur->arg[1]) % IDX_MOD), DIR_SIZE);
}
