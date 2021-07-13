/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:41:00 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 19:28:02 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** check argument and set flags then add them to list player
** in t_virtual_m (virtual machin) struct
*/

int		ft_addplayer(t_virtual_m *vm, char *av[], int i, int ac)
{
	t_list		*item;
	t_player	*player;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		ft_exit_and_free(vm, player, "player not allocated\n");
	if (ft_strequ("-n", av[i]))
	{
		vm->flgs |= NBR;
		if (ac - i <= 2)
			ft_exit_and_free(vm, player, "too few argument after -n\n");
		player->nbr = ft_atoi(av[++i]);
		if (player->nbr <= 0 || player->nbr > 4)
			ft_exit_and_free(vm, player, "wrong nbr of player [1-4]\n");
		player->path = ft_strdup(av[++i]);
	}
	else
	{
		player->nbr = 0;
		player->path = ft_strdup(av[i]);
	}
	item = ft_lstnew(NULL, 0);
	item->content = player;
	ft_lstpush(&vm->palyers, item);
	return (i);
}

void	ft_checkplayer(t_virtual_m *vm)
{
	t_list	*lst;
	int		i;
	int		ret;

	lst = vm->palyers;
	if ((ret = ft_set_nbr_arg(lst)) == -1)
		ft_exit_and_free(vm, NULL, "too many player [max palyer is 4]\n");
	else
		vm->nbr_player = ret;
	while (lst)
	{
		i = 0;
		while (++i < 5)
		{
			if (ft_get_nbr_player(vm, vm->palyers, i, lst) == 0)
				((t_player *)lst->content)->nbr = i;
		}
		lst = lst->next;
	}
}

/*
** get the next available nbr
*/

int		ft_get_nbr_player(t_virtual_m *vm, t_list *pl, int i, t_list *cur)
{
	t_player	*players;
	t_player	*curplayer;
	int			ret;

	curplayer = cur->content;
	if ((ret = open(curplayer->path, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file : %s", curplayer->path);
		ft_exit_and_free(vm, NULL, "\n");
	}
	if (ret > 0)
		close(ret);
	ret = 0;
	while (pl)
	{
		curplayer = cur->content;
		players = pl->content;
		if (curplayer->arg != players->arg &&
			curplayer->nbr == players->nbr && curplayer->nbr)
			ft_exit_and_free(vm, NULL, "duplicate nbr for player\n");
		if (curplayer->nbr || players->nbr == i)
			ret = 1;
		pl = pl->next;
	}
	return (ret);
}

/*
** set arg number to check if there's duplicate number and help me to set nbr
** for exemple if there's the same name of palyer
*/

int		ft_set_nbr_arg(t_list *pl)
{
	int			arg;
	t_player	*player;

	arg = 0;
	while (pl)
	{
		player = pl->content;
		player->arg = ++arg;
		pl = pl->next;
	}
	if (arg > 4)
		return (-1);
	return (arg);
}
