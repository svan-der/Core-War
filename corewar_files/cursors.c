/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:14:03 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:14:05 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Function that adds a new cursor at the beginning of the
** linked list of cursors. We save them like this because
** last cursor is executed first.
*/

void		add_cursor(t_cursor **head, t_cursor *new)
{
	if (new == NULL)
		return ;
	new->next = *head;
	*head = new;
}

t_cursor	*new_cursor(void)
{
	t_cursor	*new;

	new = (t_cursor *)ft_memalloc(sizeof(t_cursor));
	if (new == NULL)
		exit(ft_printf("[Error] Failed memory allocation\n"));
	return (new);
}

void		init_cursors(t_env *game)
{
	t_cursor	*new;
	t_player	*champ;
	int			id;

	id = 1;
	while (id <= game->champ_count)
	{
		new = new_cursor();
		if (new == NULL)
			exit(ft_printf("[Error] Failed memory allocation for cursur\n"));
		game->cursor_total++;
		champ = get_id(game, id);
		if (!champ)
			exit(ft_printf("[Error] Could not find player ID\n"));
		new->pos = (MEM_SIZE / game->champ_count) * (id - 1);
		champ->pos = new->pos;
		new->id = id;
		new->pid = id;
		new->registries[1] = id * -1;
		add_cursor(&game->cursors, new);
		id++;
	}
}
