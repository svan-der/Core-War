/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_champion1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 14:13:44 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/18 11:18:21 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	read_prog_size(int fd, t_player *new)
{
	int	rd;

	rd = read(fd, &new->data->prog_size, 4);
	if (rd < 0)
		exit(ft_printf("[Error] Unable to read: %s\n", new->filename));
	if (rd < 4)
		exit(ft_printf("[Error] Read too few bytes for program size\n"));
	reverse_mem(&new->data->prog_size, 3);
	if (new->data->prog_size > CHAMP_MAX_SIZE || new->data->prog_size < 0)
		exit(ft_printf("[Error] Program size of %s: %i is wrong\n", \
		new->filename, new->data->prog_size));
}

void	read_comment(int fd, t_player *new)
{
	int	rd;

	rd = read(fd, &new->data->comment, COMMENT_LENGTH);
	if (rd < 0)
		exit(ft_printf("[Error] Unable to read: %s\n", new->filename));
	if (rd < COMMENT_LENGTH)
		exit(ft_printf("[Error] Read too few bytes for comment\n"));
}

void	read_champion_code(int fd, t_player *new)
{
	int	rd;

	rd = read(fd, new->code, CHAMP_MAX_SIZE + 1);
	if (rd < 0)
		exit(ft_printf("[Error] Unable to read: %s\n", new->filename));
	if (rd > CHAMP_MAX_SIZE)
		exit(ft_printf("[Error] Program size of %s: %i exceeds the maximum " \
		"size: %i\n", new->filename, new->data->prog_size, CHAMP_MAX_SIZE));
	if (rd != (int)new->data->prog_size)
		exit(ft_printf("[Error] Program size of %s: %i differs from size " \
		"in code: %i\n", new->filename, new->data->prog_size, rd));
}

int		read_file(t_player *new)
{
	int	fd;

	fd = open(new->filename, O_RDONLY);
	if (fd < 0)
		exit(ft_printf("[Error] Failed to open: %s\n", new->filename));
	read_magic_header(fd, new);
	read_prog_name_length(fd, new);
	read_null_bytes(fd, new);
	read_prog_size(fd, new);
	read_comment(fd, new);
	read_null_bytes(fd, new);
	read_champion_code(fd, new);
	close(fd);
	return (1);
}

int		read_champion(t_env *arena)
{
	t_player	*walker;

	if (arena == NULL)
		exit(ft_printf("[Error] Missing arena\n"));
	if (arena->players == NULL)
		exit(ft_printf("[Error] Missing players\n"));
	walker = arena->players;
	while (walker)
	{
		read_file(walker);
		walker = walker->next;
	}
	return (1);
}
