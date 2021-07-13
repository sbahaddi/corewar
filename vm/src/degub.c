/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:01:30 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 16:49:29 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** read hex and convert it to int we use usngined char because ignore the signe
*/

int		ft_get_hex_val(unsigned char *l, int size, int pc)
{
	int			i;
	int			s;
	char		*nbrhex;
	char		*tmp;

	i = -1;
	s = 0;
	nbrhex = ft_strnew(0);
	while (++i < size)
	{
		tmp = ft_itoa_base(l[M((pc + i))], 16);
		if (ft_strlen(tmp) == 1)
			tmp = ft_fstrjoin(ft_strdup("0"), tmp);
		nbrhex = ft_fstrjoin(nbrhex, tmp);
	}
	s = ft_hex_ot_int(nbrhex);
	free(nbrhex);
	return (s);
}

int		ft_hex_ot_int(char *nbr)
{
	int		res;
	int		i;
	int		l;
	char	*base;

	base = ft_strdup("0123456789abcdef");
	l = ft_strlen(nbr);
	res = 0;
	i = -1;
	while (nbr[++i])
		res += ft_strlenc(base, nbr[i]) * ft_pow(16, l - i - 1);
	free(base);
	return (res);
}

void	ft_print_hex_val(char *l, int size)
{
	int				i;
	unsigned int	s;
	char			*nbrhex;

	i = 0;
	s = 0;
	nbrhex = ft_strnew(0);
	while (++i <= size)
	{
		if (i == 1)
			ft_printf("0x0000 : ");
		if (l[i - 1])
			ft_printf("%.2hhx ", l[i - 1]);
		else
			ft_printf("%.2hhx ", l[i - 1]);
		if (i % 64 == 0)
		{
			ft_printf("\n");
			if (i + 1 < size)
				ft_printf("%#.4x : ", i);
		}
	}
}

int		ft_count_proces(t_list *process)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = process;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
