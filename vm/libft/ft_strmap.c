/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:38:44 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/09 22:01:15 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = ft_memalloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!str)
		return (NULL);
	while (*(s + i))
	{
		*(str + i) = f(*((char *)(s + i)));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
