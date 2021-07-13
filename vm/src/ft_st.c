/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:11:31 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 18:15:29 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_indcode(unsigned char *arena, t_process *p, int val, int i_reg)
{
	val = (short)ft_get_hex_val(arena, 2, M((p->pc + 3)));
	if (((t_virtual_m *)p->vm)->flgs & LOGVM)
		ft_printf("P %4d | st r%d %d\n", p->id, i_reg + 1, val);
	val = M((p->pc + (val % IDX_MOD)));
	if (val < 0)
		val = MEM_SIZE + val;
	set_value_to_arena(arena, p->regs[i_reg], val, p);
	p->pc = M((p->pc + 5));
}

void		ft_st(unsigned char *arena, t_process *p)
{
	int				i_reg;
	int				val;
	unsigned char	tmp;

	val = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	tmp = val;
	if (ft_ismatch_argtype(val, 2, p) == 1)
	{
		tmp = (tmp & (IND_CODE << 4)) >> 4;
		i_reg = ft_get_hex_val(arena, 1, M((p->pc + 2))) - 1;
		if (tmp == IND_CODE)
			ft_indcode(arena, p, val, i_reg);
		else
		{
			val = ft_get_hex_val(arena, 1, M((p->pc + 3))) - 1;
			p->regs[val] = p->regs[i_reg];
			p->pc = M((p->pc + 4));
			if (((t_virtual_m *)p->vm)->flgs & LOGVM)
				ft_printf("P %4d | st r%d %d\n", p->id, i_reg + 1, val + 1);
		}
	}
}
