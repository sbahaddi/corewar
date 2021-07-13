/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:04:05 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 17:45:34 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_printf_usage(char *name)
{
	ft_printf("Usage: %s [-dump nbr_cycles] [[-n number] champion1.cor] ...\n",
				name);
	ft_printf("-------------optional options------------\n");
	ft_printf("-dump nbr_cycles 64\n");
	ft_printf("-n number [1-4]\n");
	ft_printf("-v visualizer\n");
	ft_printf("-l log operations\n");
	exit(0);
}
