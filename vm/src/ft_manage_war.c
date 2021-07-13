/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_war.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:45:13 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 17:44:55 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_checkcycles(t_virtual_m *vm)
{
	if (vm->cycles_to_check <= 0)
	{
		vm->max_checks_counter++;
		ft_kill_process(&vm->process);
		if (vm->nbr_live >= NBR_LIVE)
		{
			vm->cycles_to_die = vm->cycles_to_die - CYCLE_DELTA;
			vm->cycles_to_check = vm->cycles_to_die;
			vm->nbr_live = 0;
			vm->max_checks_counter = 0;
		}
		else if (vm->max_checks_counter >= MAX_CHECKS)
		{
			vm->cycles_to_die = vm->cycles_to_die - CYCLE_DELTA;
			vm->cycles_to_check = vm->cycles_to_die;
			vm->nbr_live = 0;
			vm->max_checks_counter = 0;
		}
		vm->nbr_live = 0;
		vm->cycles_to_check = vm->cycles_to_die;
	}
}

void			ft_execut_proc(t_virtual_m *vm, t_process *p, int i_op)
{
	if (p->nbr_cycles_actn == 0)
	{
		vm->lst_op = i_op - 1;
		vm->tab_ft_op[i_op - 1](vm->arena, p);
		p->isverified = 0;
	}
	else
		p->nbr_cycles_actn--;
}

void			ft_do_proc(t_virtual_m *vm, t_process *p)
{
	char	*nbr;

	p->oldpc = M((p->pc));
	if (p->isverified == 0)
	{
		nbr = ft_itoa_base(vm->arena[p->pc % MEM_SIZE], 16);
		p->action = ft_hex_ot_int(nbr);
		free(nbr);
		if ((p->op = ft_is_operation(p)) != -1)
		{
			p->isverified = 1;
			p->nbr_cycles_actn = g_t_op[p->op - 1].cycles - 1;
		}
		else
			p->pc = M((p->pc + 1));
	}
	if (p->isverified == 1)
		ft_execut_proc(vm, p, p->op);
	ft_display_data(vm, p);
}

/*
** check if the current byte  in arena is action if it's true
** return the value else return -1
*/

unsigned int	ft_is_operation(t_process *p)
{
	if (p->action >= 1 && p->action < 17)
		return (p->action);
	return (-1);
}
