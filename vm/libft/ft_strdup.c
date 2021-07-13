/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:15:31 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/15 22:46:38 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*t;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	t = (char*)malloc(sizeof(char) * (len + 1));
	if (t == NULL)
	{
		t = NULL;
		return (t);
	}
	while (*s1 != '\0')
		*(t + i++) = *s1++;
	*(t + i) = '\0';
	return (t);
}
