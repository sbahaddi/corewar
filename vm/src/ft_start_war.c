/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_war.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:15:17 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 20:25:55 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_endgame(t_virtual_m *vm)
{
	if (vm->winer && (vm->flgs & VISU) == 0)
		ft_printf("Contestant %d, \"%s\", has won !\n",
	vm->winer->nbr, vm->winer->champ_name);
	ft_visu_endgame(vm, NULL);
	if (vm->flgs & LOGVM && (vm->flgs & VISU) == 0)
	{
		ft_printf("cycles = %d\n", vm->cycles);
		ft_printf("cdie = %d\n", vm->cycles_to_die);
	}
}

static void	ft_dump_arena(t_virtual_m *vm)
{
	ft_print_hex_val((char *)vm->arena, MEM_SIZE);
	exit(0);
}

void		ft_start_war(t_virtual_m *vm)
{
	t_process	*p;
	t_list		*lst_process;

	vm->pause = 1;
	lst_process = vm->process;
	vm->cycles_to_check = vm->cycles_to_die;
	while (vm->process)
	{
		while (lst_process)
		{
			p = (t_process *)lst_process->content;
			ft_do_proc(vm, p);
			lst_process = lst_process->next;
		}
		ft_checkcycles(vm);
		ft_control_visu(vm, NULL);
		if (!vm->process)
			break ;
		if ((vm->flgs & DUMP) && vm->dump_cycle == vm->cycles)
			ft_dump_arena(vm);
		vm->cycles++;
		vm->cycles_to_check--;
		lst_process = vm->process;
	}
	ft_endgame(vm);
}
