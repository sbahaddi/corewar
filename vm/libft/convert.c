/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 01:39:51 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/26 01:14:56 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(long long int x, int bsnbr)
{
	long	res;
	char	*str;
	long	l;
	char	*base;

	base = ft_strdup("0123456789abcdef");
	res = x;
	l = ft_intlengh(res, bsnbr);
	str = x < 0 ? ft_strnew(l + 1) : ft_strnew(l);
	while (l--)
	{
		if (res < 0)
			str[l + 1] = base[-(res % bsnbr)];
		else
			str[l] = base[(res % bsnbr)];
		res /= bsnbr;
	}
	str[0] = x < 0 ? '-' : str[0];
	free(base);
	return (str);
}

char	*ft_uitoa_base(unsigned long long int x, int bsnbr)
{
	unsigned long long int	res;
	char					*str;
	long int				l;
	char					*base;

	base = ft_strdup("0123456789abcdef");
	res = x;
	l = ft_uintlengh(res, bsnbr);
	str = ft_strnew(l);
	while (l--)
	{
		str[l] = base[(res % bsnbr)];
		res /= bsnbr;
	}
	free(base);
	return (str);
}

int		ft_intlengh(long long int nbr, int base)
{
	int i;

	i = 0;
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	if (!i)
		return (1);
	return (i);
}

int		ft_uintlengh(unsigned long long int nbr, unsigned int base)
{
	int i;

	i = 0;
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	if (!i)
		return (1);
	return (i);
}

char	ft_searchflag(char *f)
{
	while (*f)
	{
		if (!((*f != 'd' && *f != 'X' && *f != 'x' && *f != 'i'
			&& *f != 'u' && *f != 'o' && *f != 'f' && *f != 's'
			&& *f != 'c' && *f != 'p' && *f != 'U' && *f != 'O'
			&& *f != '%' && *f != 'D' && *f && *f != 'S' && *f != 'C')))
			return (*f);
		f++;
	}
	return (0);
}
