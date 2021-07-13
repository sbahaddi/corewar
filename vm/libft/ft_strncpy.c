/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:04:54 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/06 21:44:42 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (*(src + i) != '\0' && i < len)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	while (i < len)
		*(dst + i++) = '\0';
	return (dst);
}
