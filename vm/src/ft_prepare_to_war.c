/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_to_war.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:30:37 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 19:34:08 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** creat process foreach player and asigne them and
** load execode of each of them in arena
*/

static void	ft_war_loop(t_virtual_m *vm, t_list *head)
{
	int			i;
	t_process	*process;
	t_list		*lst_proc;

	i = 0;
	while (head)
	{
		lst_proc = ft_lstnew(NULL, 0);
		if (!(process = malloc(sizeof(t_process))))
			ft_exit_and_free(vm, NULL,
			"can't allocat memory to process");
		ft_load_player_to_arena(vm, head, i);
		ft_set_process(((t_player *)head->content), process, i, vm);
		lst_proc->content = process;
		ft_lstadd(&vm->process, lst_proc);
		i += (MEM_SIZE / vm->nbr_player);
		head = head->next;
	}
}

void		ft_prepare_to_war(t_virtual_m *vm)
{
	t_list		*head;

	ft_set_all_player(vm, vm->palyers);
	head = vm->palyers;
	if (!(vm->arena = (unsigned char *)ft_strnew(MEM_SIZE)))
		ft_exit_and_free(vm, NULL,
		"can't allocat memory to arena");
	if (!(vm->colors = (unsigned char *)ft_strnew(MEM_SIZE)))
		ft_exit_and_free(vm, NULL,
		"can't allocat memory to colors");
	memset(vm->colors, 10, MEM_SIZE);
	memset(vm->arena, 0, MEM_SIZE);
	if ((vm->flgs & VISU) == 0)
		ft_printf("Introducing contestants...\n");
	ft_war_loop(vm, head);
}
