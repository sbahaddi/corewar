/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:38:17 by akhourba          #+#    #+#             */
/*   Updated: 2019/11/17 21:03:33 by sbahaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <ncurses.h>
# define DUMP 1
# define VISU 2
# define NBR 4
# define LOGVM 8
# define SHIFT(x,i) (x << (8)
# define HEIGHT 68
# define WIDTH 200
# define M(x) (x % MEM_SIZE)
# define DELAY 1000000

typedef struct s_virtual_m	t_virtual_m;

typedef struct				s_palyer
{
	int		nbr;
	int		arg;
	int		start_curs;
	char	*path;
	char	*champ_cmt;
	char	*champ_name;
	int		size;
	char	*exec_code;
	int		lst_live;
}							t_player;

typedef struct				s_process
{
	unsigned int	regs[REG_NUMBER];
	int				pc;
	int				oldpc;
	unsigned int	id;
	int				idcolor;
	char			carry;
	int				nbr_live;
	int				is_live;
	int				nbr_cycles_actn;
	int				is_moved;
	char			action;
	int				isverified;
	int				op;
	int				l_pc;
	int				i;
	t_virtual_m		*vm;
}							t_process;

typedef void				(*t_ft_op) (unsigned char *, t_process *);

struct						s_virtual_m
{
	int				nbr_process;
	unsigned char	flgs;
	int				fd;
	int				nbr_player;
	int				cycles_to_die;
	int				cycles_to_die_counter;
	int				cycles_to_check;
	int				cycles_delta;
	int				cycles;
	int				nbr_live;
	int				max_checks_counter;
	unsigned char	*arena;
	unsigned char	*colors;
	int				idgenerator;
	int				dump_cycle;
	int				lst_op;
	int				wait;
	int				pause;
	WINDOW			*win;
	t_ft_op			*tab_ft_op;
	t_op			tab_op[17];
	t_list			*palyers;
	t_player		*winer;
	t_list			*process;
};

void						ft_init(t_virtual_m *vm);

/*
** ---------reading input set value check error----------
*/

t_list						*ft_set_option(t_virtual_m *vm, int ac, char *av[]);
int							ft_read_magic_header(int fd);
int							ft_addplayer(t_virtual_m *vm, char *av[],
							int i, int ac);
int							ft_set_nbr_arg(t_list *pl);
void						ft_checkplayer(t_virtual_m *vm);
int							ft_get_nbr_player(t_virtual_m *vm, t_list *pl,
							int i, t_list *cur);

/*
** --------------------convert---------------------
*/
int							ft_hex_ot_int(char *nbr);
int							ft_get_hex_val(unsigned char *l, int size, int pc);

/*
** --------------------player---------------------
*/

void						ft_read_player_info(t_virtual_m *vm,
							t_list *player);
void						ft_set_all_player(t_virtual_m *vm, t_list *players);

/*
** --------------------prepare arena and load executable code to arena------
*/
void						ft_prepare_to_war(t_virtual_m *vm);
void						ft_load_player_to_arena(t_virtual_m *vm,
							t_list *player, int start);

/*
** --------------------initialise process and set them --------------
*/

void						ft_set_process(t_player *player, t_process *process,
							int start_curs, t_virtual_m *vm);

/*
** ---------------usage--------------------
*/

void						ft_printf_usage(char *name);

/*
**--------free and init --------------
*/
void						ft_exit_and_free(t_virtual_m *vm, void *unit,
							char *s);
void						ft_free_corewar(t_virtual_m *vm);
void						ft_free_players(t_list **pl);

/*
** -----------sort-------------------
*/

void						ft_sort(t_virtual_m *vm);
void						ft_swap(t_list *head, t_list *max);

/*
** -----------anything related to war like action and count cycles------
*/
unsigned int				ft_is_operation(t_process *p);
void						ft_kill_process(t_list **lst);
t_list						*ft_cycles_counter(t_virtual_m *vm);
void						ft_start_war(t_virtual_m *vm);
void						ft_check_process(unsigned char *arena,
							t_list *process,
							t_ft_op *tab_ft_op, t_list *player);
/*
** -----------instruction function -------------------
*/

t_ft_op						*ft_set_ft_op();
void						ft_live(unsigned char *arena, t_process *p);
void						ft_ld(unsigned char *arena, t_process *p);
void						ft_st(unsigned char *arena, t_process *p);
void						ft_add(unsigned char *arena, t_process *p);
void						ft_sub(unsigned char *arena, t_process *p);
void						ft_and(unsigned char *arena, t_process *p);
void						ft_or(unsigned char *arena, t_process *p);
void						ft_xor(unsigned char *arena, t_process *p);
void						ft_zjmp(unsigned char *arena, t_process *p);
void						ft_ldi(unsigned char *arena, t_process *p);
void						ft_sti(unsigned char *arena, t_process *p);
void						ft_fork(unsigned char *arena, t_process *p);
void						ft_lld(unsigned char *arena, t_process *p);
void						ft_lldi(unsigned char *arena, t_process *p);
void						ft_lfork(unsigned char *arena, t_process *p);
void						ft_aff(unsigned char *arena, t_process *p);
void						ft_getvalueofbitop(unsigned char *arena,
							t_process *p,
							int *val, int i_op);
int							ft_ismatch_argtype(unsigned char val,
							int i_op, t_process *p);
void						set_value_to_arena(unsigned char *arena,
							unsigned int val, int index, t_process *p);
void						ft_copie_process(t_process *p_src, t_process *p_dst,
							int start_curs, unsigned char *arena);
int							ft_skip_bytes(t_process *p, int val, int i_op);
/*
** -----------------------------visualiser
*/
void						ft_init_color();
void						ft_set_arena_toscreen(t_virtual_m *vm);
void						ft_refresh_arena(unsigned char *colors,
							unsigned char *arena,
							t_process *p, int oldpc);
void						ft_write_to_screen(int x, int y,
							t_process *p, int i);
void						ft_updatearena(t_process *p, int i);
void						ft_ini_color_arena(t_virtual_m *vm);
void						ft_refresh_all(t_virtual_m *vm, t_process *p);
void						ft_help();
void						ft_display_data(t_virtual_m *vm, t_process *p);
void						ft_control_visu(t_virtual_m *vm, t_process *p);
void						ft_visu_endgame(t_virtual_m *vm, t_process *p);
void						ft_do_proc(t_virtual_m *vm, t_process *p);
void						ft_checkcycles(t_virtual_m *vm);

/*
** debug start
*/

void						ft_print_hex_val(char *l, int size);
int							ft_count_proces(t_list *process);

/*
** debug end
*/

#endif
