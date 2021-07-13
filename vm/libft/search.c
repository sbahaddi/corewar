/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 01:48:07 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/27 02:25:43 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_searchall(char *f, char c, t_flags *ret, va_list args)
{
	ret->minif = ft_search_zmps(f, c, 5) ? va_arg(args, int) :
	ft_searchnbr(f, c, 1);
	if (ft_search_zmps(f, c, 4))
	{
		ret->prcsn = va_arg(args, int);
		ret->prcsn = ret->prcsn < 0 ? -2 : ret->prcsn;
	}
	else
		ret->prcsn = ft_searchnbr(f, c, 0);
	ret->zero = ft_search_zmps(f, c, 0);
	ret->minus = ft_search_zmps(f, c, 1);
	ret->plus = ft_search_zmps(f, c, 2);
	ret->space = ft_search_zmps(f, c, 3);
	ret->hash = ft_search_zmps(f, c, 6);
	if (ret->minif < 0)
	{
		ret->minus = 1;
		ret->minif = ABS(ret->minif);
	}
	if ((ret->prcsn >= 0 || ret->minus || !ret->minif) && H(c))
		ret->zero = 0;
	if (ret->prcsn >= ret->minif && ATL(c))
		ret->minif = 0;
	ret->prcsn = (ret->prcsn == -1) ? 6 : ret->prcsn;
	ret->space = ret->plus ? 0 : ret->space;
}

int				ft_searchonsize(char *f, char c, int isfloat)
{
	int i;

	i = 0;
	while (*f && *f != c)
	{
		if (*f == 'l' && !isfloat)
			i++;
		if (*f == 'h' && !isfloat)
			i += 10;
		if ((*f == 'l') && isfloat)
			i++;
		if (*f == 'L' && isfloat)
			i = 2;
		if (*f == 'j' && !isfloat)
			i = 6;
		if (*f == 'z' && !isfloat)
			i = 8;
		f++;
	}
	if (i == 10)
		return (3);
	if (i == 20)
		return (4);
	return (i);
}

int				ft_indextoskip(char *f)
{
	int i;

	i = 1;
	if (*f == '%')
	{
		f++;
		i++;
	}
	while (*f != 'd' && *f != 'X' && *f != 'x' && *f != 'i'
			&& *f != 'u' && *f != 'o' && *f != 'f' && *f != 's'
			&& *f != 'c' && *f != 'p' && *f != 'U' && *f != 'O'
			&& *f != '%' && *f != 'D' && *f && *f != 'F' &&
			*f != 'S' && *f != 'C')
	{
		i++;
		f++;
	}
	if (i == 1)
		i++;
	return (i);
}

int				ft_search_zmps(char *cmdf, char c, int zmp)
{
	while (*cmdf != c)
	{
		if (*cmdf == '0' && !ft_isdigit(*(cmdf - 1))
				&& !zmp && *(cmdf - 1) != '.')
			return (1);
		if (*cmdf == '-' && zmp == 1)
			return (1);
		if (*cmdf == '+' && zmp == 2)
			return (1);
		if (*cmdf == ' ' && zmp == 3)
			return (1);
		if (*cmdf == '.' && zmp == 4 && *(cmdf + 1) == '*')
			return (1);
		if (*cmdf == '*' && zmp == 5 && *(cmdf - 1) != '.')
			return (1);
		if (*cmdf == '#' && zmp == 6 && c != 'd' && c != 'i' &&
			c != 's' && c != 'c')
			return (1);
		cmdf++;
	}
	return (0);
}
