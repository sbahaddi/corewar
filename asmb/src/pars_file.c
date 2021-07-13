/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:07:15 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 16:23:16 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		length_err(char *str, int k)
{
	int		len;

	len = ft_strlen(str);
	if (len > PROG_NAME_LENGTH && k == 1)
		length_name_error(1);
	if (len > COMMENT_LENGTH && k == 2)
		length_name_error(2);
}

static void		add_new_line(t_asm *asem, char *str, int k)
{
	free(asem->temp);
	asem->temp = str;
	str = ft_strjoin(asem->temp, "\n");
	free(asem->temp);
	asem->temp = str;
	free(asem->line);
	length_err(str, k);
}

static char		*endl_get(t_asm *asem, char *str, int k)
{
	int		i;
	char	*temp;

	i = 0;
	while (get_next_line(asem->fd_r, &asem->line) > 0)
	{
		asem->cmp++;
		str = ft_strjoin(asem->temp, asem->line);
		if (ft_strchr(str, '"'))
		{
			i++;
			temp = asem->line;
			line_end_err(asem);
			free(temp);
			break ;
		}
		add_new_line(asem, str, k);
	}
	if (i == 0)
		error_syntax(asem);
	return (str);
}

static char		*endl_name_err(t_asm *asem, char *str, int k)
{
	int		i;
	char	*temp;

	i = 0;
	str = ft_strjoin(asem->line, "\n");
	free(asem->temp);
	asem->temp = str;
	str = endl_get(asem, str, k);
	i = -1;
	while (str[++i])
		if (str[i] == '"')
			break ;
	temp = str;
	str = ft_strsub(str, 0, i + 1);
	length_err(str, k);
	free(temp);
	return (str);
}

char			*val_name_comm(t_asm *asem, int k)
{
	char	*str;
	int		i;

	asem->temp = asem->line;
	asem->line = ft_strchr(asem->line, '"') + 1;
	if ((i = -1) && ft_strchr(asem->line, '"'))
	{
		while (asem->line[++i])
			if (asem->line[i] == '"')
				break ;
		str = ft_strsub(asem->line, 0, i + 1);
		line_end_err(asem);
		length_err(str, k);
		return (str);
	}
	else
	{
		asem->temp = ft_strdup("\0");
		str = ft_strjoin(asem->temp, asem->line);
		free(asem->temp);
		asem->temp = str;
		str = endl_name_err(asem, str, k);
		free(asem->temp);
	}
	return (str);
}
