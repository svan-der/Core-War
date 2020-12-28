/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_champion2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 14:12:25 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:00:06 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	read_magic_header(int fd, t_player *new)
{
	int	rd;

	rd = read(fd, &new->data->magic, 4);
	if (rd < 0)
		exit(ft_printf("[Error] Unable to read: %s\n", new->filename));
	if (rd < 4)
		exit(ft_printf("[Error] Read too few bytes for magic header\n"));
	reverse_mem(&new->data->magic, 3);
	if (new->data->magic != COREWAR_EXEC_MAGIC)
		exit(ft_printf("[Error] Magic header is invalid\n"));
}

void	read_prog_name_length(int fd, t_player *new)
{
	int	rd;

	rd = read(fd, &new->data->prog_name, PROG_NAME_LENGTH);
	if (rd < 0)
		exit(ft_printf("[Error] Unable to read: %s\n", new->filename));
	if (rd < PROG_NAME_LENGTH)
		exit(ft_printf("[Error] Read too few bytes for program name\n"));
}

void	read_null_bytes(int fd, t_player *new)
{
	int	rd;
	int	buff;

	rd = read(fd, &buff, 4);
	if (rd < 0)
		exit(ft_printf("[Error] Unable to read: %s\n", new->filename));
	if (rd < 4)
		exit(ft_printf("[Error] Read too few bytes\n"));
	if (buff != 0)
		exit(ft_printf("[Error] Missing 4 null bytes after program name\n"));
}
