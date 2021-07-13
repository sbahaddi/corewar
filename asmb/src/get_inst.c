/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:27:34 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/17 13:02:20 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		check_comment(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ';' || str[i] == '#')
			return (i);
	}
	return (ft_strlen(str));
}

static void		malloc_inst(t_asm *asem, t_inst **inst)
{
	if (!asem->insthead)
	{
		asem->insthead = malloc(sizeof(t_inst));
		*inst = asem->insthead;
	}
	else
	{
		(*inst)->next = malloc(sizeof(t_inst));
		*inst = (*inst)->next;
	}
}

static void		befor_pars_inst(t_asm *asem, t_inst *inst)
{
	char	*str1;
	char	*str2;
	char	*str3;

	asem->cmp++;
	str1 = asem->line;
	asem->line = ft_strtrim(asem->line);
	str2 = asem->line;
	asem->line = ft_strsub(asem->line, 0, check_comment(asem->line));
	str3 = asem->line;
	asem->line = ft_strtrim(asem->line);
	asem->temp = asem->line;
	pars_inst(asem, inst);
	free(str1);
	free(str2);
	free(str3);
}

static int		check_newline(char *str)
{
	int		len;

	len = ft_strlen(str) - 1;
	if (str[len] == '\n')
		return (1);
	return (0);
}

void			get_inst(t_asm *asem)
{
	t_inst			*inst;
	unsigned int	cmp_inst;
	char			*str;

	cmp_inst = 0;
	while (get_next_line_n(asem->fd_r, &asem->line))
	{
		str = asem->line;
		if (empty_line(asem->line) == 0)
		{
			free(asem->line);
			continue;
		}
		malloc_inst(asem, &inst);
		ft_memset(inst, 0, sizeof(t_inst));
		cmp_inst++;
		asem->new_line = check_newline(str);
		befor_pars_inst(asem, inst);
		free(asem->line);
	}
	if (cmp_inst == 0)
		error_syntax(asem);
	if (asem->new_line != 1)
		length_name_error(4);
	inst->next = NULL;
}
