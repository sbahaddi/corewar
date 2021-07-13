/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_endy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:36 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/07 12:25:52 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			big_endy4(t_asm *asem, int val)
{
	int magic;

	if (val < 0)
		magic = (((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
				((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24));
	else
		magic = (((val >> 24) & 0x000000FF) | ((val >> 8) & 0x0000FF00) |
				((val << 8) & 0x00FF0000) | ((val << 24) & 0xFF000000));
	write(asem->fd_w, &magic, 4);
}

void			big_endy2(t_asm *asem, int val)
{
	int magic;

	if (val < 0)
		magic = (((val & 0xFF) << 8) | ((val & 0xFF00) >> 8));
	else
		magic = (((val >> 8) & 0x00FF) | ((val << 8) & 0xFF00));
	write(asem->fd_w, &magic, 2);
}
