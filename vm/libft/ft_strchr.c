/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 01:46:34 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/08 02:11:51 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*sr;

	sr = (char *)s;
	i = ft_strlen((char *)s);
	if ((char)c == '\0')
		return (sr + i);
	i = 0;
	while (*(sr + i) != '\0')
	{
		if (*(char *)(sr + i) == (char)c)
			return (sr + i);
		i++;
	}
	return (NULL);
}
