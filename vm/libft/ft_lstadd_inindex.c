/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_inindex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 18:13:26 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/14 18:17:22 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_inindex(t_list **alst, t_list *new, int i)
{
	int		index;
	t_list	*head;
	t_list	*next;

	index = -1;
	head = NULL;
	next = NULL;
	head = (*alst);
	if ((*alst))
	{
		while ((*alst)->next && ++index < i - 1)
			(*alst) = (*alst)->next;
		if (i == 0)
			ft_lstadd(alst, new);
		else
		{
			new->next = (*alst)->next;
			(*alst)->next = new;
			(*alst) = head;
		}
	}
}
