/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_op_arg.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 15:39:40 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 20:07:56 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_op_arg_size(int op, int arg)
{
	if (arg == T_REG)
		return (1);
	if (arg == T_IND)
		return (2);
	if (arg == T_DIR && g_op_tab[op].label_size == FALSE)
		return (4);
	if (arg == T_DIR && g_op_tab[op].label_size == TRUE)
		return (2);
	return (0);
}

/*
** Reads single byte and cast the result to an integer.
*/

int		get_reg(t_env *game, int offset)
{
	unsigned char	arg;

	while (offset < 0)
		offset += MEM_SIZE;
	arg = game->arena->code[offset % MEM_SIZE];
	return ((int)arg);
}

/*
** Reads size bytes in reverseorder and cast the result to an integer.
*/

int		get_val(t_env *g, int offset, size_t size)
{
	int				arg;

	while (offset < 0)
		offset += MEM_SIZE;
	if (size == IND_SIZE)
	{
		((unsigned char *)&arg)[1] = g->arena->code[offset % MEM_SIZE];
		((unsigned char *)&arg)[0] = g->arena->code[(offset + 1) % MEM_SIZE];
		return ((short)arg);
	}
	((unsigned char *)&arg)[3] = g->arena->code[offset % MEM_SIZE];
	((unsigned char *)&arg)[2] = g->arena->code[(offset + 1) % MEM_SIZE];
	((unsigned char *)&arg)[1] = g->arena->code[(offset + 2) % MEM_SIZE];
	((unsigned char *)&arg)[0] = g->arena->code[(offset + 3) % MEM_SIZE];
	return (arg);
}

/*
** Get the values of the arguments given by either the encoding byte, or
** if no encoding byte is present, from the g_op_tab struct.
** Skips the operation byte and encoding byte if applicable.
*/

int		get_op_arg(t_env *game, t_cursor *cur)
{
	int				n;
	int				offset;

	n = 0;
	offset = g_op_tab[cur->op.id].encode == TRUE ? 2 : 1;
	while (n < MAX_ARGS_NUMBER - 1)
	{
		if (cur->op.t_arg[n] == T_DIR)
			cur->arg[n] = get_val(game, cur->pos + offset,
			g_op_tab[cur->op.id].label_size == TRUE ? IND_SIZE : DIR_SIZE);
		else if (cur->op.t_arg[n] == T_IND)
			cur->arg[n] = get_val(game, cur->pos + offset, IND_SIZE);
		else if (cur->op.t_arg[n] == T_REG)
		{
			cur->arg[n] = get_reg(game, cur->pos + offset);
			if (cur->arg[n] < 1 || cur->arg[n] > REG_NUMBER)
				return (0);
		}
		offset += get_op_arg_size(cur->op.id, cur->op.t_arg[n]);
		n++;
	}
	return (1);
}
