/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 01:46:49 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:59 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_round(char *nbr, int pr, int p, int np)
{
	char *res;

	res = ft_snbrnew(p + pr + 1);
	res[p + pr + 1] = '\0';
	ft_memmove(res + 1, nbr, p + pr);
	if (pr > 1 && ABS(np) != 1 && np != 0)
		ft_roundnbr(res, np >= 0 ? (p + pr) - 1 :
		pr, ft_scan(nbr, np >= 0 ? (p + pr) - 1 : pr));
	else if (np != -1 && pr != 1)
		ft_roundnbr(res, np >= 0 ? (p + pr) - 1 :
		pr, ft_scan(nbr, np >= 0 ? (p + pr) - 1 : pr));
	else
		ft_roundnbr(res, np >= 0 ? (p + pr) - 1 : pr,
		ft_scan(nbr, np >= 0 ? (p + pr) - 1 : pr));
	if (res[0] == '0' && p >= 1 && np >= 0)
		ft_memmove(res, res + 1, p + pr + 1);
	free(nbr);
	return (res);
}

int		ft_scan(char *nbr, int pos)
{
	int	isr;
	int	i;

	i = 0;
	isr = I(nbr[pos]) >= 5 ? 1 : 0;
	i = isr != 0 ? 1 : 0;
	if ((I(nbr[pos > 0 ? pos - 1 : 0]) % 2 && I(nbr[pos]) >= 5) ||
		I(nbr[pos]) > 5)
		return (1);
	else if (I(nbr[pos]) < 5)
		return (0);
	while (nbr[pos + i] != '\0' && isr)
	{
		if (nbr[pos + i] != '0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_roundnbr(char *res, int r, int x)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (r >= 0 && x)
	{
		if (!j || i)
		{
			i = I(res[r]) != 9 ? 0 : 1;
			res[r] = C(R(I(res[r])));
			if (!i)
				break ;
		}
		else
			break ;
		r--;
		j++;
	}
	return (res);
}
