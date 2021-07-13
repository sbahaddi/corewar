/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadeciaml.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 03:07:23 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:24 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_globalpx(char *f, va_list args, char c)
{
	char	*str;
	t_flags	flgs;
	int		len;

	ft_searchall(f, c, &flgs, args);
	str = ft_dxp(f, args, c);
	len = ft_strlen(str);
	if (c == 'p')
		flgs.hash = 2;
	str = ft_dxph(flgs, str, len, c);
	if (c == 'X')
		ft_strtrasform(str, 1);
	return (str);
}

char	*ft_dxp(char *f, va_list args, char c)
{
	char	*str;
	int		i;

	i = ft_searchonsize(f, c, 0);
	if (i == 1 || i == 8 || c == 'p')
		str = ft_uitoa_base(va_arg(args, unsigned long int), 16);
	else if (i == 2 || i == 6)
		str = ft_uitoa_base(va_arg(args, unsigned long long int), 16);
	else if (i == 3)
		str = ft_uitoa_base((unsigned short)va_arg(args, unsigned int), 16);
	else if (i == 4)
		str = ft_uitoa_base((unsigned char)va_arg(args, unsigned int), 16);
	else
		str = ft_uitoa_base(va_arg(args, unsigned int), 16);
	return (str);
}

char	*ft_dxph(t_flags flgs, char *str, int len, char c)
{
	if (str[0] == '0' && !flgs.prcsn)
		str[0] = '\0';
	if (flgs.hash > 0 && flgs.hash < 2)
		flgs.hash = str[0] == '\0' || str[0] == '0' ? 0 : flgs.hash;
	flgs.zero = str[0] == '\0' && c != 'o' ? 0 : flgs.zero;
	if (flgs.minif && flgs.hash && flgs.zero && ft_tolower(c) != 'o')
		flgs.minif -= 2;
	else if (ft_tolower(c) == 'o' && flgs.minif &&
		flgs.hash && flgs.zero && str[0] != '\0')
		flgs.minif -= 1;
	flgs.prcsn = flgs.prcsn < 0 ? 0 : flgs.prcsn;
	flgs.prcsn = flgs.prcsn >= 0 ? flgs.prcsn + ABS(flgs.hash) : flgs.prcsn;
	flgs.prcsn = flgs.prcsn > len ? flgs.prcsn - len : 0;
	if (flgs.prcsn && flgs.hash)
		flgs.prcsn -= 1;
	str = ft_strfillwithxp(flgs, len, str);
	return (str);
}

char	*ft_strfillwithxp(t_flags flgs, int len, char *nbr)
{
	char *str;
	char *tmp;

	tmp = "\0";
	if (flgs.minif > len && flgs.zero)
		flgs.prcsn = flgs.minif - len - (flgs.prcsn > 0 ? flgs.prcsn : 0);
	flgs.minif = (flgs.minif > len && flgs.zero) ? 0 : flgs.minif;
	if (flgs.prcsn > 0)
		tmp = ft_fstrjoin(ft_snbrnew(flgs.prcsn), nbr);
	else if (!flgs.prcsn && ABS(flgs.plus) == 1)
		tmp = ft_fstrjoin(ft_snbrnew(1), nbr);
	str = tmp[0] != '\0' ? ft_strdup(tmp) : nbr;
	if (tmp[0] != '\0')
		free(tmp);
	if (flgs.prcsn >= 0 && ABS(flgs.plus))
		str[0] = flgs.plus > 0 ? '+' : '-';
	if ((flgs.prcsn >= 0 && flgs.hash) || flgs.hash < 0)
		str = flgs.hash < 1 ? ft_fstrjoin(ft_strdup("0"), str) :
		ft_fstrjoin(ft_strdup("0x"), str);
	flgs.minif = flgs.minif > 0 ? flgs.minif - ft_strlen(str) : 0;
	if (flgs.minif > 0)
		tmp = ft_memset(ft_strnew(flgs.minif), ' ', flgs.minif);
	if (flgs.minif > 0)
		str = flgs.minus ? ft_fstrjoin(str, tmp) : ft_fstrjoin(tmp, str);
	return (str);
}

void	ft_strtrasform(char *str, int y)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (y == 1)
			str[i] = ft_toupper(str[i]);
		else if (y == 2)
			str[i] = ft_tolower(str[i]);
		i++;
	}
}
