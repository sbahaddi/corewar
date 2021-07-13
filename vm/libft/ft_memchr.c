/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:42:39 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/07 21:03:11 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*lc;
	size_t	i;

	i = 0;
	lc = (char *)s;
	while (i < n)
	{
		if ((unsigned char)*(lc + i) == (unsigned char)c)
			return (lc + i);
		i++;
	}
	return (NULL);
}
