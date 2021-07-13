/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:03:22 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/07 21:20:04 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*ls1;
	char	*ls2;
	size_t	i;

	ls1 = (char *)s1;
	ls2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)*(ls1 + i) != (unsigned char)*(ls2 + i))
			return ((unsigned char)*(ls1 + i) - (unsigned char)*(ls2 + i));
		i++;
	}
	return (0);
}
