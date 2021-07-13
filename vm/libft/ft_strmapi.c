/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:56:23 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/09 22:01:37 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		*(str + i) = f(i, *((char *)(s + i)));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
