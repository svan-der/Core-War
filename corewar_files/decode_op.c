/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decode_op.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 15:27:26 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:41:38 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** int	is_valid_encode_arg(t_env *game, t_cursor *cur)
**
**  Check if the given argument types are valid. The allowed argument types are
**  stored in the 'g_op_tab'.
*/

int		is_valid_encode_arg(t_env *game, t_cursor *cur)
{
	int		i;
	char	byte;

	i = 0;
	byte = game->arena->code[(cur->pos + 1) % MEM_SIZE];
	if ((byte & MASK) != 0)
		return (0);
	while (i < MAX_ARGS_NUMBER - 1)
	{
		if ((g_op_tab[cur->op.id].t_arg[i] & cur->op.t_arg[i]) == FALSE &&
			g_op_tab[cur->op.id].t_arg[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** int	extract_encode_arg(t_env *game, t_cursor *cur)
**
**  Extract the arguments of the encoding byte and store them. The least
**  significant bitpair of that byte must always be 0b00. Check the validity
**  of the arguments in another function.
*/

int		extract_encode_arg(t_env *game, t_cursor *cur)
{
	int		n;
	char	byte;

	n = MAX_ARGS_NUMBER - 1;
	byte = game->arena->code[(cur->pos + 1) % MEM_SIZE];
	while (n)
	{
		n--;
		byte = byte >> 2;
		if ((byte & MASK) == IND_CODE)
			cur->op.t_arg[n] = T_IND;
		else if ((byte & MASK) == DIR_CODE)
			cur->op.t_arg[n] = T_DIR;
		else if ((byte & MASK) == REG_CODE)
			cur->op.t_arg[n] = T_REG;
	}
	if (is_valid_encode_arg(game, cur) == FALSE)
		return (0);
	return (1);
}

int		decode_op(t_env *game, t_cursor *cur)
{
	if (extract_encode_arg(game, cur) == TRUE)
		return (1);
	return (0);
}
