/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vsleak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:01:01 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/27 03:59:44 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_fstrlen(char *s, int f)
{
	int i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	if (f)
	{
		free(s);
		s = NULL;
	}
	return (i);
}

char	*ft_fstrjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	str = (char *)ft_memalloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	ft_strcat(str, (char *)s1);
	ft_strcat(str, (char *)s2);
	free(s1);
	free(s2);
	return (str);
}

char	*ft_fstrdup(char *s2, const char *s1)
{
	char	*t;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	t = (char*)malloc(sizeof(char) * (len + 1));
	if (t == NULL)
	{
		t = NULL;
		return (t);
	}
	while (*s1 != '\0')
		*(t + i++) = *s1++;
	*(t + i) = '\0';
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (t);
}

void	ft_mulfree(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
}
