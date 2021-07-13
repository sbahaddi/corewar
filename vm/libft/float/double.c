/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 22:44:34 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:32 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_strdouble(double x, int precision)
{
	t_flt	f;

	f.bf = ft_uconvert((char *)&x, 8);
	f.p = ft_biaspower(f.bf, 1024, 12);
	if ((f.str = ft_special(f.bf, 11)) && f.str[0] != '\0')
	{
		free(f.bf);
		return (f.str);
	}
	f.mnts = ft_mantissa_val(&f.bf[11], ft_status(f.bf, 12));
	f.pown = f.p > 0 ? ft_2power("2", f.p) : ft_2power("5", -f.p);
	f.str = ft_strnew(ft_strlen(f.pown) + ft_strlen(f.mnts) + 1);
	f.str = ft_multiple(f.mnts, f.pown, f.str);
	if (precision && x == 0)
		precision += I(f.bf[0]);
	f.str = ft_pmanager(f.str, f.mnts, precision, f.p);
	if (f.bf[0] == '1')
		f.str = ft_fstrjoin(ft_strdup("-"), f.str);
	if (x == 0 && !precision)
		f.str[1 + I(f.bf[0])] = '\0';
	else if (x == 0)
		f.str[precision + 2] = '\0';
	ft_mulfree(f.mnts, f.pown);
	free(f.bf);
	return (f.str);
}

char		*ft_strldouble(long double x, int precision)
{
	t_flt	f;

	f.bf = ft_uconvert((char *)&x, 10);
	f.p = ft_biaspower(f.bf, 16384, 16);
	if ((f.str = ft_special(f.bf, 15)) && f.str[0] != '\0')
	{
		free(f.bf);
		return (f.str);
	}
	f.mnts = ft_mantissa_val(&f.bf[16], I(f.bf[16]));
	f.pown = f.p > 0 ? ft_2power("2", f.p) : ft_2power("5", -f.p);
	f.str = ft_strnew(ft_strlen(f.pown) + ft_strlen(f.mnts) + 1);
	f.str = ft_multiple(f.mnts, f.pown, f.str);
	f.str = ft_pmanager(f.str, f.mnts, precision, f.p);
	if (x < 0)
		f.str = ft_fstrjoin(ft_strdup("-"), f.str);
	if (x == 0 && !precision)
		f.str[1] = '\0';
	else if (x == 0)
		f.str[precision + 2] = '\0';
	ft_mulfree(f.mnts, f.pown);
	free(f.bf);
	return (f.str);
}

char		*ft_strfillfeg(t_flags flgs, char *nbr)
{
	char *tmp;

	tmp = NULL;
	if (flgs.hash && !flgs.prcsn)
		nbr = ft_fstrjoin(nbr, ft_strdup("."));
	if (flgs.minif > 0)
		tmp = flgs.zero ? ft_snbrnew(flgs.minif) :
		ft_memset(ft_strnew(flgs.minif), ' ', flgs.minif);
	if (flgs.minif > 0 && flgs.zero)
		nbr = ft_fstrjoin(tmp, nbr);
	if (flgs.plus)
		nbr = flgs.plus < 0 ? ft_fstrjoin(ft_strdup("-"), nbr) :
		ft_fstrjoin(ft_strdup("+"), nbr);
	if (flgs.minif > 0 && !flgs.zero)
		nbr = flgs.minus ? ft_fstrjoin(nbr, tmp) : ft_fstrjoin(tmp, nbr);
	return (ft_fstrdup(nbr, nbr));
}

char		*ft_globalfe(char *f, va_list args, char c)
{
	char	*str;
	t_flags	flgs;
	int		len;
	int		a;

	ft_searchall(f, c, &flgs, args);
	str = ft_fe(f, args, c, flgs.prcsn);
	a = ft_ispecial(str, &flgs);
	if (flgs.prcsn >= flgs.minif && a)
		flgs.minif = 0;
	flgs.plus = str[0] == '-' ? -1 : flgs.plus;
	if ((flgs.minif && flgs.zero) || flgs.prcsn > 0 || flgs.plus < 0)
		str = ft_fstrdup(str, flgs.plus == -1 ? str + 1 : str);
	len = ft_strlen(str);
	flgs.hash = flgs.prcsn > 0 ? 0 : flgs.hash;
	flgs.space = flgs.plus ? 0 : flgs.space;
	if ((flgs.space && !flgs.plus && flgs.zero) || flgs.plus || flgs.hash)
		flgs.minif = flgs.minif - (ABS(flgs.plus) + flgs.hash + flgs.space);
	flgs.minif = flgs.minif > len ? flgs.minif - len : 0;
	flgs.zero = flgs.minus ? 0 : flgs.zero;
	str = ft_strfillfeg(flgs, str);
	if (flgs.space)
		str = ft_fstrjoin(ft_strdup(" "), str);
	return (str);
}

char		*ft_fe(char *f, va_list args, char c, int precision)
{
	char	*str;
	int		i;

	str = NULL;
	i = ft_searchonsize(f, c, 1);
	if (i == 1 || c == 'F')
		str = ft_strdouble(va_arg(args, double), precision);
	else if (i == 2)
		str = ft_strldouble(va_arg(args, long double), precision);
	else
		str = ft_strdouble(va_arg(args, double), precision);
	return (str);
}
