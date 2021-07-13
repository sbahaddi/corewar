/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:54:37 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/15 17:03:27 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		malloc_error(void)
{
	ft_printf("ERROR malloc\n");
	exit(1);
}

void		error(char *str)
{
	ft_printf(str);
	exit(1);
}

void		error_syntax(t_asm *asem)
{
	if (ft_strlen(asem->line) != 0)
	{
		ft_printf("Syntax error at token [TOKEN] Line -[%d]- \"%s\"\n",
		asem->cmp, asem->line);
	}
	else
		ft_printf("Syntax error at token [TOKEN] Line -[%d]- \"NULL\"\n",
		asem->cmp);
	exit(1);
}

void		error_lexic(t_asm *asem)
{
	ft_printf("Lexical error at Line -[%d]-\n", asem->cmp + 1);
	exit(1);
}

void		error_arg(char *str)
{
	ft_printf("Can't read source file %s\n", str);
	exit(1);
}
