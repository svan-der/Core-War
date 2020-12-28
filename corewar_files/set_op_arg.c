/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_op_arg.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 16:17:52 by rheuts        #+#    #+#                 */
/*   Updated: 2020/08/31 16:18:58 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Set the type of argument(s) for the operation.
*/

int		set_op_arg(t_env *game, t_cursor *cur)
{
	if (g_op_tab[cur->op.id].encode == TRUE)
		return (decode_op(game, cur));
	else
		cur->op.t_arg[0] = T_DIR;
	return (1);
}
