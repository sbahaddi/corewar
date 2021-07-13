/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 01:41:22 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/27 04:02:09 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_di(char *f, va_list args, char c)
{
	char	*str;
	int		i;

	str = NULL;
	i = ft_searchonsize(f, c, 0);
	if (i == 1 || c == 'D' || i == 8)
		str = ft_itoa_base(va_arg(args, long int), 10);
	else if (i == 2 || i == 6)
		str = ft_itoa_base(va_arg(args, long long), 10);
	else if (i == 3)
		str = ft_itoa_base((short)va_arg(args, int), 10);
	else if (i == 4)
		str = ft_itoa_base((char)va_arg(args, int), 10);
	else
		str = ft_itoa_base(va_arg(args, int), 10);
	return (str);
}

char		*ft_globaldi(char *f, va_list args, char c)
{
	char	*str;
	t_flags	flgs;
	int		len;
	int		fk;

	ft_searchall(f, c, &flgs, args);
	str = ft_di(f, args, c);
	flgs.plus = str[0] == '-' ? -1 : flgs.plus;
	if ((flgs.minif && flgs.zero) || flgs.prcsn > 0 || flgs.plus)
		str = flgs.plus == -1 ? ft_fstrdup(str, str + 1) : ft_fstrdup(str, str);
	if (str[0] == '0' && !flgs.prcsn)
		str[0] = '\0';
	flgs.zero = str[0] == '\0' ? 0 : flgs.zero;
	len = ft_strlen(str);
	if (flgs.space && !flgs.plus && flgs.zero)
		flgs.minif--;
	flgs.prcsn = flgs.prcsn < 0 ? 0 : flgs.prcsn;
	flgs.prcsn = flgs.prcsn >= 0 ? flgs.prcsn + ABS(flgs.plus) : flgs.prcsn;
	flgs.prcsn = flgs.prcsn >= len ? flgs.prcsn - len : 0;
	fk = flgs.minif > len && !flgs.zero ? 1 : 0;
	str = ft_strfillwithxp(flgs, len, str);
	if (flgs.space && !flgs.plus && !fk)
		str = ft_fstrjoin(ft_strdup(" "), str);
	return (str);
}
