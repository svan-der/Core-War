/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnew_un.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaripap <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 14:10:34 by dsaripap      #+#    #+#                 */
/*   Updated: 2020/08/28 13:38:10 by dsaripap      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned char		*ft_strnew_un(size_t size)
{
	size_t			i;
	unsigned char	*result;

	result = (unsigned char *)malloc(sizeof(unsigned char) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = 0;
		i++;
	}
	result[i] = '\0';
	return (result);
}
