/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:35:15 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/17 12:24:59 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_reg(t_inst *inst, t_asm *asem, int i)
{
	int		nb;
	char	*str;

	str = ft_strsub(inst->arg[i], 1, ft_strlen(inst->arg[i]));
	nb = ft_atoi(str);
	if (nb < 1 || nb > 16)
		er_arg_op(inst, inst->action, i);
	write(asem->fd_w, &nb, 1);
	free(str);
}

static void		print_dir_suit(t_asm *asem, t_inst *inst, char *str, int i)
{
	int		nb;

	if (!verif_arg(str))
	{
		nb = ft_atoi(str);
		if (g_op_tab[inst->index - 1].label == 0)
			big_endy4(asem, nb);
		else
			big_endy2(asem, nb);
	}
	else
		er_arg_op(inst, inst->action, i);
}

static void		print_dir(t_inst *inst, t_asm *asem, int i)
{
	char	*str;

	str = ft_strsub(inst->arg[i], 1, ft_strlen(inst->arg[i]));
	if (str[0] == ':')
	{
		get_size_diff(asem, inst, i);
		if (g_op_tab[inst->index - 1].label == 0)
			big_endy4(asem, inst->diff_size);
		else
			big_endy2(asem, inst->diff_size);
	}
	else
		print_dir_suit(asem, inst, str, i);
	free(str);
}

static void		print_indir(t_inst *inst, t_asm *asem, int i)
{
	int		nb;

	if (inst->arg[i][0] == ':')
	{
		get_size_diff(asem, inst, i);
		big_endy2(asem, inst->diff_size);
	}
	else
	{
		if (!verif_arg(inst->arg[i]))
		{
			nb = ft_atoi(inst->arg[i]);
			big_endy2(asem, nb);
		}
		else
			er_arg_op(inst, inst->action, i);
	}
}

void			args_print(t_asm *asem, t_inst *inst)
{
	int		i;

	i = -1;
	if (inst->action)
	{
		if (inst->arg)
			while (inst->arg[++i])
			{
				if (inst->arg[i][0] == 'r')
					print_reg(inst, asem, i);
				else if (inst->arg[i][0] == '%')
					print_dir(inst, asem, i);
				else
					print_indir(inst, asem, i);
			}
	}
}
