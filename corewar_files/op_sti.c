/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sti.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <dsaripap@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/08 18:55:58 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/09/14 20:58:00 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation sti
**
** Usage:
**  Argument 1: T_REG
**  Argument 2: T_REG/T_DIR/T_IND
**  Argument 3: T_REG/T_DIR
**
** Write the value of the first argument at address: 'cursor position + second
** argument + third argument % IDX_MOD'.
*/

void		op_sti(t_env *game, t_cursor *cur)
{
	(void)game;
	if (cur->op.t_arg[0] == T_REG)
		cur->arg[0] = cur->registries[cur->arg[0]];
	if (cur->op.t_arg[1] == T_REG)
		cur->arg[1] = cur->registries[cur->arg[1]];
	else if (cur->op.t_arg[1] == T_IND)
		cur->arg[1] = get_val(game, cur->pos + (cur->arg[1] % IDX_MOD), \
		DIR_SIZE);
	if (cur->op.t_arg[2] == T_REG)
		cur->arg[2] = cur->registries[cur->arg[2]];
	write_mem(game, cur->pos + ((cur->arg[1] + cur->arg[2]) % IDX_MOD), \
	cur->arg[0], REG_SIZE);
}
