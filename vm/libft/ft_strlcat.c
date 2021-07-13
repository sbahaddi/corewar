/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:20:22 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/11 16:36:24 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lndst;
	size_t	lnsrc;
	size_t	i;

	lnsrc = ft_strlen((char *)src);
	lndst = ft_strlen(dst);
	i = 0;
	if (lndst + 1 > size)
		return (lnsrc + size);
	else if (lndst + 1 < size)
	{
		while (lndst + i < size - 1 && i < lnsrc)
		{
			*(dst + lndst + i) = *(src + i);
			i++;
		}
		*(dst + lndst + i) = '\0';
	}
	return (lndst + lnsrc);
}
