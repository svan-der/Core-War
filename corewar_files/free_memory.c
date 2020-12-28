/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:14:24 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 20:43:33 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	free_players(t_player **player)
{
	t_player	*walker;
	t_player	*next;

	if (*player == NULL)
		return ;
	walker = *player;
	while (walker)
	{
		next = walker->next;
		ft_memdel((void **)&(walker->data));
		ft_memdel((void **)&(walker));
		walker = next;
	}
}

void	free_cursors(t_cursor **head)
{
	t_cursor	*walker;
	t_cursor	*next;

	if (*head == NULL)
		return ;
	walker = *head;
	while (walker)
	{
		next = walker->next;
		ft_memdel((void **)&(walker));
		walker = next;
	}
}

void	free_env(t_env **game)
{
	if (*game == NULL)
		return ;
	if ((*game)->players != NULL)
		free_players(&(*game)->players);
	if ((*game)->cursors != NULL)
		free_cursors(&(*game)->cursors);
	ft_memdel((void **)&(*game)->arena->code);
	ft_memdel((void **)&(*game)->arena->color);
	ft_memdel((void **)&(*game)->arena);
	ft_memdel((void **)game);
}
