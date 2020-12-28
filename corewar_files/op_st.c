/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_st.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 20:05:06 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 20:57:55 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation store
**
** Usage:
**  Argument 1: T_REG
**  Argument 2: T_REG/T_IND
**
** Write the value of the registry with the index of the first
** argument either into the virtual machine memory at the current address +
** the second argument (T_IND) or store it in the registry with the index of
** the second argument (T_REG);
*/

void		op_st(t_env *game, t_cursor *cur)
{
	if (cur->op.t_arg[0] == T_REG)
		cur->arg[0] = cur->registries[cur->arg[0]];
	if (cur->op.t_arg[1] == T_REG)
		cur->registries[cur->arg[1]] = cur->arg[0];
	else if (cur->op.t_arg[1] == T_IND)
		write_mem(game, cur->pos + (cur->arg[1] % IDX_MOD), cur->arg[0], \
		REG_SIZE);
}
