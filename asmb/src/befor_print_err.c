/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   befor_print_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:48:58 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/05 16:43:10 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		check_befor_label(t_asm *asem, t_inst *inst, int i, int k)
{
	t_inst	*temp;
	char	*str;
	int		j;

	temp = asem->insthead;
	j = -1;
	while (inst->arg[i][++j])
		if (inst->arg[i][j] == ':')
			break ;
	str = ft_strsub(inst->arg[i], j + 1, ft_strlen(inst->arg[i]));
	while (temp)
	{
		if (temp->lable)
			if (ft_strcmp(temp->lable, str) == 0)
			{
				k++;
				if (k > 1)
					duplic_label(temp);
			}
		temp = temp->next;
	}
	if (k == 0)
		er_arg_label(inst, str, i);
	free(str);
}

static void		reg(t_inst *inst, int i)
{
	int		nb;
	char	*str;

	nb = 0;
	str = ft_strsub(inst->arg[i], 1, ft_strlen(inst->arg[i]));
	if (!verif_arg(str))
		nb = ft_atoi(str);
	else
		er_arg_op(inst, inst->action, i);
	if (nb < 1 || nb > 16)
		er_arg_op(inst, inst->action, i);
	free(str);
}

static void		dir(t_inst *inst, t_asm *asem, int i)
{
	int		nb;
	int		k;
	char	*str;

	k = 0;
	str = ft_strsub(inst->arg[i], 1, ft_strlen(inst->arg[i]));
	if (str[0] == ':')
		check_befor_label(asem, inst, i, k);
	else
	{
		if (!verif_arg(str))
			nb = ft_atoi(str);
		else
			er_arg_op(inst, inst->action, i);
	}
	free(str);
}

static void		indir(t_inst *inst, t_asm *asem, int i)
{
	int		nb;
	int		k;

	k = 0;
	if (inst->arg[i][0] == ':')
		check_befor_label(asem, inst, i, k);
	else
	{
		if (!verif_arg(inst->arg[i]))
			nb = ft_atoi(inst->arg[i]);
		else
			er_arg_op(inst, inst->action, i);
	}
}

void			check_befor_err(t_asm *asem)
{
	int			i;
	t_inst		*inst;

	inst = asem->insthead;
	while (inst)
	{
		i = -1;
		if (inst->action)
		{
			while (inst->arg[++i])
			{
				if (inst->arg[i][0] == 'r')
					reg(inst, i);
				else if (inst->arg[i][0] == '%')
					dir(inst, asem, i);
				else
					indir(inst, asem, i);
			}
		}
		inst = inst->next;
	}
}
