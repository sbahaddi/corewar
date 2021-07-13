/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 22:59:54 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:45 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_pmanager(char *str, char *mnts, int pr, int p)
{
	int np;
	int pos;
	int x;

	p = p < 0 ? ft_strlen(str) - ft_strlen(mnts) - ABS(p)
		: ft_strlen(str) - ft_strlen(mnts);
	np = p;
	p = p < 0 ? ABS(p - 1) : p;
	if (np < -1)
		str = ft_fstrjoin(ft_snbrnew(ABS(p)), str);
	p = np < -1 ? p : p + 1;
	if ((size_t)pr + ABS(p) > ft_strlen(str))
		str = ft_fstrjoin(str, ft_snbrnew(pr - ft_strlen(str) + ABS(p)));
	pr = np <= -1 ? pr : pr + 1;
	str = ft_round(str, pr, ABS(p), np);
	pos = np < 0 ? 0 : ABS(p);
	x = str[0] == '0' ? 1 : 0;
	pos = str[0] != '0' && !pos ? 1 : pos;
	str = ft_point(str, pos, x, str[0] == '0' ? 1 : 0);
	ft_finstr(str, pr, p, np);
	return (str);
}

void		ft_finstr(char *str, int pr, int p, int np)
{
	if (pr > 1 && np != -1)
		str[np >= 0 ? ABS(p) + pr : pr + 2] = '\0';
	else if (np != -1 && pr != 1)
		str[np >= 0 ? ABS(p) + pr - 1 : pr + 1] = '\0';
	else
	{
		pr += np < 0 && pr ? 1 : 0;
		pr += pr == 1 && np >= 0 ? -1 : 0;
		str[np >= 0 ? (ABS(p) + pr) : pr + 1] = '\0';
	}
}
