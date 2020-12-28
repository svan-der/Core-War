/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:15:50 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/17 14:51:49 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Printing the linked list of champions
*/

void				print_champions(t_env *game)
{
	t_player		*champ;

	champ = game->players;
	while (champ != NULL)
	{
		ft_printf("Champion ID : %i\n", champ->id);
		champ = champ->next;
	}
}

/*
** Printing the linked list of cursors
*/

void				print_cursors(t_env *game)
{
	t_cursor		*cursor;

	cursor = game->cursors;
	while (cursor != NULL)
	{
		ft_printf("Cursor ID : %d\n", cursor->id);
		cursor = cursor->next;
	}
}

/*
** Printing the arena
*/

void				print_dump(t_env *game)
{
	size_t			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0 && i != 0)
			ft_printf("\n");
		if (i % 32 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", game->arena->code[i]);
		i += 1;
	}
	ft_printf("\n");
}

void				print_arena(t_env *game)
{
	size_t			i;
	unsigned char	mem;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_printf("%c", 10);
		else if (i % 1 == 0 && i != 0)
			ft_printf("%c", 32);
		if (game->arena->color[i] != 0)
			ft_printf(ANSI_COLOR_BLUE);
		mem = game->arena->code[i];
		ft_printf("%02x", mem);
		ft_printf(ANSI_COLOR_RESET);
		i++;
	}
	ft_printf("%c", 10);
}
