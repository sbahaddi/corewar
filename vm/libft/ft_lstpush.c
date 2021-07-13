/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 18:03:54 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/14 18:13:12 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *new)
{
	t_list *head;

	head = *alst;
	if (*alst)
	{
		while ((*alst)->next)
			(*alst) = (*alst)->next;
		new->next = (*alst)->next;
		(*alst)->next = new;
		(*alst) = head;
	}
	else
		ft_lstadd(alst, new);
}
