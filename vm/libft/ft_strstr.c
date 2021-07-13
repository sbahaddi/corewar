/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 02:26:45 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/12 23:51:30 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cstrcmp(const char *s1, const char *s2)
{
	while (*s2 != '\0')
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	char	*s;
	char	*n;

	s = (char *)haystack;
	n = (char *)needle;
	if (*n == '\0')
		return (s);
	while (*s != '\0')
	{
		if (ft_cstrcmp(s, needle) == 0)
			return (s);
		s++;
	}
	return (NULL);
}
