/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 14:34:15 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 18:00:09 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		free_args(char ***tab)
{
	int				i;
	char			**mx;

	i = -1;
	mx = *tab;
	while (mx[++i])
	{
		free(mx[i]);
		mx[i] = NULL;
	}
	free(mx);
	mx = NULL;
}

static void		free_inst(t_inst **st)
{
	t_inst		*inst;
	t_inst		*tmp;

	inst = *st;
	while (inst)
	{
		tmp = inst->next;
		if (inst->lable)
			free(inst->lable);
		if (inst->action)
		{
			free(inst->action);
			free_args(&inst->arg);
		}
		free(inst);
		inst = NULL;
		inst = tmp;
	}
}

void			free_as(t_asm **asem)
{
	t_asm			*v;
	t_asm			*tmp;

	v = *asem;
	while (v)
	{
		tmp = v->next;
		free(v->name);
		free(v->comment);
		free(v->exe);
		free(v->line);
		free_inst(&v->insthead);
		if (v)
			free(v);
		v = NULL;
		v = tmp;
	}
}
