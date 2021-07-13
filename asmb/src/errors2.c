/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:24:24 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/17 22:10:06 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		er_arg_op(t_inst *inst, char *str, int i)
{
	ft_printf("Invalid parameter %d for instruction '%s' with the opcode %d\n",
	i + 1, str, inst->index);
	exit(1);
}

void		duplic_label(t_inst *inst)
{
	ft_printf("duplicate label %s\n", inst->lable);
	exit(1);
}

void		er_arg_label(t_inst *inst, char *str, int i)
{
	ft_printf("No such label %s while attempting to dereference token ");
	ft_printf("\"%s\"\n", str, inst->arg[i]);
	exit(1);
}

void		length_name_error(int k)
{
	if (k == 1)
		ft_printf("Champion name too long (Max length 128)\n");
	if (k == 2)
		ft_printf("Champion comment too long (Max length 2048)\n");
	if (k == 3)
	{
		ft_printf("Champion size too long (Max length CHAMP_MAX_SIZE");
		ft_printf(" 'MEM_SIZE / 6')\n");
	}
	if (k == 4)
	{
		ft_printf("Syntax error - unexpected end of input");
		ft_printf(" (Perhaps you forgot to end with a newline ?)\n");
	}
	exit(1);
}

void		error_inst_args(t_inst *inst, int i)
{
	ft_printf("error in arg %d for instriction %s\n", i + 1, inst->action);
	exit(1);
}
