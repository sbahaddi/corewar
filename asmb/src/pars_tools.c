/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:04:15 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 17:52:12 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			empty_line(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_strlen(str) != 0)
	{
		temp = str;
		temp = ft_strtrim(str);
		if (temp[0] == '#' || temp[0] == ';')
		{
			free(temp);
			return (0);
		}
		i = ft_strlen(temp);
		free(temp);
	}
	return (i);
}

void		line_end_err(t_asm *asem)
{
	char		*temp;
	size_t		i;

	i = 0;
	temp = asem->line;
	asem->line = ft_strchr(asem->line, '"') + 1;
	while (asem->line[i] == ' ' || asem->line[i] == '\t')
		i++;
	if (i != ft_strlen(asem->line))
	{
		if (asem->line[i] == '#' || asem->line[i] == ';')
			;
		else
			error_syntax(asem);
	}
}

int			between_error(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] != '"')
		return (0);
	return (1);
}

void		skip_empty_line(t_asm *asem)
{
	int			i;

	i = -1;
	while (get_next_line(asem->fd_r, &asem->line) > 0)
	{
		asem->temp1 = asem->line;
		if (empty_line(asem->line) != 0)
			break ;
		asem->cmp++;
		free(asem->temp1);
	}
}

void		skip_empty(t_asm *asem)
{
	char		*str;

	while (get_next_line(asem->fd_r, &asem->line) > 0)
	{
		asem->cmp++;
		str = asem->line;
		if (empty_line(asem->line) != 0)
			break ;
		free(str);
	}
}
