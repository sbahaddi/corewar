/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:58:03 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 18:39:21 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_value_to_arena(unsigned char *arena,
						unsigned int val, int index, t_process *p)
{
	int				i;
	unsigned char	tmp;

	i = -1;
	while (++i < 4)
	{
		tmp = val >> (24 - (i * 8));
		p->vm->colors[M((index + i))] = p->idcolor + 4;
		arena[M((index + i))] = tmp;
		ft_updatearena(p, M((index + i)));
		val = val - (tmp << (24 - (i * 8)));
	}
}

/*
** copy data from old process to new one
** take care of p_dst-action it will be negative sometime
*/

void	ft_copie_process(t_process *p_src, t_process *p_dst,
							int start_curs, unsigned char *arena)
{
	int		i;
	char	*nbr;

	i = -1;
	p_dst->pc = M(start_curs);
	nbr = ft_itoa_base(arena[p_dst->pc], 16);
	p_dst->action = ft_hex_ot_int(nbr);
	p_dst->carry = p_src->carry;
	p_dst->vm = p_src->vm;
	p_dst->nbr_live = p_src->nbr_live;
	p_dst->is_live = p_src->is_live;
	p_dst->id = ((t_virtual_m *)p_dst->vm)->idgenerator++;
	p_dst->idcolor = p_src->idcolor;
	p_dst->isverified = 0;
	while (++i < REG_NUMBER)
		p_dst->regs[i] = p_src->regs[i];
	free(nbr);
}

/*
** skip the the variable if ther's an error with ag type
*/

int		ft_skip_bytes(t_process *p, int val, int i_op)
{
	unsigned char	tmp;
	int				i;
	int				t_pc;

	i = 0;
	t_pc = p->pc;
	p->pc = M((p->pc + 2));
	while (++i <= g_t_op[i_op].nbr_arg)
	{
		tmp = val >> (8 - (i * 2));
		if (tmp == REG_CODE)
			p->pc += 1;
		else if (tmp == DIR_CODE)
			p->pc += (g_t_op[i_op].size_t_dir ? 2 : 4);
		else if (tmp == IND_CODE)
			p->pc += 2;
		val -= (tmp << (8 - (i * 2)));
	}
	p->pc = M(p->pc);
	return (-1);
}
