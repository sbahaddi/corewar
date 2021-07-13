/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:56:16 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:54 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_multiple(char *n1, char *n2, char *res)
{
	t_mu m;

	m.l1 = ft_strlen(n1);
	m.l2 = ft_strlen(n2);
	ft_memset(res, '0', m.l2 + m.l1);
	res[m.l2 + m.l1] = '\0';
	m.i = m.l1;
	m.sm = 0;
	while (--m.i >= 0)
	{
		m.j = m.l2;
		m.k = m.i + m.j + 1;
		while (--m.j >= 0 && --m.k >= 0)
		{
			m.sm = I(n1[m.i]) * I(n2[m.j]) + I(res[m.k]) + m.sm;
			res[m.k] = C(m.sm);
			m.sm = m.sm / 10;
		}
		res[m.k - 1] += m.sm;
		m.sm /= 10;
	}
	if (res[0] == '0')
		ft_memmove(res, res + 1, m.l1 + m.l2);
	return (res);
}

char		*ft_2power(char *nbr, int pow)
{
	t_pow	p;

	if (!pow || pow == 1)
		return (pow != 0 ? ft_strdup(nbr) : ft_strdup("1"));
	p.x = ft_strdup("1");
	p.tmp = ft_strdup(nbr);
	p.i = pow;
	p.res = ft_strnew((pow) * ft_strlen(nbr) + 1);
	while (p.i > 1)
	{
		if (p.i % 2 != 0)
		{
			p.x = ft_fstrdup(p.x, ft_multiple(p.x, p.tmp, p.res));
			ft_multiple(p.tmp, p.tmp, p.res);
		}
		else
			ft_multiple(p.tmp, p.tmp, p.res);
		p.tmp = ft_fstrdup(p.tmp, p.res);
		p.i /= 2;
	}
	ft_multiple(p.x, p.tmp, p.res);
	ft_mulfree(p.x, p.tmp);
	return (p.res);
}

char		*ft_sumx(char *nbr1, char *nbr2)
{
	t_sum	a;
	char	*res;

	a.sm = 0;
	a.i = ft_strlen(nbr1);
	a.j = ft_strlen(nbr2) - 1;
	res = ft_strnew(a.i);
	ft_memset(res, '0', a.i + 1);
	while (--a.i >= 0)
	{
		if (a.j >= 0)
			a.sm = I(nbr1[a.i]) + I(nbr2[a.j--]) + a.sm;
		else
			a.sm = I(nbr1[a.i]) + a.sm;
		res[a.i + 1] = C(a.sm);
		a.sm /= 10;
	}
	res[a.i + 1] = C(a.sm);
	a.i = ft_strlen(nbr1);
	if (res[0] == '0')
	{
		ft_memmove(res, res + 1, a.i);
		res[a.i] = '\0';
	}
	return (res);
}

int			ft_pow(int nb, int power)
{
	int f;

	f = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
	{
		while (power != 0)
		{
			f *= nb;
			power--;
		}
	}
	return (f);
}
