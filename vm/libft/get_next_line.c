/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:40:44 by akhourba          #+#    #+#             */
/*   Updated: 2019/07/26 13:10:22 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gstrjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = strlen((char *)s1);
	j = strlen((char *)s2);
	str = (char *)ft_memalloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, (char *)s1);
	strcat(str, (char *)s2);
	free(s1);
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char *str;
	int			i;

	i = 0;
	if (fd < 0 || read(fd, &buf, 0) < 0 || !line)
		return (-1);
	if (!str)
		str = ft_strnew(0);
	while ((ret = read((int)fd, &buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		str = ft_gstrjoin(str, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	i = ft_strlenc(str, '\n');
	*line = ft_strsub(str, 0, i);
	if (!ret && !str[0] && !i)
		return (0);
	str = ft_fstrdup(str, str + i + 1);
	return (1);
}
