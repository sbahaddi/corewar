/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:49:11 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 18:09:12 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_indcode(unsigned char *arena, t_process *p, int val)
{
	int				i_reg;

	i_reg = 0;
	i_reg = ft_get_hex_val(arena, 1, M((p->pc + 4))) - 1;
	val = (short)ft_get_hex_val(arena, 2, M((p->pc + 2)));
	val = M((p->pc + (val % IDX_MOD)));
	if (val < 0)
		val = MEM_SIZE + val;
	p->regs[i_reg] = ft_get_hex_val(arena, 4, M(val));
	if (((t_virtual_m *)p->vm)->flgs & LOGVM)
		ft_printf("P %4d | ld %d r%d\n", p->id,
		p->regs[i_reg], i_reg + 1);
	p->pc = M((p->pc + 5));
	p->carry = p->regs[i_reg] ? 0 : 1;
}

void			ft_ld(unsigned char *arena, t_process *p)
{
	int				i_reg;
	int				val;
	unsigned char	tmp;

	val = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	tmp = val;
	i_reg = 0;
	if (ft_ismatch_argtype(val, 1, p) == 1)
	{
		tmp = tmp >> 6;
		if (tmp == DIR_CODE)
		{
			i_reg = ft_get_hex_val(arena, 1, M((p->pc + 6))) - 1;
			p->regs[i_reg] = ft_get_hex_val(arena, 4, M((p->pc + 2)));
			if (((t_virtual_m *)p->vm)->flgs & LOGVM)
				ft_printf("P %4d | ld %d r%d\n",
				p->id, p->regs[i_reg], i_reg + 1);
			p->pc = M((p->pc + 7));
			p->carry = p->regs[i_reg] ? 0 : 1;
		}
		else if (tmp == IND_CODE)
			ft_indcode(arena, p, val);
	}
}
