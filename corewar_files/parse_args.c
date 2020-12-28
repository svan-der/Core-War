/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:13:24 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 20:07:10 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** int	is_player(t_env *game, int i)
**  Checks if the command line argument is a valid file (ends in .cor).
*/

static int	is_player(t_env *game, int i)
{
	if (i < game->argc && ft_strstr(game->argv[i], ".cor") != NULL)
		return (1);
	return (0);
}

/*
** int	is_player_nbr(t_env *game, int *i)
**  Checks if the '-n' flag is followed by a number and a player.
*/

static int	is_player_nbr(t_env *game, int *i)
{
	int	j;

	j = *i;
	if (j < game->argc && !ft_strcmp("-n", game->argv[j]))
	{
		j++;
		if (j < game->argc && is_num(game, j) == TRUE)
		{
			j++;
			if (j < game->argc && is_player(game, j) == TRUE)
			{
				*i = j;
				return (1);
			}
		}
	}
	return (0);
}

/*
** int	parse_args(t_env *game)
**  Checks if the command line arguments are valid.
**  ./corewar [flags] [[[-n] [0-9]] [champion.cor]]...
*/

int			parse_args(t_env *game)
{
	int	i;

	i = 1;
	while (i < game->argc)
	{
		if (i < game->argc && is_flag(game, &i) == TRUE)
			i++;
		else
			break ;
	}
	while (i < game->argc)
	{
		if (is_player_nbr(game, &i) == TRUE)
			save_player(game, i - 1, i);
		else if (is_player(game, i) == TRUE)
			save_player(game, 0, i);
		else
			exit(printf("[Error] Usage: ./corewar [-dump number] "
			"[[-n number] file.cor] ...\n"));
		i++;
	}
	return (1);
}
