/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsleak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:57:40 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 21:15:03 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_free_corewar(t_virtual_m *vm)
{
	free(vm->tab_ft_op);
	if (vm->arena)
		free(vm->arena);
	if (vm->colors)
		free(vm->colors);
	if (vm->palyers)
		ft_free_players(&vm->palyers);
}

void	ft_free_players(t_list **pl)
{
	t_list			*lst;
	t_player		*d_pl;

	while (*pl)
	{
		lst = *pl;
		d_pl = lst->content;
		*pl = (*pl)->next;
		free(d_pl->exec_code);
		free(d_pl->champ_cmt);
		free(d_pl->champ_name);
		free(d_pl->path);
		free(lst->content);
		free(lst);
	}
}

void	ft_exit_and_free(t_virtual_m *vm, void *unit, char *s)
{
	if (vm->flgs & VISU)
		endwin();
	ft_printf("%s", s);
	if (unit)
		free(unit);
	exit(0);
}
