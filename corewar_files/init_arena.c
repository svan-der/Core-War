/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_arena.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:14:38 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/18 11:15:11 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that loads the executable code of the champions in
** the arena
*/

static int	load_arena(t_env *game)
{
	t_player	*walker;
	int			i;

	walker = game->players;
	while (walker)
	{
		i = 0;
		while (i < walker->data->prog_size)
		{
			game->arena->code[walker->pos + i] = walker->code[i];
			game->arena->color[walker->pos + i] = walker->id;
			i++;
		}
		walker = walker->next;
	}
	return (1);
}

/*
** Function that initializes the arena and sets the position
** of each cursor (one for each champion).
** CAUTION : A Cursor does not belong to a specific champion.
*/

int			init_arena(t_env *game)
{
	game->arena = (t_arena *)ft_memalloc(sizeof(t_arena));
	game->arena->code = ft_strnew_un(MEM_SIZE);
	if (game->arena->code == NULL)
		return (ERROR);
	game->arena->color = ft_strnew_un(MEM_SIZE);
	if (game->arena->color == NULL)
		return (ERROR);
	init_cursors(game);
	load_arena(game);
	return (SUCCESS);
}
