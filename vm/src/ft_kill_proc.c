/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:20:18 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 17:44:50 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** kill the process the arn't declare live in this period of cycles_to_die
** and return the max nbr of live
** this function not tested yet
*/

static void	ft_kill_it(t_list **prev, t_list **curr, t_list **lst)
{
	if (!(*prev))
	{
		(*prev) = (*curr)->next;
		free((*curr)->content);
		free((*curr));
		(*lst) = (*prev);
		(*curr) = (*prev);
		(*prev) = NULL;
	}
	else
	{
		(*prev)->next = (*curr)->next;
		free((*curr)->content);
		free((*curr));
		(*curr) = (*prev)->next;
	}
}

void		ft_kill_process(t_list **lst)
{
	t_list		*curr;
	t_list		*prev;
	t_list		*head;
	t_process	*p;

	curr = (*lst);
	head = (*lst);
	prev = NULL;
	while (curr)
	{
		p = curr->content;
		if (p->is_live == 0 || p->vm->cycles_to_die < 0)
			ft_kill_it(&prev, &curr, lst);
		else
		{
			p->is_live = 0;
			p->nbr_live = 0;
			prev = curr;
			curr = curr->next;
		}
	}
}
