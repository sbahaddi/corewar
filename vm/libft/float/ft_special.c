/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 22:50:21 by akhourba          #+#    #+#             */
/*   Updated: 2019/01/28 21:44:41 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_special(char *bf, int nbits)
{
	int j;

	j = 1;
	while (bf[j])
	{
		if (bf[j] != '1' && j <= nbits)
			return ("\0");
		if (j > nbits && bf[j] != '0')
			return (ft_strdup("nan"));
		j++;
	}
	return (bf[0] != '1' ? ft_strdup("inf") : ft_strdup("-inf"));
}

int		ft_ispecial(char *str, t_flags *flgs)
{
	if (!ft_strcmp(str, "inf") ||
		!ft_strcmp(str, "-inf") || !ft_strcmp(str, "nan"))
	{
		flgs->hash = 0;
		flgs->zero = 0;
		return (0);
	}
	return (1);
}
