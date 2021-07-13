/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:57:07 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:06 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_s(char *f, va_list args, char c)
{
	char	*joiner;
	int		hldr;
	char	*str;
	t_flags	flgs;

	ft_searchall(f, c, &flgs, args);
	if (c == 'S' || ft_searchonsize(f, c, 0) == 1)
		joiner = ft_widestring(va_arg(args, wchar_t *));
	else
		joiner = va_arg(args, char *);
	str = joiner ? ft_strdup(joiner) : NULL;
	joiner = NULL;
	if (!str)
		str = ft_strdup("(null)");
	hldr = (int)ft_strlen(str);
	if (flgs.prcsn < hldr && flgs.prcsn >= 0)
		str[flgs.prcsn] = '\0';
	hldr = flgs.prcsn < hldr && flgs.prcsn >= 0 ? flgs.prcsn : hldr;
	if (flgs.minif > hldr)
		joiner = ft_memset(ft_strnew(flgs.minif - hldr), ' ',
		flgs.minif - hldr);
	if (joiner)
		str = !flgs.minus ? ft_fstrjoin(joiner, str) : ft_fstrjoin(str, joiner);
	return (str);
}

char	*ft_c(char *f, char c, va_list args)
{
	char	*str;
	char	mc;
	char	*tmp;
	t_flags flgs;

	tmp = NULL;
	mc = '\0';
	ft_searchall(f, c, &flgs, args);
	if (c == 'C' || ft_searchonsize(f, c, 0) == 1)
		return (ft_wc(flgs, args));
	mc = va_arg(args, int);
	str = ft_strnew(1);
	ft_memset(str, mc != '\0' ? mc : '0', 1);
	if (flgs.minif > 1)
		tmp = flgs.zero ? ft_snbrnew(flgs.minif - 1) :
	ft_memset(ft_strnew(flgs.minif - 1), ' ', flgs.minif - 1);
	if (flgs.minif > 1)
		str = !flgs.minus ? ft_fstrjoin(tmp, str) : ft_fstrjoin(str, tmp);
	ft_printc(str, flgs, mc);
	if (!flgs.minif)
		ft_putchar(mc);
	return (str);
}

char	*ft_percent(char *f, char c, va_list args)
{
	char	*str;
	char	*tmp;
	t_flags	flgs;

	tmp = NULL;
	ft_searchall(f, c, &flgs, args);
	str = ft_strnew(1);
	ft_memset(str, '%', 1);
	if (flgs.minif > 1)
		tmp = flgs.zero ? ft_snbrnew(flgs.minif - 1) :
		ft_memset(ft_strnew(flgs.minif - 1), ' ', flgs.minif - 1);
	if (flgs.minif > 1)
		str = !flgs.minus ? ft_fstrjoin(tmp, str) : ft_fstrjoin(str, tmp);
	return (str);
}

void	ft_printc(char *str, t_flags flgs, char mc)
{
	int i;

	i = 0;
	while (i < flgs.minif)
	{
		if (i == flgs.minus - 1 && mc == '\0')
			ft_putchar('\0');
		else if (mc == '\0' && i == flgs.minif - 1 && !flgs.minus)
			ft_putchar('\0');
		else
			ft_putchar(str[i]);
		i++;
	}
}

char	*ft_wc(t_flags flgs, va_list args)
{
	char *res;
	char *str;
	char *tmp;

	flgs.hash = 0;
	str = NULL;
	res = ft_widechar(va_arg(args, unsigned int));
	if (flgs.minif > 1)
		tmp = flgs.zero ? ft_snbrnew(flgs.minif - 1) :
	ft_memset(ft_strnew(flgs.minif - 1), ' ', flgs.minif - 1);
	if (flgs.minif > 1)
		str = !flgs.minus ? ft_fstrjoin(tmp, res) : ft_fstrjoin(str, res);
	if (!str)
		str = res;
	if (!flgs.minif && res[0] == '\0')
	{
		ft_putchar('\0');
		return (ft_fstrdup(res, "1"));
	}
	if (res[0] == '\0' && flgs.minif)
		ft_printc(str, flgs, '\0');
	else
		ft_putstr(str);
	return (str);
}
