/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:13:56 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/15 13:08:49 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	intro_player(t_env *game, int id)
{
	t_player	*walker;

	walker = game->players;
	while (walker)
	{
		if (walker->id == id)
			ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n", \
			id, walker->data->prog_size, walker->data->prog_name, \
			walker->data->comment);
		walker = walker->next;
	}
}

static void	report_winner(t_env *game)
{
	t_player	*iter;
	int			found;

	iter = game->players;
	found = 0;
	while (iter)
	{
		if (iter->id == game->champ_last_reported)
		{
			found = 1;
			break ;
		}
		iter = iter->next;
	}
	if (found == 1)
		ft_printf("Contestant %i, \"%s\", has won !\n",
		iter->id, iter->data->prog_name);
}

static void	introduction(t_env *game)
{
	int		id;

	id = 1;
	ft_printf("Introducing contestants...\n");
	while (id <= game->champ_count)
	{
		intro_player(game, id);
		id++;
	}
}

int			main(int argc, char **argv)
{
	t_env	*game;

	if (argc < 2)
		exit(ft_printf("[Error] Usage: ./corewar [-dump number] "
		"[[-n number] .cor] ...\n"));
	game = new_env(argc, argv);
	if (parse_args(game) == FALSE)
		return (0);
	read_champion(game);
	if (assign_id(game) == FALSE)
		return (0);
	introduction(game);
	init_arena(game);
	if (game->flag_v == 1)
		visualizer(game);
	game_loop(game);
	if (game->flag_dump >= 0 && game->cycles_total >= game->flag_dump)
	{
		print_dump(game);
		free_env(&game);
		return (SUCCESS);
	}
	report_winner(game);
	free_env(&game);
	return (0);
}
