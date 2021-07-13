/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visu_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:20:55 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 19:50:48 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_help(void)
{
	mvprintw(HEIGHT + 3, WIDTH / 2, "esc : exit | spacebar : pause/resume");
	mvprintw(HEIGHT + 5, WIDTH / 2, "q : -1 | w : /10");
	mvprintw(HEIGHT + 7, WIDTH / 2, "e : +1 | r : *10", 0);
}

void	ft_display_data(t_virtual_m *vm, t_process *p)
{
	if (vm->flgs & VISU)
	{
		attron(COLOR_PAIR(11));
		mvprintw(8, WIDTH + 10, "%-10s", vm->pause ? "'paused'" : "'running'");
		mvprintw(10, WIDTH + 10, "cycles : %5d", vm->cycles);
		mvprintw(12, WIDTH + 10, "process : %5d", ft_count_proces(vm->process));
		mvprintw(24, WIDTH + 10, "delay : %-8d", vm->wait / 100);
		mvprintw(26, WIDTH + 10, "----------------------------");
		mvprintw(28, WIDTH + 10, "cycle to die : %4d", vm->cycles_to_die);
		mvprintw(30, WIDTH + 10, "cycle delta : %4d", vm->cycles_delta);
		mvprintw(32, WIDTH + 10, "lives : %8.8d/21", vm->nbr_live);
		mvprintw(34, WIDTH + 10, "checks %.8d/10", vm->max_checks_counter);
		attroff(COLOR_PAIR(11));
		ft_refresh_all(vm, p);
	}
}

void	ft_visu_endgame(t_virtual_m *vm, t_process *p)
{
	char	ch;

	ch = -1;
	if ((vm->flgs & VISU) && vm->winer)
	{
		attron(COLOR_PAIR(vm->winer->nbr));
		mvprintw(50, WIDTH + 10, "Contestant %d, \"%s\", has won !\n",
		vm->winer->nbr, vm->winer->champ_name);
		attroff(COLOR_PAIR(vm->winer->nbr));
		ft_refresh_all(vm, p);
		while (1)
		{
			ch = getch();
			if (ch == 27)
				break ;
		}
	}
}
