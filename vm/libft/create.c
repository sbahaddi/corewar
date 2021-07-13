/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:39:23 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/27 04:02:32 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_snbrnew(size_t size)
{
	char *str;

	str = ft_strnew(size);
	ft_memset(str, '0', size);
	return (str);
}

char	*ft_point(char *nbr, int pos, int x, int s)
{
	char	*res;
	int		l;
	int		i;
	int		point;

	point = 0;
	i = -1;
	l = ft_strlen(nbr) - s;
	res = ft_snbrnew(l + 1);
	while (++i <= l)
	{
		res[i + x] = nbr[i - point + s];
		if (i == pos)
		{
			res[i + x] = '.';
			point = 1;
		}
	}
	free(nbr);
	return (res);
}

char	*ft_strfillwith(t_flags flgs, int len, char *nbr)
{
	char *str;
	char *tmp;

	tmp = "\0";
	if (flgs.minif > len && flgs.zero)
	{
		flgs.prcsn = flgs.minif - len - (flgs.prcsn > 0 ? flgs.prcsn : 0);
		flgs.minif = 0;
	}
	if (flgs.prcsn > 0)
		tmp = ft_strjoin(ft_snbrnew(flgs.prcsn), nbr);
	else if (!flgs.prcsn && flgs.plus == 1)
		tmp = ft_strjoin(ft_snbrnew(1), nbr);
	str = tmp[0] != '\0' ? ft_strdup(tmp) : nbr;
	if (tmp[0] != '\0')
		free(tmp);
	if (flgs.prcsn >= 0 && flgs.plus)
		str[0] = flgs.plus > 0 ? '+' : '-';
	flgs.minif = flgs.minif > 0 ? flgs.minif - ft_strlen(str) : 0;
	if (flgs.minif > 0)
		tmp = ft_memset(ft_strnew(flgs.minif), ' ', flgs.minif);
	if (flgs.minif > 0)
		str = flgs.minus ? ft_strjoin(str, tmp) : ft_strjoin(tmp, str);
	return (str);
}
