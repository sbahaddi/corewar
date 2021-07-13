/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controle_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:50:23 by sbahaddi          #+#    #+#             */
/*   Updated: 2019/11/17 19:56:05 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_pause_run(t_virtual_m *vm)
{
	vm->pause = vm->pause ? 0 : 1;
	attron(COLOR_PAIR(11));
	mvprintw(8, WIDTH + 10, "%-10s",
	vm->pause ? "'Paused'" : "'running'");
	attroff(COLOR_PAIR(11));
	return (vm->pause);
}

static void	ft_speed(t_virtual_m *vm, int ch)
{
	if (ch == 113 || ch == 119)
		vm->wait -= ch == 113 ? 1000 : 10000;
	if (vm->wait < 1000)
		vm->wait = 1000;
	if (ch == 101 || ch == 114)
		vm->wait += ch == 113 ? 1000 : 10000;
	if (vm->wait > DELAY)
		vm->wait = DELAY;
	attron(COLOR_PAIR(11));
	mvprintw(24, WIDTH + 10, "delay : %-8d", vm->wait / 100);
	attroff(COLOR_PAIR(11));
}

void		ft_control_visu(t_virtual_m *vm, t_process *p)
{
	char		ch;

	ch = -1;
	if (vm->flgs & VISU)
	{
		while (1)
		{
			ch = getch();
			if (ch == 27)
			{
				endwin();
				exit(0);
			}
			else if (ch == 113 || ch == 119 || ch == 101 || ch == 114)
				ft_speed(vm, ch);
			else if (ch == ' ' && !ft_pause_run(vm))
				break ;
			else if (!vm->pause)
				break ;
		}
		ft_refresh_all(vm, p);
		usleep(vm->wait / 100);
	}
}
