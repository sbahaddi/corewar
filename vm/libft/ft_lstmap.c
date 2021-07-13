/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:36:33 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/12 17:18:43 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *fl;

	new = NULL;
	fl = NULL;
	if (lst)
	{
		if (!(new = ft_lstnew(f(lst)->content, f(lst)->content_size)))
		{
			free(new);
			return (NULL);
		}
		if (lst->next)
			fl = ft_lstmap(lst->next, f);
		ft_lstadd(&fl, new);
	}
	return (fl);
}
