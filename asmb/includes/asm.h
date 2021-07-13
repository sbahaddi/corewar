/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaidi <lsaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:07:39 by lsaidi            #+#    #+#             */
/*   Updated: 2019/11/17 13:02:38 by lsaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "../libft/includes/libft.h"

typedef struct		s_inst
{
	char			*lable;
	char			*action;
	char			**arg;
	char			arg_type;
	unsigned char	inst_size_char;
	unsigned int	inst_size;
	char			index;
	int				nb_args;
	unsigned int	diff_size;
	struct s_inst	*next;
}					t_inst;

typedef struct		s_asm
{
	char			*line;
	char			*exe;
	char			*temp;
	char			*temp1;
	char			*name;
	char			*comment;
	int				size;
	int				fd_r;
	int				fd_w;
	int				i1;
	int				i2;
	int				cmp;
	int				new_line;
	int				cmp_name_com;
	int				err_line;
	int				err_coln;
	t_inst			*insthead;
	unsigned int	prog_size;
	struct s_asm	*next;
}					t_asm;

int					get_name_comment(t_asm **asem);
void				error_syntax(t_asm *asem);
void				error(char *str);
void				malloc_error(void);
void				error_lexic(t_asm *asem);
void				free_as(t_asm **asem);
void				error_arg(char *str);
int					get_comment(t_asm **asem);
int					get_name(t_asm **asem);
int					pars_name_comment(t_asm **asem);
int					empty_line(char *str);
char				*val_name_comm(t_asm *asem, int k);
int					between_error(char *str);
void				line_end_err(t_asm *asem);
void				endl_err(t_asm *asem);
void				skip_empty_line(t_asm *asem);
void				length_name_error(int k);
void				skip_empty(t_asm *asem);
void				asemble_name_comm(t_asm *asem, int k);
char				*name_exe(char *str, t_asm *asem);
void				er_arg_op(t_inst *inst, char *str, int i);
void				pars_action_next(t_asm *asem, t_inst *inst);
void				error_inst_args(t_inst *inst, int i);
void				pars_inst(t_asm *asem, t_inst *inst);
void				er_arg_label(t_inst *inst, char *str, int i);
int					verif_arg(char *str);
void				duplic_label(t_inst *inst);
void				get_inst(t_asm *asem);
void				check_args(t_asm *asem);
void				check_befor_err(t_asm *asem);
void				print_inst(t_asm *asem);
void				big_endy4(t_asm *asem, int val);
void				big_endy2(t_asm *asem, int val);
int					get_next_line_n(const int fd, char **line);
void				args_print(t_asm *asem, t_inst *inst);
void				get_size_diff(t_asm *asem, t_inst *inst, int i);

#endif
