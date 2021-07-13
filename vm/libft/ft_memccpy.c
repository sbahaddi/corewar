/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 00:31:16 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/07 15:22:15 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char *t;

	t = dst;
	while (n--)
	{
		*(t) = *(unsigned char *)(src++);
		if (*(unsigned char *)t++ == (unsigned char)c)
			return (t);
	}
	return (NULL);
}
