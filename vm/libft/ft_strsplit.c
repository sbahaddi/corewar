/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:05:17 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/14 22:10:29 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			get_ttsize(char const *s, char c)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			i++;
		s++;
	}
	return (i);
}

static int			get_tsize(char const *s, char c)
{
	int i;

	i = 0;
	while (*(s + i) != c && *(s + i))
		i++;
	return (i);
}

char				**ft_strsplit(char const *s, char c)
{
	int		i;
	int		len;
	char	**str;
	int		j;

	j = -1;
	i = 0;
	if (!s)
		return (NULL);
	len = get_ttsize(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (++j < len)
	{
		while (*s == c)
			s++;
		i = get_tsize(s, c);
		if (!(*(str + j) = (char *)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		*(str + j) = ft_strncpy(*(str + j), s, (size_t)i);
		str[j][i] = '\0';
		s = s + i;
	}
	str[j] = 0;
	return (str);
}
