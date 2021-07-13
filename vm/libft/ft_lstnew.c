/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 02:13:27 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/13 20:00:23 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newls;

	if (!(newls = (t_list *)(malloc(sizeof(t_list)))))
	{
		free(newls);
		return (NULL);
	}
	newls->next = NULL;
	if (!content)
	{
		newls->content = NULL;
		newls->content_size = 0;
		return (newls);
	}
	else
	{
		if (!(newls->content = malloc(content_size + 1)))
		{
			free(newls->content);
			return (NULL);
		}
		ft_memcpy(newls->content, content, content_size);
		newls->content_size = content_size;
	}
	return (newls);
}
