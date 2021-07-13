/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inst_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:46:01 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/17 13:02:31 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			inst_size(t_inst *inst, int val_add)
{
	unsigned int args;
	unsigned int size;

	size = 0;
	if (val_add == T_REG)
		size = 1;
	else if (val_add == T_DIR)
		if (g_op_tab[inst->index - 1].label == 0)
			size = 4;
		else
			size = 2;
	else if (val_add == T_IND)
		size = 2;
	args = inst->inst_size + size;
	return (args);
}

static int			and_diff(t_inst *inst, int i, int val_add)
{
	if ((g_op_tab[inst->index - 1].args[i] & val_add) == 0)
		return (1);
	return (0);
}

static void			set_size_char(t_inst *inst, int i, int val_add)
{
	if (val_add == T_REG)
		inst->inst_size_char = 1 << ((3 - i) * 2) | inst->inst_size_char;
	else if (val_add == T_DIR)
		inst->inst_size_char = 1 << ((3 - i) * 2 + 1) | inst->inst_size_char;
	else if (val_add == T_IND)
	{
		inst->inst_size_char = 1 << ((3 - i) * 2) | inst->inst_size_char;
		inst->inst_size_char = 1 << ((3 - i) * 2 + 1) | inst->inst_size_char;
	}
}

static void			verif_check_args(t_inst *temp, int i, int val_add)
{
	char	*str;

	str = temp->arg[i];
	temp->arg[i] = ft_strtrim(temp->arg[i]);
	if (temp->arg[i] == NULL || ft_strlen(temp->arg[i]) == 0)
		er_arg_op(temp, temp->action, i);
	else
	{
		if (temp->arg[i][0] == 'r')
			val_add = T_REG;
		else if (temp->arg[i][0] == '%')
		{
			if (temp->arg[i][1] != '\0')
				val_add = T_DIR;
		}
		else
			val_add = T_IND;
		if (and_diff(temp, i, val_add))
			error_inst_args(temp, i);
		temp->inst_size = inst_size(temp, val_add);
		set_size_char(temp, i, val_add);
	}
	free(str);
}

void				check_args(t_asm *asem)
{
	int		i;
	int		val_add;
	t_inst	*temp;

	temp = asem->insthead;
	while (temp)
	{
		i = -1;
		if (temp->action)
		{
			if (temp->arg)
				while (temp->arg[++i])
				{
					val_add = 0;
					verif_check_args(temp, i, val_add);
				}
			if (g_op_tab[temp->index - 1].octal == 1)
				temp->inst_size++;
			temp->inst_size++;
			asem->prog_size += temp->inst_size;
			if (asem->prog_size > CHAMP_MAX_SIZE)
				length_name_error(3);
		}
		temp = temp->next;
	}
}
