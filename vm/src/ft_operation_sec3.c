/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_sec3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:41:07 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 18:19:12 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_zjmp(unsigned char *arena, t_process *p)
{
	int			val;
	int			tmp;

	tmp = (short)ft_get_hex_val(arena, 2, M((p->pc + 1)));
	val = M((p->pc + (tmp % IDX_MOD)));
	if (val < 0)
		val = val + MEM_SIZE;
	if (p->carry)
	{
		p->pc = val;
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | zjmp %d OK\n", p->id, tmp);
	}
	else
	{
		p->pc = M((p->pc + 3));
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | zjmp %d FAILED\n", p->id, tmp);
	}
}

void	ft_ldi(unsigned char *arena, t_process *p)
{
	int				val[4];
	int				pre_pc;
	int				vallog;

	pre_pc = p->pc;
	val[0] = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val[0], 9, p) == 1)
	{
		p->pc = M((p->pc + 2));
		ft_getvalueofbitop(arena, p, (int *)val, 9);
		val[3] = ft_get_hex_val(arena, 1, M((p->pc - 1))) - 1;
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | ldi %d %d r%d\n",
			p->id, val[1], val[2], val[3] + 1);
		pre_pc = M((pre_pc + ((val[2] + val[1]) % IDX_MOD)));
		vallog = pre_pc;
		if (pre_pc < 0)
			pre_pc = MEM_SIZE + pre_pc;
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("%7c| -> load from %d + %d = %d (with pc and mod %d)\n",
			' ', val[1], val[2], val[1] + val[2], vallog);
		p->regs[val[3]] = ft_get_hex_val(arena, 4, pre_pc);
	}
}

void	ft_sti(unsigned char *arena, t_process *p)
{
	int				val[4];
	int				pre_pc;
	int				tmp;

	pre_pc = p->pc;
	p->oldpc = p->pc;
	val[0] = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val[0], 10, p) == 1)
	{
		p->pc = M((p->pc + 2));
		ft_getvalueofbitop(arena, p, (int *)val, 10);
		tmp = ft_get_hex_val(arena, 1, M((pre_pc + 2)));
		pre_pc = (pre_pc + (val[3] + val[2]) % IDX_MOD);
		val[0] = pre_pc;
		pre_pc = M(pre_pc);
		if (pre_pc < 0)
			pre_pc = MEM_SIZE + pre_pc;
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | sti r%d %d %d\n", p->id, tmp, val[2], val[3]);
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n"
			, val[2], val[3], val[2] + val[3], val[0]);
		set_value_to_arena(arena, val[1], pre_pc, p);
	}
}

void	ft_fork(unsigned char *arena, t_process *p)
{
	int				valdump[2];
	int				val;
	t_list			*proc_item;
	t_process		*process;

	proc_item = ft_lstnew(NULL, 0);
	if (!(process = malloc(sizeof(t_process))))
		ft_exit_and_free(p->vm, NULL,
		"can't allocat memory to process");
	val = (short)ft_get_hex_val(arena, 2, M((p->pc + 1)));
	valdump[0] = val;
	valdump[1] = (val % IDX_MOD + p->pc);
	val = M((val % IDX_MOD + p->pc));
	if (val < 0)
		val = MEM_SIZE + val;
	ft_copie_process(p, process, val, arena);
	proc_item->content = process;
	ft_lstadd(&((t_virtual_m *)p->vm)->process, proc_item);
	p->pc = M(p->pc + 3);
	if (((t_virtual_m *)p->vm)->flgs & LOGVM)
		ft_printf("P %4d | fork %d (%d)\n", p->id, valdump[0], valdump[1]);
}
