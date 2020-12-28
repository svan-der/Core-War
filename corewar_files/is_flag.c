/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_flag.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:53:59 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:58:43 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** int	is_num(t_env *game, int i)
**  Checks if the given string consists of only digits.
*/

int			is_num(t_env *game, int i)
{
	int	j;

	j = 0;
	if (i >= game->argc)
		return (0);
	while (game->argv[i][j])
	{
		if (ft_isdigit(game->argv[i][j]) == FALSE)
			return (0);
		j++;
	}
	return (1);
}

static int	is_dump_flag(t_env *game, int *i)
{
	int	j;
	int n;

	j = *i;
	if (j < game->argc && !ft_strcmp("-dump", game->argv[j]))
	{
		j++;
		if (j < game->argc && is_num(game, j) == TRUE)
		{
			n = ft_atoi(game->argv[j]);
			if (n > 0)
				game->flag_dump = n;
			else
				exit(ft_printf("[Error] Dump number must be higher than 0\n"));
			*i = j;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	is_a_flag(t_env *game, int *i)
{
	if (*i < game->argc && !ft_strcmp("-a", game->argv[*i]))
	{
		game->flag_a = 1;
		return (TRUE);
	}
	return (FALSE);
}

static int	is_v_flag(t_env *game, int *i)
{
	if (*i < game->argc && !ft_strcmp("-v", game->argv[*i]))
	{
		game->flag_v = 1;
		return (TRUE);
	}
	return (FALSE);
}

/*
** int	is_flag(t_env *game, int *i)
**  Checks if the command line argument is a flag and if
**  the required parameters are specified.
*/

int			is_flag(t_env *game, int *i)
{
	if (is_dump_flag(game, i))
		return (TRUE);
	else if (is_v_flag(game, i))
		return (TRUE);
	else if (is_a_flag(game, i))
		return (TRUE);
	return (FALSE);
}
