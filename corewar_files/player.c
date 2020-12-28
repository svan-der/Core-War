/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 18:54:49 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/17 22:48:38 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		add_player(t_player **head, t_player *new)
{
	if (new == NULL)
		return ;
	new->next = *head;
	*head = new;
}

t_header	*new_header(void)
{
	t_header	*new;

	new = (t_header *)ft_memalloc(sizeof(t_header));
	if (!new)
		return (NULL);
	return (new);
}

t_player	*new_player(void)
{
	t_player	*new;

	new = (t_player *)ft_memalloc(sizeof(t_player));
	if (!new)
		return (NULL);
	new->data = new_header();
	if (!new->data)
		return (NULL);
	return (new);
}

int			save_player(t_env *game, int rank_n, int rank_a)
{
	t_player	*new;

	new = new_player();
	if (!new)
		return (0);
	new->filename = game->argv[rank_a];
	new->rank_n = ft_atoi(game->argv[rank_n]);
	new->rank_a = rank_a;
	add_player(&game->players, new);
	game->champ_count++;
	return (1);
}
