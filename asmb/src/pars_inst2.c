/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inst2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:19:51 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 13:43:21 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			check_action(char *act, t_inst *inst)
{
	int i;

	i = -1;
	while (g_op_tab[++i].name)
		if (ft_strcmp(g_op_tab[i].name, act) == 0)
		{
			(inst)->index = i + 1;
			return (1);
		}
	return (0);
}

static void			set_args(t_asm *asem, t_inst *inst)
{
	int		i;
	int		symbol;

	symbol = 0;
	i = -1;
	while (asem->line[++i])
		if (asem->line[i] == ',')
			symbol++;
	if (symbol + 1 != g_op_tab[inst->index - 1].nb_arg)
		er_arg_op(inst, inst->action, symbol);
	else
	{
		i = -1;
		inst->arg = ft_strsplit(asem->line, ',');
		while (++i <= symbol)
			if (inst->arg[i] == NULL)
				er_arg_op(inst, "ENDLINE", i);
	}
}

static void			check_opcode(t_asm *asem, t_inst *inst)
{
	if (check_action(inst->action, inst))
	{
		if (ft_strchr(asem->line, ','))
			set_args(asem, inst);
		else if (ft_strchr(asem->line, '%'))
			inst->arg = ft_strsplit(asem->line, ' ');
		else if (ft_strlen(asem->line) != 0)
			inst->arg = ft_strsplit(asem->line, ' ');
		else
			error_syntax(asem);
	}
	else
		error_lexic(asem);
}

void				pars_action_next(t_asm *asem, t_inst *inst)
{
	int				j;
	unsigned int	k;

	j = -1;
	k = 0;
	while (asem->line[++j])
	{
		if (asem->line[j] == ' ' || asem->line[j] == '\t')
		{
			k = 0;
			break ;
		}
		else if (asem->line[j] == ':')
		{
			k = 1;
			break ;
		}
	}
	inst->action = ft_strsub(asem->line, 0, j - k);
	asem->temp = asem->line;
	asem->line = ft_strsub(asem->line, j - k, ft_strlen(asem->line));
	check_opcode(asem, inst);
	free(asem->temp);
}
