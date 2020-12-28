/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_zjmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 14:07:23 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:22:30 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that implements the operation jump
*/

void	op_zjmp(t_env *game, t_cursor *cur)
{
	int	new_pos;

	(void)game;
	if (cur->carry == TRUE)
	{
		new_pos = ((cur->pos + (cur->arg[0] % IDX_MOD)) % MEM_SIZE);
		while (new_pos < 0)
			new_pos += MEM_SIZE;
		cur->pos = new_pos;
	}
}
