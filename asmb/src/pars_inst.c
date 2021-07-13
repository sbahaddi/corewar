/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:33 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/07 12:21:22 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		get_lable(t_asm *asem, t_inst *inst)
{
	int		i;
	char	*str;
	char	*temp;

	i = -1;
	while (asem->line[++i])
		if (asem->line[i] == ':')
			break ;
	str = asem->line;
	inst->lable = ft_strsub(asem->line, 0, i);
	asem->line = ft_strsub(asem->line, i + 1, ft_strlen(asem->line));
	if (ft_strlen(asem->line) != 0)
	{
		temp = asem->line;
		asem->line = ft_strtrim(asem->line);
		pars_action_next(asem, inst);
		free(temp);
	}
	free(str);
}

int			check_lable(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '%' || !ft_strchr(LABEL_CHARS, str[i]))
			return (1);
	}
	return (0);
}

void		pars_inst(t_asm *asem, t_inst *inst)
{
	int		i;
	char	*temp;

	if (!ft_strchr(asem->line, ':'))
	{
		inst->lable = NULL;
		pars_action_next(asem, inst);
	}
	else if (ft_strchr(asem->line, ':'))
	{
		i = -1;
		while (asem->line[++i])
			if (asem->line[i] == ':')
				break ;
		temp = ft_strsub(asem->line, 0, i);
		if (!check_lable(temp))
			get_lable(asem, inst);
		else
		{
			inst->lable = NULL;
			pars_action_next(asem, inst);
		}
		free(temp);
	}
}
