/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:50:24 by lsaidi            #+#    #+#             */
/*   Updated: 2019/10/18 16:49:14 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*name_exe(char *str, t_asm *asem)
{
	int		i;

	if (ft_strstr(str, "/") && (i = ft_strlen(str)))
	{
		while (i--)
			if (str[i] == '/')
				break ;
		asem->temp = str;
		asem->temp = ft_strsub(str, i + 1, ft_strlen(str));
		free(asem->temp);
	}
	if (ft_strstr(str, ".s"))
	{
		i = ft_strlen(str);
		while (i--)
			if (str[i] == '.')
				break ;
		str = ft_strsub(str, 0, i);
		asem->temp = str;
		str = ft_strjoin(str, ".cor");
	}
	else
		error_arg(str);
	free(asem->temp);
	return (str);
}
