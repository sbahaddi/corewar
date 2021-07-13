/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uoctal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 08:09:11 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:28 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_globaluo(char *f, va_list args, char c)
{
	char	*str;
	t_flags	flgs;
	int		len;

	ft_searchall(f, c, &flgs, args);
	str = ft_uo(f, args, c);
	len = ft_strlen(str);
	if (flgs.hash && c != 'U' && c != 'u')
		flgs.hash = -2;
	flgs.plus = 0;
	if (str[0] == '0' && (c == 'o' || c == 'O') && flgs.hash)
	{
		if (flgs.prcsn)
			flgs.prcsn -= 1;
		if (flgs.hash == -2)
			str[0] = '\0';
	}
	else if (flgs.prcsn && (c == 'o' || c == 'O')
			&& flgs.hash && str[0] != '\0')
		flgs.prcsn -= len;
	if (flgs.prcsn == 0)
		flgs.zero = 0;
	str = ft_dxph(flgs, str, len, c);
	return (str);
}

char	*ft_uo(char *f, va_list args, char c)
{
	char	*str;
	int		i;
	int		x;

	x = c == 'u' || c == 'U' ? 10 : 8;
	i = ft_searchonsize(f, c, 0);
	if (i == 1 || i == 8 || c == 'U' || c == 'O')
		str = ft_uitoa_base(va_arg(args, unsigned long int), x);
	else if (i == 2 || i == 6)
		str = ft_uitoa_base(va_arg(args, unsigned long long int), x);
	else if (i == 3)
		str = ft_uitoa_base((unsigned short)va_arg(args, unsigned int), x);
	else if (i == 4)
		str = ft_uitoa_base((unsigned char)va_arg(args, unsigned int), x);
	else
		str = ft_uitoa_base(va_arg(args, unsigned int), x);
	return (str);
}
