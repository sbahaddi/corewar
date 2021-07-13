/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 09:47:37 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/14 17:54:57 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_get(int *i, int *len, char *s)
{
	while (ft_iswspace(*(s + *i)))
		*i += 1;
	while (ft_iswspace(s[*len - 1]))
		*len -= 1;
	if (*i > *len)
		*i = 0;
}

char			*ft_strtrim(char const *s)
{
	int		i;
	char	*str;
	int		len;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen((char *)s);
	ft_get(&i, &len, (char *)s);
	str = (char *)ft_memalloc(sizeof(char) * (len - i + 1));
	if (!str)
		return (NULL);
	while (i < len && *(s + i))
	{
		*(str + j) = *(s + i);
		j++;
		i++;
	}
	*(str + j) = '\0';
	return (str);
}
