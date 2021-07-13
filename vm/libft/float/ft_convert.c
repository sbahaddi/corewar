/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 22:52:28 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:36 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uconvert(char *ptr, int size)
{
	int		i;
	int		j;
	int		l;
	char	*res;

	l = 0;
	res = ft_strnew(size * 8 + 1);
	i = size;
	while (--i >= 0)
	{
		j = 8;
		while (--j >= 0)
		{
			res[l++] = ((*(ptr + i) >> j) & 1) != 0 ? '1' : '0';
		}
	}
	return (res);
}

char	*ft_mantissa_val(char *bf, int one)
{
	int			i;
	t_mantissa	m;

	m.nbrbit = ft_strlen(bf);
	m.res = ft_strnew(m.nbrbit + (m.nbrbit / 4) + 1);
	m.sum = !one ? ft_strdup("0") : ft_strdup("1");
	m.multi = ft_strdup("0");
	i = 0;
	while (++i < m.nbrbit)
	{
		m.sum = ft_fstrdup(m.sum, ft_multiple(m.sum, "10", m.res));
		if (bf[i] == '1')
		{
			ft_mulfree(m.sum, m.multi);
			m.multi = ft_2power("5", i);
			if (ft_strlen(m.multi) > ft_strlen(m.res))
				m.sum = ft_sumx(m.multi, m.res);
			else
				m.sum = ft_sumx(m.res, m.multi);
		}
	}
	ft_mulfree(m.res, m.multi);
	return (m.sum);
}

int		ft_biaspower(char *m, int start, int nbr)
{
	int i;
	int sumres;
	int sub;

	sub = start - 1;
	sumres = 0;
	i = 1;
	while (i < nbr)
	{
		if (m[i] == '1')
			sumres += start;
		i++;
		start /= 2;
	}
	if (sumres == 0)
		return (-(sub - 1));
	return (sumres - sub);
}

int		ft_status(char *f, int nbr)
{
	int i;

	i = 1;
	while (i < nbr)
	{
		if (f[i++] != '0')
			return (1);
	}
	return (0);
}
