/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_name_com.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:47:36 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 17:58:54 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				get_name(t_asm **asem)
{
	char	*str;

	if (ft_strstr((*asem)->line, NAME_CMD_STRING))
	{
		str = (*asem)->line;
		(*asem)->line = ft_strstr((*asem)->line, NAME_CMD_STRING) + 5;
		if (!between_error((*asem)->line))
			error_syntax(*asem);
		(*asem)->name = val_name_comm(*asem, 1);
		free(str);
	}
	return (1);
}

int				get_comment(t_asm **asem)
{
	char	*str;

	if (ft_strstr((*asem)->line, COMMENT_CMD_STRING))
	{
		str = (*asem)->line;
		(*asem)->line = ft_strstr((*asem)->line, COMMENT_CMD_STRING) + 8;
		if (!between_error((*asem)->line))
			error_syntax(*asem);
		(*asem)->comment = val_name_comm((*asem), 2);
		free(str);
	}
	return (1);
}

int				pars_name_comment(t_asm **asem)
{
	int		i;

	if (!(i = 0) && ((ft_strstr((*asem)->line, NAME_CMD_STRING)) ||
	(ft_strstr((*asem)->line, COMMENT_CMD_STRING))))
	{
		while ((*asem)->line[i] == ' ' || (*asem)->line[i] == '\t')
			i++;
		if ((*asem)->line[i] != '.')
			return (0);
		if (ft_strstr((*asem)->line, NAME_CMD_STRING)
		&& (*asem)->line[i + 1] == 'n')
		{
			(*asem)->i1++;
			get_name(asem);
		}
		else if (ft_strstr((*asem)->line, COMMENT_CMD_STRING)
		&& (*asem)->line[i + 1] == 'c')
		{
			(*asem)->i2++;
			get_comment(asem);
		}
	}
	else
		error_syntax(*asem);
	return (1);
}

int				get_name_comment(t_asm **asem)
{
	skip_empty_line(*asem);
	if (!pars_name_comment(asem))
		return (0);
	skip_empty_line(*asem);
	if (!pars_name_comment(asem))
		return (0);
	if ((*asem)->i1 > 0 || (*asem)->i2 > 0)
		error_syntax(*(asem));
	return (1);
}

void			asemble_name_comm(t_asm *asem, int k)
{
	size_t		i;
	size_t		ret;
	int			zero;

	i = -1;
	if (!(zero = 0) && k == 1)
	{
		while (++i < ft_strlen(asem->name) - 1)
			write(asem->fd_w, &asem->name[i], 1);
		ret = PROG_NAME_LENGTH - i;
		i = -1;
		while (++i < ret)
			write(asem->fd_w, &zero, 1);
		write(asem->fd_w, &zero, 4);
	}
	else if (k == 2)
	{
		while (++i < ft_strlen(asem->comment) - 1)
			write(asem->fd_w, &asem->comment[i], 1);
		ret = COMMENT_LENGTH - i;
		i = -1;
		while (++i < ret)
			write(asem->fd_w, &zero, 1);
		write(asem->fd_w, &zero, 4);
	}
}
