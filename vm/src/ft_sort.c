/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:31:06 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 19:45:00 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** sort player
*/

void	ft_sort(t_virtual_m *vm)
{
	t_list *head;
	t_list *max;
	t_list *mhead;

	head = vm->palyers;
	while (head)
	{
		max = head;
		mhead = head->next;
		while (mhead)
		{
			if (((t_player *)max->content)->nbr >
				((t_player *)mhead->content)->nbr)
				max = mhead;
			mhead = mhead->next;
		}
		if (((t_player *)max->content)->nbr > vm->nbr_player)
			ft_exit_and_free(vm, NULL, "Wrong Number\n");
		ft_swap(head, max);
		head = head->next;
	}
}

/*
** swap value
*/

void	ft_swap(t_list *head, t_list *max)
{
	void	*content;

	content = head->content;
	head->content = max->content;
	max->content = content;
}
