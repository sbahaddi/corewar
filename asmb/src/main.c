/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:18:38 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/17 21:07:36 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		init(t_asm *asem)
{
	asem->temp = NULL;
	asem->temp1 = NULL;
	asem->name = NULL;
	asem->comment = NULL;
	asem->exe = NULL;
	asem->i1 = -1;
	asem->i2 = -1;
	asem->cmp = 1;
}

int				verif_arg(char *str)
{
	int		i;

	i = -1;
	if (str[0] == '-')
		i = 0;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

void			start(t_asm *asem, char **av, int ac)
{
	if (!get_name_comment(&asem))
		error_syntax(asem);
	get_inst(asem);
	check_args(asem);
	check_befor_err(asem);
	if ((asem->fd_w = open(asem->exe, O_WRONLY | O_CREAT, 0644)) < 0)
		error_arg(av[ac - 1]);
	big_endy4(asem, COREWAR_EXEC_MAGIC);
	asemble_name_comm(asem, 1);
	big_endy4(asem, asem->prog_size);
	asemble_name_comm(asem, 2);
	print_inst(asem);
}

int				main(int ac, char **av)
{
	t_asm		*asem;

	if (!(asem = (t_asm *)malloc(sizeof(t_asm))))
		malloc_error();
	ft_memset(asem, 0, sizeof(t_asm));
	if (ac == 1)
		error("Usage: ./asm <sourcefile.s>\n");
	if ((asem->fd_r = open(av[ac - 1], O_RDONLY)) < 0)
		error_arg(av[ac - 1]);
	init(asem);
	asem->exe = name_exe(av[ac - 1], asem);
	start(asem, av, ac);
	ft_printf("Writing output program to %s\n", asem->exe);
	close(asem->fd_r);
	close(asem->fd_w);
	free_as(&asem);
	return (0);
}
