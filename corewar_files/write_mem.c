/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_mem.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 16:54:06 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 18:52:13 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	write_mem(t_env *game, int pos, int value, size_t size)
{
	while (pos < 0)
		pos += MEM_SIZE;
	if (size == IND_SIZE)
	{
		game->arena->code[pos % MEM_SIZE] = ((unsigned char *)&value)[1];
		game->arena->code[(pos + 1) % MEM_SIZE] = ((unsigned char *)&value)[0];
	}
	else if (size == DIR_SIZE || size == REG_SIZE)
	{
		game->arena->code[pos % MEM_SIZE] = ((unsigned char *)&value)[3];
		game->arena->code[(pos + 1) % MEM_SIZE] = ((unsigned char *)&value)[2];
		game->arena->code[(pos + 2) % MEM_SIZE] = ((unsigned char *)&value)[1];
		game->arena->code[(pos + 3) % MEM_SIZE] = ((unsigned char *)&value)[0];
	}
}
