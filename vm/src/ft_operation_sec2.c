/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_sec2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:04:17 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 18:17:06 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** represent the opertations with function
*/

void	ft_and(unsigned char *arena, t_process *p)
{
	int				i_reg;
	int				pre_pc;
	int				val[4];

	pre_pc = p->pc;
	val[0] = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val[0], 5, p) == 1)
	{
		p->pc = M((p->pc + 2));
		ft_getvalueofbitop(arena, p, (int *)val, 5);
		pre_pc = p->pc - 1;
		i_reg = ft_get_hex_val(arena, 1, M(pre_pc)) - 1;
		p->regs[i_reg] = val[1] & val[2];
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | and %d %d r%d\n",
			p->id, val[1], val[2], i_reg + 1);
		p->carry = p->regs[i_reg] ? 0 : 1;
	}
}

void	ft_or(unsigned char *arena, t_process *p)
{
	int				i_reg;
	int				pre_pc;
	int				val[4];

	pre_pc = p->pc;
	val[0] = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val[0], 6, p) == 1)
	{
		p->pc = M((p->pc + 2));
		ft_getvalueofbitop(arena, p, (int *)val, 6);
		pre_pc = p->pc - 1;
		i_reg = ft_get_hex_val(arena, 1, M(pre_pc)) - 1;
		p->regs[i_reg] = val[1] | val[2];
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | or %d %d r%d\n",
			p->id, val[1], val[2], i_reg + 1);
		p->carry = p->regs[i_reg] ? 0 : 1;
	}
}

void	ft_xor(unsigned char *arena, t_process *p)
{
	int	i_reg;
	int	pre_pc;
	int	val[4];

	pre_pc = p->pc;
	val[0] = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val[0], 7, p) == 1)
	{
		p->pc = M((p->pc + 2));
		ft_getvalueofbitop(arena, p, (int *)val, 7);
		pre_pc = p->pc - 1;
		i_reg = ft_get_hex_val(arena, 1, M(pre_pc)) - 1;
		p->regs[i_reg] = val[1] ^ val[2];
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | xor %d %d r%d\n",
			p->id, val[1], val[2], i_reg + 1);
		p->carry = p->regs[i_reg] ? 0 : 1;
	}
}
