/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_mem.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 14:11:05 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/05 21:44:04 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	reverse_mem(void *s, size_t n)
{
	size_t			i;
	unsigned char	c;
	unsigned char	*mem;

	i = 0;
	mem = (unsigned char *)s;
	while (i < n - i)
	{
		c = mem[i];
		mem[i] = mem[n - i];
		mem[n - i] = c;
		i++;
	}
}
