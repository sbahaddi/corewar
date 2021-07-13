/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:38:05 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 19:27:03 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** check if the arg type give match with the arg type in t_op
*/

static int	ft_check_argtype(t_process *p, int l_val, int i_op, int t_val)
{
	int				i_reg;

	i_reg = 0;
	if (l_val == REG_CODE)
	{
		i_reg = ft_get_hex_val((p->vm)->arena, 1, M(p->l_pc)) - 1;
		if (i_reg < 0 || i_reg > 15)
			return (ft_skip_bytes(p, t_val, i_op));
		p->l_pc += 1;
	}
	else if (l_val == DIR_CODE)
		p->l_pc += g_t_op[i_op].size_t_dir ? 2 : 4;
	else if (l_val == IND_CODE)
		p->l_pc += 2;
	return (1);
}

int			ft_ismatch_argtype(unsigned char val, int i_op, t_process *p)
{
	int				i;
	unsigned char	l_val;
	int				t_val;

	t_val = val;
	p->l_pc = p->pc + 2;
	i = 0;
	while (++i <= g_t_op[i_op].nbr_arg)
	{
		l_val = val >> (8 - (i * 2));
		if (l_val <= g_t_op[i_op].typearg[i - 1]
			&& (l_val & g_t_op[i_op].typearg[i - 1]))
		{
			if (ft_check_argtype(p, l_val, i_op, t_val) == -1)
				return (-1);
			val = val - (l_val << (8 - (i * 2)));
		}
		else
			return (ft_skip_bytes(p, t_val, i_op));
	}
	return (1);
}

/*
** this function help to stor the value for the operation that's
** has/have many args type
** like [and,xor,or,lldi]
*/

static void	getval_dircode(unsigned char *arena, t_process *p,
			int i_op, int *val)
{
	if (g_t_op[i_op].size_t_dir)
		val[p->i] = (short)ft_get_hex_val(arena, 2, M(p->pc));
	else
		val[p->i] = ft_get_hex_val(arena, 4, M(p->pc));
	p->pc = M((p->pc + (g_t_op[i_op].size_t_dir ? 2 : 4)));
}

static void	getval_indcode(unsigned char *arena, t_process *p,
			int oldpc, int *val)
{
	val[p->i] = (short)ft_get_hex_val(arena, 2, M(p->pc));
	val[p->i] = M((oldpc + (val[p->i] % IDX_MOD)));
	if (val[p->i] < 0)
		val[p->i] = val[p->i] + MEM_SIZE;
	val[p->i] = ft_get_hex_val(arena, 4, val[p->i]);
	p->pc = M((p->pc + 2));
}

void		ft_getvalueofbitop(unsigned char *arena, t_process *p,
			int *val, int i_op)
{
	unsigned char	tmp;
	int				i_reg;
	int				tval;
	int				oldpc;

	p->i = 0;
	oldpc = M((p->pc - 2));
	tval = val[0];
	while (++p->i <= g_t_op[i_op].nbr_arg)
	{
		tmp = val[0] >> (8 - (p->i * 2));
		if (tmp == REG_CODE)
		{
			i_reg = ft_get_hex_val(arena, 1, M(p->pc)) - 1;
			val[p->i] = p->regs[i_reg];
			p->pc = M((p->pc + 1));
		}
		else if (tmp == DIR_CODE)
			getval_dircode(arena, p, i_op, val);
		else if (tmp == IND_CODE)
			getval_indcode(arena, p, oldpc, val);
		val[0] -= (tmp << (8 - (p->i * 2)));
	}
	val[0] = tval;
}
