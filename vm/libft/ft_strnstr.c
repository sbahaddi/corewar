/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 03:06:27 by akhourba          #+#    #+#             */
/*   Updated: 2018/10/09 00:40:51 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = ft_strlen((char *)needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && len-- > 0)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp(haystack, needle, i) == 0)
			{
				if (i > len + 1)
					break ;
				return ((char *)haystack);
			}
		}
		haystack++;
	}
	return (NULL);
}
