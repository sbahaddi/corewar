/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widestring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 00:35:03 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/31 22:14:40 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_widestring(wchar_t *str)
{
	int				wc[2];
	char			*res;
	char			*tmp;

	wc[0] = -1;
	if (!str)
		return (NULL);
	res = ft_strdup("\0");
	while (str[++wc[0]] != L'\0')
	{
		wc[1] = str[wc[0]];
		if (wc[1] < 0 || (wc[1] >= 0xd800 && wc[1] < 0xe000) ||
		wc[1] > 0x10ffff || (wc[1] >= 256 && MB_CUR_MAX == 1))
		{
			free(res);
			return (ft_strdup("\0"));
		}
		tmp = ft_itoa_base(wc[1], 2);
		wc[1] = ft_strlen(tmp);
		tmp = ft_wsetmask(tmp, ft_mask(wc[1]));
		wc[1] = ft_getsizemask(wc[1]);
		tmp = ft_wchar(tmp, wc[1] / 8);
		res = ft_fstrjoin(res, tmp);
	}
	return (res);
}

char	*ft_wchar(char *s, int size)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	res = ft_strnew(sizeof(char) * size + 1);
	i = 0;
	while (i < size)
	{
		res[i] = ft_wbinary(s + (j * 9));
		i++;
		j++;
	}
	res[i] = '\0';
	free(s);
	return (res);
}

int		ft_wbinary(char *res)
{
	int wc;
	int i;
	int j;

	j = 0;
	i = 8;
	wc = 0;
	while (--i >= 0)
	{
		if (res[i] == '1')
			wc += ft_pow(2, j);
		j++;
	}
	return (wc);
}

char	*ft_mask(int wnbr)
{
	if (wnbr <= 7)
		return (ft_strdup("0xxxxxxx"));
	else if (wnbr <= 11)
		return (ft_strdup("110xxxxx 10xxxxxx"));
	else if (wnbr <= 16)
		return (ft_strdup("1110xxxx 10xxxxxx 10xxxxxx"));
	else if (wnbr <= 21)
		return (ft_strdup("11110xxx 10xxxxxx 10xxxxxx 10xxxxxx"));
	else
		return (ft_strdup("\0"));
}
