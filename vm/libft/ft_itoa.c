/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 21:43:24 by akhourba          #+#    #+#             */
/*   Updated: 2018/12/06 03:23:47 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_getintsize(int n)
{
	int i;

	i = n < 0 ? 1 : 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_getintsize(n);
	if (n == 0)
	{
		str = ft_strnew(len + 1);
		str[0] = '0';
		return (str);
	}
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (--len + 1 > 0)
	{
		if (n < 0)
		{
			str[len] = -(n % 10) + '0';
			n = -n;
		}
		else
			str[len] = (n % 10) + '0';
		n = (n / 10);
	}
	str[0] = str[0] == '0' ? '-' : str[0];
	return (str);
}
