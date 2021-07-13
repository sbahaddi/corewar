/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:23:08 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/07 23:48:19 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*rdst;
	char	*rsrc;

	rsrc = (char *)src;
	rdst = (char *)dst;
	i = 0;
	if (rdst > rsrc)
	{
		while ((int)--len >= 0)
			*(rdst + len) = *(rsrc + len);
	}
	else
	{
		while (i < len)
		{
			rdst[i] = rsrc[i];
			i++;
		}
	}
	return (rdst);
}
