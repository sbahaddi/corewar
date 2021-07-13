/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:42:17 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 16:50:07 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_init(t_virtual_m *vm)
{
	vm->winer = NULL;
	vm->idgenerator = 1;
	vm->process = NULL;
	vm->flgs = 0;
	vm->palyers = NULL;
	vm->nbr_live = 0;
	vm->max_checks_counter = 0;
	vm->cycles = 0;
	vm->cycles_delta = CYCLE_DELTA;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->cycles_to_die_counter = 0;
	vm->cycles_to_check = 0;
	vm->tab_ft_op = ft_set_ft_op();
	vm->wait = DELAY;
}

t_ft_op	*ft_set_ft_op(void)
{
	t_ft_op *tab_ft_op;

	tab_ft_op = malloc(sizeof(t_ft_op) * 16);
	tab_ft_op[0] = &ft_live;
	tab_ft_op[1] = &ft_ld;
	tab_ft_op[2] = &ft_st;
	tab_ft_op[3] = &ft_add;
	tab_ft_op[4] = &ft_sub;
	tab_ft_op[5] = &ft_and;
	tab_ft_op[6] = &ft_or;
	tab_ft_op[7] = &ft_xor;
	tab_ft_op[8] = &ft_zjmp;
	tab_ft_op[9] = &ft_ldi;
	tab_ft_op[10] = &ft_sti;
	tab_ft_op[11] = &ft_fork;
	tab_ft_op[12] = &ft_lld;
	tab_ft_op[13] = &ft_lldi;
	tab_ft_op[14] = &ft_lfork;
	tab_ft_op[15] = &ft_aff;
	return (tab_ft_op);
}
