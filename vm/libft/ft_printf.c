/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 02:22:57 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/27 06:43:02 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *restrict f, ...)
{
	int		ret;
	va_list	args;

	ret = 0;
	va_start(args, f);
	while (*f)
	{
		if (*f == '%')
		{
			ret += ft_glolbal((char *)(f + 1), args);
			f += ft_indextoskip((char *)(f));
		}
		else
		{
			ft_putchar(*f);
			ret++;
			f++;
		}
	}
	return (ret);
}

int			ft_searchnbr(char *f, char c, int precision)
{
	int ret;

	ret = -2;
	if (c == 'f' || c == 'F')
		ret = -1;
	if (!precision)
	{
		while (*f != c && *f != '.')
			f++;
		while (*f != c)
		{
			if (ft_atoi(f) > ret)
				ret = ft_atoi(f);
			f++;
		}
		return (ret);
	}
	ret = 0;
	while (*f != c && *f != '.')
	{
		if (ft_atoi(f) > ret)
			ret = ft_atoi(f);
		f++;
	}
	return (ret);
}

int			ft_glolbal(char *f, va_list args)
{
	char	c;
	char	*str;

	c = ft_searchflag(f);
	if (c == '%')
		str = ft_percent(f, c, args);
	else if (c == 'c' || c == 'C')
		str = ft_c(f, c, args);
	else if (c == 's' || c == 'S')
		str = ft_s(f, args, c);
	else if (c == 'd' || c == 'i' || c == 'D')
		str = ft_globaldi(f, args, c);
	else if (c == 'x' || c == 'X' || c == 'p')
		str = ft_globalpx(f, args, c);
	else if (c == 'f' || c == 'F')
		str = ft_globalfe(f, args, c);
	else if (c == 'o' || c == 'u' || c == 'U' || c == 'O')
		str = ft_globaluo(f, args, c);
	else
		return (0);
	if (ft_tolower(c) != 'c')
		ft_putstr(str);
	return (ft_fstrlen(str, 1));
}
