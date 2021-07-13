/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 15:04:16 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 20:00:26 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_set_arena_toscreen(t_virtual_m *vm)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	box(vm->win, 0, 0);
	refresh();
	wrefresh(vm->win);
	while (++i <= MEM_SIZE)
	{
		attron(COLOR_PAIR(vm->colors[i - 1]));
		mvprintw(3 + y, 5 + x, "%.2hhx", vm->arena[i - 1]);
		attroff(COLOR_PAIR(vm->colors[i - 1]));
		x += 3;
		if (i % 64 == 0)
		{
			x = 0;
			y++;
		}
	}
}

void		ft_refresh_arena(unsigned char *colors, unsigned char *arena,
						t_process *p, int oldpc)
{
	int		x;
	int		y;
	char	c;

	y = (oldpc) / 64;
	x = (oldpc) % 64;
	x = x + (x * 2);
	attron(COLOR_PAIR(colors[p->oldpc]));
	mvprintw(3 + y, 5 + x, "%.2hhx", arena[p->oldpc]);
	attroff(COLOR_PAIR(colors[p->oldpc]));
	y = (p->pc) / 64;
	x = p->pc % 64;
	x = x + (x * 2);
	c = p->idcolor;
	attron(COLOR_PAIR(c));
	mvprintw(3 + y, 5 + x, "%.2hhx", arena[p->pc]);
	attroff(COLOR_PAIR(c));
}

void		ft_write_to_screen(int x, int y, t_process *p, int i)
{
	unsigned char	*arena;
	unsigned char	*colors;
	int				c;

	arena = ((t_virtual_m *)p->vm)->arena;
	colors = ((t_virtual_m *)p->vm)->colors;
	if (p->pc == i)
	{
		c = p->idcolor;
	}
	else
		c = p->idcolor + 4;
	attron(COLOR_PAIR(c));
	mvprintw(3 + y, 5 + x, "%.2hhx", arena[i]);
	attroff(COLOR_PAIR(c));
}

void		ft_updatearena(t_process *p, int i)
{
	int		x;
	int		y;

	y = (i) / 64;
	x = (i) % 64;
	x = x + (x * 2);
	ft_write_to_screen(x, y, p, i);
}

void		ft_refresh_all(t_virtual_m *vm, t_process *p)
{
	if (p)
		ft_refresh_arena(vm->colors, vm->arena, p, p->oldpc);
	refresh();
	wrefresh(vm->win);
}
