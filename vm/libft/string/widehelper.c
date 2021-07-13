/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widehelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 04:04:28 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:09 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_wsetmask(char *nbr, char *mask)
{
	int i;
	int j;

	i = ft_strlen(nbr);
	j = ft_strlen(mask);
	while (--j >= 0)
	{
		if (mask[j] == 'x')
		{
			if (--i >= 0)
				mask[j] = nbr[i];
			else
				mask[j] = '0';
		}
	}
	free(nbr);
	return (mask);
}

int		ft_getsizemask(int wnbr)
{
	if (wnbr <= 7)
		return (8);
	else if (wnbr <= 11)
		return (16);
	else if (wnbr <= 16)
		return (24);
	else if (wnbr <= 21)
		return (32);
	else
		return (0);
}

char	*ft_widechar(wchar_t wc)
{
	char	*res;

	if (wc < 0 || (wc >= 0xd800 && wc < 0xe000) ||
	wc > 0x10ffff || (wc >= 256 && MB_CUR_MAX == 1))
		return (ft_strdup("\0"));
	res = ft_itoa_base(wc, 2);
	wc = ft_strlen(res);
	res = ft_wsetmask(res, ft_mask(wc));
	wc = ft_getsizemask(wc) / 8;
	res = ft_wchar(res, wc);
	return (res);
}
