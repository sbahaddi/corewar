/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_sec1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:57:18 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 18:15:40 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** represent the opertations with function
*/

void	ft_live(unsigned char *arena, t_process *p)
{
	int			val;
	t_player	*data;
	t_list		*player;

	player = ((t_virtual_m *)p->vm)->palyers;
	p->pc = M((p->pc + 1));
	val = ft_get_hex_val(arena, 4, p->pc);
	if (((t_virtual_m *)p->vm)->flgs & LOGVM)
		ft_printf("P %4d | live %d\n", p->id, val, p->pc);
	while (player)
	{
		data = player->content;
		if (-data->nbr == val)
		{
			((t_virtual_m *)p->vm)->winer = data;
			data->lst_live = ((t_virtual_m *)p->vm)->cycles;
			break ;
		}
		player = player->next;
	}
	p->is_live = 1;
	((t_virtual_m *)p->vm)->nbr_live++;
	p->pc = M((p->pc + 4));
}

void	ft_add(unsigned char *arena, t_process *p)
{
	int				i_reg1;
	int				i_reg2;
	int				i_reg3;
	int				val;

	val = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val, 3, p) == 1)
	{
		i_reg1 = ft_get_hex_val(arena, 1, M((p->pc + 2))) - 1;
		i_reg2 = ft_get_hex_val(arena, 1, M((p->pc + 3))) - 1;
		i_reg3 = ft_get_hex_val(arena, 1, M((p->pc + 4))) - 1;
		p->regs[i_reg3] = p->regs[i_reg1] + p->regs[i_reg2];
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | add r%d r%d r%d\n", p->id,
			i_reg1 + 1, i_reg2 + 1, i_reg3 + 1);
		p->carry = p->regs[i_reg3] ? 0 : 1;
		p->pc = M((p->pc + 5));
	}
}

void	ft_sub(unsigned char *arena, t_process *p)
{
	int				i_reg1;
	int				i_reg2;
	int				i_reg3;
	int				val;

	val = ft_get_hex_val(arena, 1, M((p->pc + 1)));
	if (ft_ismatch_argtype(val, 4, p) == 1)
	{
		i_reg1 = ft_get_hex_val(arena, 1, M((p->pc + 2))) - 1;
		i_reg2 = ft_get_hex_val(arena, 1, M((p->pc + 3))) - 1;
		i_reg3 = ft_get_hex_val(arena, 1, M((p->pc + 4))) - 1;
		p->regs[i_reg3] = p->regs[i_reg1] - p->regs[i_reg2];
		if (((t_virtual_m *)p->vm)->flgs & LOGVM)
			ft_printf("P %4d | sub r%d r%d r%d\n", p->id,
			i_reg1 + 1, i_reg2 + 1, i_reg3 + 1);
		p->carry = p->regs[i_reg3] ? 0 : 1;
		p->pc = M((p->pc + 5));
	}
}
