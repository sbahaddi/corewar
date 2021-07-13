/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:51:20 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 13:43:29 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char			*filter_first(t_inst *inst, int i)
{
	char	*str;
	int		j;

	j = -1;
	while (inst->arg[i][++j])
		if (inst->arg[i][j] == ':')
			break ;
	str = ft_strsub(inst->arg[i], j + 1, ft_strlen(inst->arg[i]));
	return (str);
}

void				get_size_diff(t_asm *asem, t_inst *inst, int i)
{
	t_inst	*temp;
	char	*str;
	int		cmp;
	int		k;

	temp = asem->insthead;
	cmp = 0;
	k = 0;
	str = filter_first(inst, i);
	while (temp)
	{
		if (temp->lable)
			if (ft_strcmp(temp->lable, str) == 0)
			{
				k++;
				inst->diff_size = cmp - asem->cmp;
				break ;
			}
		cmp = cmp + temp->inst_size;
		temp = temp->next;
	}
	if (k == 0)
		error_lexic(asem);
	free(str);
}

void				print_inst(t_asm *asem)
{
	t_inst *temp;

	temp = asem->insthead;
	asem->cmp = 0;
	while (temp)
	{
		if (temp->action)
		{
			write(asem->fd_w, &g_op_tab[temp->index - 1].opcode, 1);
			if (g_op_tab[temp->index - 1].octal == 1)
				write(asem->fd_w, &temp->inst_size_char, 1);
			args_print(asem, temp);
		}
		asem->cmp = asem->cmp + temp->inst_size;
		temp = temp->next;
	}
}
