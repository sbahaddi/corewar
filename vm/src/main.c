/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:53:56 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 20:46:32 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_set_visu(t_virtual_m *vm)
{
	if (vm->flgs & VISU)
	{
		initscr();
		noecho();
		nodelay(stdscr, true);
		vm->win = newwin(HEIGHT, WIDTH, 1, 1);
		curs_set(0);
		start_color();
		ft_init_color();
	}
}

int				main(int ac, char **av)
{
	t_virtual_m vm;

	ft_init(&vm);
	ft_set_option(&vm, ac, av);
	ft_checkplayer(&vm);
	if (ac == 1 || !vm.palyers)
		ft_printf_usage(av[0]);
	ft_sort(&vm);
	ft_set_visu(&vm);
	ft_prepare_to_war(&vm);
	if (vm.flgs & VISU)
	{
		ft_set_arena_toscreen(&vm);
		ft_help();
	}
	ft_start_war(&vm);
	if (vm.flgs & VISU)
		endwin();
	ft_free_corewar(&vm);
	return (0);
}
