/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_sec4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:37:01 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 22:34:56 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_lld_indcode(unsigned char *arena, t_process *p)
{
	int		i_reg;
	int		val;

	i_reg = ft_get_hex_val(arena, 1, M((p->pc + 4))) - 1;
	val = (short)ft_get_hex_val(arena, 2, M((p->pc + 2)));
	val = M((p->pc + (val)));
	if (val < 0)
		val = MEM_SIZE + val;
	p->regs[i_reg] = ft_get_hex_val(arena, 4, M(val));
	if (((t_virtual_m *)p->vm)->flgs & LOGVM)
		ft_printf("P %4d | lld %d r%d\n", p->id,
		p->regs[i_reg], i_reg + 1);
	p->pc = M((p->pc + 5));
	p->carry = p->regs[i_reg] ? 0 : 1;
}

void		ft_lld(unsigned char *arena, t_process *p)
{
	int				i_reg;
	int				val;
	unsigned char	tmp;

	val = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	tmp = val;
	i_reg = 0;
	if (ft_ismatch_argtype(val, 12, p) == 1)
	{
		tmp = tmp >> 6;
		if (tmp == DIR_CODE)
		{
			i_reg = ft_get_hex_val(arena, 1, M((p->pc + 6))) - 1;
			p->regs[i_reg] = ft_get_hex_val(arena, 4, M((p->pc + 2)));
			if (((t_virtual_m *)p->vm)->flgs & LOGVM)
				ft_printf("P %4d | lld %d r%d\n",
				p->id, p->regs[i_reg], i_reg + 1);
			p->pc = M((p->pc + 7));
			p->carry = p->regs[i_reg] ? 0 : 1;
		}
		else if (tmp == IND_CODE)
			ft_lld_indcode(arena, p);
	}
}

void		ft_lldi(unsigned char *arena, t_process *p)
{
	int				val[4];
	int				pre_pc;
	int				vallog;

	pre_pc = M((p->pc));
	val[0] = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val[0], 13, p) == 1)
	{
		p->pc = M((p->pc + 2));
		ft_getvalueofbitop(arena, p, (int *)val, 9);
		val[3] = ft_get_hex_val(arena, 1, M((p->pc - 1))) - 1;
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | lldi %d %d r%d\n",
			p->id, val[1], val[2], val[3] + 1);
		vallog = pre_pc + ((val[2] + val[1]));
		pre_pc = M((pre_pc + (val[2] + val[1])));
		if (pre_pc < 0)
			pre_pc = MEM_SIZE + pre_pc;
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			val[1], val[2], val[1] + val[2], vallog);
		p->regs[val[3]] = ft_get_hex_val(arena, 4, M(pre_pc));
		p->carry = p->regs[val[3]] ? 0 : 1;
	}
}

void		ft_lfork(unsigned char *arena, t_process *p)
{
	int				val;
	t_list			*proc_item;
	t_process		*process;
	int				valdump[2];

	proc_item = ft_lstnew(NULL, 0);
	if (!(process = malloc(sizeof(t_process))))
		ft_exit_and_free(p->vm, NULL,
		"can't allocat memory to process");
	val = (short)ft_get_hex_val(arena, 2, M((p->pc + 1)));
	valdump[0] = val;
	valdump[1] = val + p->pc;
	val = M(valdump[1]);
	if (val < 0)
		val = MEM_SIZE + val;
	ft_copie_process(p, process, val, arena);
	proc_item->content = process;
	ft_lstadd(&((t_virtual_m *)p->vm)->process, proc_item);
	p->pc = M(p->pc + 3);
	if (((t_virtual_m *)p->vm)->flgs & LOGVM)
		ft_printf("P %4d | lfork %d (%d)\n", p->id, valdump[0], valdump[1]);
}

void		ft_aff(unsigned char *arena, t_process *p)
{
	int				val;

	val = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val, 15, p) == 1)
	{
		val = ft_get_hex_val(arena, 1, M((p->pc + 2))) - 1;
		if (p->vm->flgs & VISU)
		{
			mvprintw(50, WIDTH + 10, "aff %c", p->regs[val] % 256);
		}
		p->pc = M((p->pc + 3));
	}
}
