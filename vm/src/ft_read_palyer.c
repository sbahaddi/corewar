/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_palyer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:44:54 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 19:38:41 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_read_player_info(t_virtual_m *vm, t_list *player)
{
	int				fd;
	unsigned char	data[5];
	t_player		*p;

	p = player->content;
	fd = open(p->path, O_RDONLY);
	p->champ_name = ft_strnew(PROG_NAME_LENGTH);
	p->champ_cmt = ft_strnew(COMMENT_LENGTH);
	read(fd, data, 4);
	if (ft_get_hex_val(data, 4, 0) != COREWAR_EXEC_MAGIC)
		ft_exit_and_free(vm, NULL, "magic header not exist\n");
	read(fd, p->champ_name, PROG_NAME_LENGTH);
	read(fd, data, 4);
	read(fd, data, 4);
	p->size = ft_get_hex_val(data, 4, 0);
	if (p->size > CHAMP_MAX_SIZE)
		ft_exit_and_free(vm, NULL, "champion has  exceeded the size\n");
	p->exec_code = ft_strnew(p->size);
	read(fd, p->champ_cmt, COMMENT_LENGTH);
	read(fd, data, 4);
	read(fd, p->exec_code, p->size);
	close(fd);
}

void		ft_set_all_player(t_virtual_m *vm, t_list *players)
{
	t_list *head;

	head = players;
	while (head)
	{
		ft_read_player_info(vm, head);
		head = head->next;
	}
}

void		ft_load_player_to_arena(t_virtual_m *vm, t_list *player, int start)
{
	t_player	*p;
	int			i;

	i = -1;
	p = player->content;
	vm->winer = player->content;
	if ((vm->flgs & VISU) == 0)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			p->nbr, p->size, p->champ_name, p->champ_cmt);
	}
	if (vm->flgs & VISU)
	{
		attron(COLOR_PAIR(p->nbr + 4));
		mvprintw(14 + (p->nbr * 2), WIDTH + 10,
		"[player %2.2d] - %s", p->nbr, p->champ_name);
		attroff(COLOR_PAIR(p->nbr + 4));
	}
	while (++i < p->size)
	{
		vm->colors[start + i] = p->nbr + 4;
		vm->arena[start + i] = p->exec_code[i];
	}
}

static void	ft_proc_loop(t_process *process)
{
	int		i;

	i = 0;
	while (++i < REG_NUMBER)
		process->regs[i] = 0;
	if ((process->op = ft_is_operation(process)) != -1)
	{
		process->isverified = 1;
		process->nbr_cycles_actn = g_t_op[process->action - 1].cycles;
	}
}

void		ft_set_process(t_player *player, t_process *process,
							int start_curs, t_virtual_m *vm)
{
	char	*nbr;

	player->start_curs = start_curs;
	process->pc = start_curs;
	process->carry = 0;
	nbr = ft_itoa_base(vm->arena[process->pc], 16);
	process->action = ft_hex_ot_int(nbr);
	process->nbr_live = 0;
	process->isverified = 0;
	process->nbr_cycles_actn = g_t_op[process->action - 1].cycles;
	process->regs[0] = -player->nbr;
	process->vm = vm;
	process->is_live = 0;
	process->op = 0;
	process->id = vm->idgenerator++;
	process->idcolor = process->id;
	ft_proc_loop(process);
	free(nbr);
}
