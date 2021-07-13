/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:23:29 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 19:40:18 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_read_magic_header(int fd)
{
	char	*bytes;
	int		i;
	int		magic;

	magic = 0;
	bytes = ft_strnew(4);
	read(fd, bytes, 4);
	i = -1;
	while (++i < 4)
		magic += bytes[i];
	if (magic == COREWAR_EXEC_MAGIC)
		return (1);
	return (0);
}

/*
** get flags -v -d ...
** and palyers
*/

t_list	*ft_set_option(t_virtual_m *vm, int ac, char *av[])
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	while (++i < ac)
	{
		if (ft_strequ("-dump", av[i]) && av[i + 1])
		{
			vm->flgs |= DUMP;
			vm->dump_cycle = ft_atoi(av[++i]);
		}
		else if (ft_strequ("-v", av[i]))
			vm->flgs |= VISU;
		else if (ft_strequ("-l", av[i]))
			vm->flgs |= LOGVM;
		else
			i = ft_addplayer(vm, av, i, ac);
		if (!head && vm->palyers)
			head = vm->palyers;
	}
	return (vm->palyers);
}
